MAG Core version *1.0.0* is now available from:  <https://github.com/magnetwork/mag/releases>

Please report bugs using the issue tracker at github: <https://github.com/magnetwork/mag/issues>

Mandatory Update
==============

MAG Core v1.0.0 is a mandatory update for all users on Magnet Network. This release contains a new core base (PIVx 3.1 fork) and major protocol changes that are not backwards compatible with any older versions of Magnet clients.

Existing users have up till November 12, 2018 to Swap their coins on [Cryptopia Exchange](https://support.cryptopia.co.nz/csm?id=kb_article&sys_id=7eb0d4e8dbe1a780d7e096888a961908). If you have not done so and missed the deadline, please contact us _now_.

How to Install / Upgrade
==============

If you are running an older version, shut it down. Wait until it has completely shut down (which might take a few minutes for older versions), then run the installer (on Windows) or just copy over /Applications/MAG-Qt (on Mac) or magd/mag-qt (on Linux).

Compatibility
==============

MAG Core is extensively tested on multiple operating systems using
the Linux kernel, macOS 10.8+, and Windows Vista and later.

Microsoft ended support for Windows XP on [April 8th, 2014](https://www.microsoft.com/en-us/WindowsForBusiness/end-of-xp-support),
No attempt is made to prevent installing or running the software on Windows XP, you
can still do so at your own risk but be aware that there are known instabilities and issues.
Please do not report issues about Windows XP to the issue tracker.

MAG Core should also work on most other Unix-like systems but is not
frequently tested on them.

### :exclamation::exclamation::exclamation: MacOS 10.13 High Sierra :exclamation::exclamation::exclamation:

**Currently there are issues with the 3.x gitian release on MacOS version 10.13 (High Sierra), no reports of issues on older versions of MacOS.**

 
Notable Changes
==============

With this new client we are switching from a hybrid Proof-of-Work/Proof-of-Stake (POW/POS) network to a full Proof-Of-Stake based network. The reward distribution has been redesigned, detailed information and links are available in the repository README.md.

User Experience
--------------

### Graphical User Interface

The visual layout of the MAG Qt wallet has undergone a complete overhaul.
The overview tab has been simplified greatly to display only balances that are active or relevant, also a reward section has been added.
A merchant tab, which lets you login to your [merchant dashboard](https://merchant.magnetwork.io/) (can be turned off in the options) is also present.

### Wallet Options

-	The stake split threshold (default: 2000) can now be set via the wallet options.
-	“Unlock for staking and anonymization only” is selected by default when unlocking the wallet from the User Interface

Technical Changes
--------------

Due to the recent issues and vulnerabilities found on ZeroCoin protocol we will not be activating it for the launch. We do not rule out using obfuscation mechanisms in the future but only from well tested solutions as we cannot afford the maintenance overhead should any issue arise (exchanges, collaterals…) with our present resources/team/support available.

*1.0.0* Change log
--------------

Initial release.
 
## Credits

- Bitcoin Core Team
- Dash Team
- PIVx Team
- MAG Team
