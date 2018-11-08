// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_GUICONSTANTS_H
#define BITCOIN_QT_GUICONSTANTS_H

/* Milliseconds between model updates */
static const int MODEL_UPDATE_DELAY = 1000;

/* AskPassphraseDialog -- Maximum passphrase length */
static const int MAX_PASSPHRASE_SIZE = 1024;

/* Mag GUI -- Size of icons in status bar */
static const int STATUSBAR_ICONSIZE = 16;

static const bool DEFAULT_SPLASHSCREEN = true;

/* Invalid field background style */
#define STYLE_INVALID "background:#ce8e8e"

/* Transaction list -- unconfirmed transaction */
#define COLOR_UNCONFIRMED QColor(95, 95, 80)
/* Transaction list -- negative amount (RED)*/
#define COLOR_NEGATIVE QColor(200, 75, 75)
/* Transaction list -- bare address (without label - Dark Gray) */
#define COLOR_BAREADDRESS QColor(110, 110, 110)
/* Transaction list -- TX status decoration - open until date */
#define COLOR_TX_STATUS_OPENUNTILDATE QColor(60, 120, 150)
/* Transaction list -- TX status decoration - offline */
#define COLOR_TX_STATUS_OFFLINE QColor(192, 192, 192)
/* Transaction list -- TX status decoration - default color */
#define COLOR_BLACK QColor(51, 51, 51)
/* Transaction list -- TX status decoration - conflicted (LIGHT RED) */
#define COLOR_CONFLICTED QColor(200, 100, 100)
/* Transaction list -- TX status decoration - orphan (Light Gray #D3D3D3) */
#define COLOR_ORPHAN QColor(211, 211, 211)
/* Transaction list -- TX status decoration - stake (Blue-Gray #7c8282) */
#define COLOR_STAKE QColor(124,130,130)
/* Tooltips longer than this (in characters) are converted into rich text,
   so that they can be word-wrapped.
 */
static const int TOOLTIP_WRAP_THRESHOLD = 80;

/* Maximum allowed URI length */
static const int MAX_URI_LENGTH = 255;

/* QRCodeDialog -- size of exported QR Code image */
#define EXPORT_IMAGE_SIZE 256

/* Number of frames in spinner animation */
#define SPINNER_FRAMES 35

#define QAPP_ORG_NAME "MAG"
#define QAPP_ORG_DOMAIN "magnetwork.io"
#define QAPP_APP_NAME_DEFAULT "MAG-Qt"
#define QAPP_APP_NAME_TESTNET "MAG-Qt-testnet"

#endif // BITCOIN_QT_GUICONSTANTS_H
