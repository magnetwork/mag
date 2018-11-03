// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "pow.h"

#include "chain.h"
#include "chainparams.h"
#include "main.h"
#include "primitives/block.h"
#include "uint256.h"
#include "util.h"

#include <math.h>


unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader* pblock)
{
    if (pindexLast->nHeight <= Params().LAST_POW_BLOCK()) {
        return Params().ProofOfWorkLimit().GetCompact();
    }
    else {
        uint256 bnTargetLimit = (~uint256(0) >> 32);

        if(!(pindexLast->IsProofOfStake() && pindexLast->pprev->IsProofOfStake())) {
            return bnTargetLimit.GetCompact();
        }
        else {
            int64_t nTargetSpacing = 60;
            // We want a narrower retargeting window as we switch to POS
            // then progressively widen out.
            int64_t nTargetTimespan = 60 * std::min(40, (pindexLast->nHeight - Params().LAST_POW_BLOCK()) + 5);
            int64_t diff = pindexLast->GetBlockTime() - pindexLast->pprev->GetBlockTime();
            int64_t nActualSpacing = diff < 1 ? 1 : diff;

            // ppcoin: target change every block
            // ppcoin: retarget with exponential moving toward target spacing
            uint256 bnNew;
            bnNew.SetCompact(pindexLast->nBits);

            int64_t nInterval = nTargetTimespan / nTargetSpacing;
            bnNew *= ((nInterval - 1) * nTargetSpacing + nActualSpacing + nActualSpacing);
            bnNew /= ((nInterval + 1) * nTargetSpacing);

            if (bnNew <= 0 || bnNew > bnTargetLimit)
                bnNew = bnTargetLimit;

            return bnNew.GetCompact();
        }
    }
}

bool CheckProofOfWork(uint256 hash, unsigned int nBits)
{
    bool fNegative;
    bool fOverflow;
    uint256 bnTarget;

    if (Params().SkipProofOfWorkCheck())
        return true;

    bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

    // Check range
    if (fNegative || bnTarget == 0 || fOverflow || bnTarget > Params().ProofOfWorkLimit())
        return error("CheckProofOfWork() : nBits below minimum work");

    // Check proof of work matches claimed amount
    if (hash > bnTarget)
        return error("CheckProofOfWork() : hash doesn't match nBits");

    return true;
}

uint256 GetBlockProof(const CBlockIndex& block)
{
    uint256 bnTarget;
    bool fNegative;
    bool fOverflow;
    bnTarget.SetCompact(block.nBits, &fNegative, &fOverflow);
    if (fNegative || fOverflow || bnTarget == 0)
        return 0;
    // We need to compute 2**256 / (bnTarget+1), but we can't represent 2**256
    // as it's too large for a uint256. However, as 2**256 is at least as large
    // as bnTarget+1, it is equal to ((2**256 - bnTarget - 1) / (bnTarget+1)) + 1,
    // or ~bnTarget / (nTarget+1) + 1.
    return (~bnTarget / (bnTarget + 1)) + 1;
}
