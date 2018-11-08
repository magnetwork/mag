MAG Core version *1.0.0* (a fork from PIVx 3.1) is now available from:  <https://github.com/magnetwork/mag/releases>

Please report bugs using the issue tracker at github: <https://github.com/magnetwork/mag/issues>

Mandatory Update
==============

- FIRST RELEASE

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

- FIRST RELEASE

User Experience
--------------

### Graphical User Interface

The visual layout of the MAG Qt wallet has undergone a complete overhaul.
The overview tab has been simplified greatly to display only balances that are active or relevant, also a reward section has been added.
A merchant tab, which lets you login to your [merchant dashboard](https://merchant.magnetwork.io/) (can be turned off in the options).

### Wallet Options

-	The stake split threshold (default: 2000) can now be set via the wallet options.
-	“Unlock for staking and anonymization only” is selected by default when unlocking the wallet from the User Interface

Technical Changes
--------------

- FIRST RELEASE

*1.0.0* Change log
--------------

Detailed release notes follow. This overview includes changes that affect behavior, not code moves, refactors and string updates. For convenience in locating the code changes and accompanying discussion, both the pull request and git merge commit are mentioned.

### Core Features
 - #001 `cb1632520` [Core] FIRST RELEASE

### Build System
 - #001 `9071bfe2f` [Depends] FIRST RELEASE
 
### P2P Protocol and Network Code
 - #001 `61156def7` [Network] FIRST RELEASE

### GUI
 - #001 `d9b23fe60` [Qt] FIRST RELEASE
 
### RPC/REST
 - #001 `772160b1b` [Wallet/RPC] FIRST RELEASE

### Wallet
 - #001 `8c8350b59` [Wallet] FIRST RELEASE
 
### Miscellaneous
 - #001 `d2b017217` [Bug] FIRST RELEASE
 
## Credits

- Bitcoin Core Team
- Dash Team
- PIVx Team
- MAG Team