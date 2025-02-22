# Archipelago Star Fox 64
This repository contains everything needed to build the ROM Hack, the .apworld and all connectors necessary for playing Star Fox 64 in Archipelago.

# How to use
Download and install the .apworld from releases. You will also need the connector for the platform you want to play on. See the setup guide for more information.

# How to build
## Dependencies
In the n64/tools folder, you will need to place:
* [mips64/](https://github.com/DragonMinded/libdragon/releases/tag/toolchain-continuous-prerelease)
* [armips](https://github.com/Kingcom/armips/releases)
* ed64romconfig (can be built from [libdragon](https://github.com/DragonMinded/libdragon))

In the n64/rom folder, you will need to place a file called `Star_Fox_64.z64`. This file cannot be byte-swapped. The MD5 of the file needed is: `741a94eee093c4c8684e66b89f8685e8`

Run `make` followed by `make release`. Needed files will be in the release folder.
