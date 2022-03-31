# rv-hud

This project should result in a control unit of a mobile home. The aim of the project is to display and control the sensors and functions of the motorhome centrally via a touch panel.

The whole thing will work together with WOMO\_LIN to ensure the greatest possible compatibility with different manufacturers.

## Current State

Currently, the design is being developed and implemented. As soon as this is completed, the necessary functions will be added.

## Screenshots

<img src="screenshots/mainscreen.png?raw=true" alt="Main Screen" width="50%">
<img src="screenshots/settings.png?raw=true" alt="Main Screen" width="50%">

## Prepare simulator

In order to run it on a simulator, you have to change the Symlink of `lv_conf.h`, `lv_drv_conf.h`, and `Makefile` to simulator.

```
ln -sf lv_conf.h.simulator lv_conf.h
ln -sf lv_drv_conf.h.simulator lv_drv_conf.h
ln -sf Makefile.simulator Makefile
make clean
```

To run it on the Raspberry PI, please use:
```
ln -sf lv_conf.h.raspberry lv_conf.h
ln -sf lv_drv_conf.h.raspberry lv_drv_conf.h
ln -sf Makefile.raspberry Makefile
make clean
```

## License

rv-smart-tanksensor (c) by Martin Verges.

rv-smart-tanksensor is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this work.
If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

### Design

A special thanks to the excellent designer [Florian Koczy](https://koczy-design.de), who developed the design for this project!

