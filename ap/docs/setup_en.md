# Setup guide for Star Fox 64

## Prerequisites

You will need the Star Fox 64 v1.1 ROM. MD5s of supported files:
* `741a94eee093c4c8684e66b89f8685e8`
* `ef9a76901153f66123dafccb0c13cd94`

You can play either on Bizhawk, on Project 64 4.0 or on a real n64 console using an EverDrive64 (either v3.0 or X7)
* [Bizhawk](https://tasvideos.org/BizHawk/ReleaseHistory)
  * Version 2.10 and later is supported.
  * Detailed installation instructions for BizHawk can be found at the above link.
  * Windows users must run the prereq installer first, which can also be found at the above link.
* [Project 64 4.0](https://www.pj64-emu.com/nightly-builds)
  * Project 64 4.0 is currently in developement, however Dev-4.0.0-6555-9034bc6 was tested and no issues were found.
  * You can either use the installer, or the zip, both of which can be found at the above link.
* EverDrive 64
  * You will need to install the USB driver for your OS.
    * [Windows](https://ftdichip.com/wp-content/uploads/2021/08/CDM212364_Setup.zip)
    * [Linux](https://ftdichip.com/wp-content/uploads/2022/07/libftd2xx-x86_64-1.4.27.tgz)
  * For EverDrive v3.0, the OS version needs to be 3.06 to be compatible. The X7 can use the latest OS version.
  * The Nintendo 64 Expansion Pak is required

# Configuration & Playing

* [Bizhawk](#bizhawk)
* [Project 64](#project-64)
* [EverDrive 64](#everdrive-64)

## Bizhawk

No specific configuration is necessary for Bizhawk. However, it is recommended to enable AutoSaveRAM. Every 5s is fine.

Load the game, and then load the `Archipelago/data/lua/connector_sf64_bizhawk.lua`. Use the Archipelago Launcher's `Browse Files` button to find the Archipelago directory.

## Project 64

* Click `Options` -> `Configuration`
* Under `General settings`:
  * Uncheck `Pause emulation when window is not active`
  * Uncheck `Hide advanced settings`
* Under `General settings` -> `Advanced`:
  * Check `Enable debugger`
* Click OK
* Click `Debugger` -> `Scripts...`
* Click the `...` button. This will open the scripts folder. Place the `connector_sf64_pj64.js` file here

Load the game, and then load the connector script.

## EverDrive 64

No specific configuration is necessary for EverDrive 64.

Load the game, and then run the `connector_sf64_ed64` executable.
