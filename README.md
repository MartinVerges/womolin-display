# rv-hud

This project should result in a control unit of a mobile home. The aim of the project is to display and control the sensors and functions of the motorhome centrally via a touch panel.

The whole thing will work together with WOMO\_LIN to ensure the greatest possible compatibility with different manufacturers.

## Current State

It's a working prototype.
After installation, it will start and show the Tank status.
The status itself comes from a MQTT Server that you need to provide or install on the RPI.

You can change and modify the settings comfortably from the GUI itself by accessing the settings dialog.

## Used Hardware

I used my [wifi-hotspot](https://github.com/MartinVerges/wifi-HotSpot/) Raspberry Pi for the GUI.

- Raspberry PI (I use the [4B with 8GB variant](https://www.amazon.de/gp/product/B0899VXM8F))
- SD card (e.g. [SanDisk Extreme Pro 64GB](https://www.amazon.de/gp/product/B07G3GMRYF))
- Display (e.g. [Waveshare 7inch 1024x600 DSI IPS Touch](https://www.amazon.de/gp/product/B09QHYKY5R))

Please note: at the current state, this Project only works on 1024x600 pixel and provides no other configurations.

## Installation

If you want to give it a try, take a look at the [INSTALL.md](https://github.com/MartinVerges/womolin-display/blob/main/INSTALL.md) documentation.

## Screenshots

<img src="screenshots/mainscreen.png?raw=true" alt="Main Screen" width="50%">
<img src="screenshots/settings.png?raw=true" alt="Settings" width="50%">
<img src="screenshots/batteries.png?raw=true" alt="Battery state" width="50%">
<img src="screenshots/gas_level.png?raw=true" alt="Gas level" width="50%">

## Prepare simulator

In order to run it on a simulator, you have to change the Symlink of `lv_conf.h`, `lv_drv_conf.h`, and `Makefile` to simulator.

```
git update-index --skip-worktree lv_conf.h lv_drv_conf.h
ln -sf lv_conf.h.simulator lv_conf.h
ln -sf lv_drv_conf.h.simulator lv_drv_conf.h
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build .
```

To run it on the Raspberry PI, please use:
```
git update-index --skip-worktree lv_conf.h lv_drv_conf.h
ln -sf lv_conf.h.raspberry lv_conf.h
ln -sf lv_drv_conf.h.raspberry lv_drv_conf.h
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .
```

## License

rv-smart-tanksensor (c) by Martin Verges.

rv-smart-tanksensor is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this work.
If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

### Design

A special thanks to the excellent designer [Florian Koczy](https://koczy-design.de), who developed the design for this project!
