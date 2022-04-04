
# Create the basis SD Card Image

Install and Start RPI-IMAGER
Choose "Raspberry Pi OS (other)"
Choose "Raspberry Pi OS Lite (64-bit)"

Configure the Image using the Settings Dialog
-> Enable SSH + Add Key
-> Set UserName + Password
-> Enable Wifi + Configure your SSID

# Start up the newly create OS

Plug in the SD-Card and power on your RPI device
Login using your configured username or if possible SSH with Key.
When logged in, switch to the root user using `sudo su`.

# Update the OS to latest

As the Image is a bit older, it makes sense to Update the OS to the latest state.
To load the newer kernel, we have to restart the RPI.
```
apt -y update
apt -y dist-upgrade
reboot
```

If you experience reboot hangs, make sure that your eeprom firmware is up to date.

# Install the Waveshare display drivers

As I use the [Waveshare 7 inch DSI LCD 1024x600](https://www.waveshare.com/wiki/7inch_DSI_LCD_(C)) display on my Raspberry PI, I need to install the correct driver to bring it on.

```
apt -y install git build-essential 
cd /usr/src/
git clone https://github.com/waveshare/7inch-DSI-LCD-C.git
cd 7inch-DSI-LCD-C/64/$(uname -r|awk -F \- '{print $1}')
./WS_7inchDSI1024x600_MAIN.sh
reboot
```

Your display should come to life when the system reboots.
If not, please consult the Waveshare support documentation.

# Install the frontend to the RPI

Depending on your display, first you have to create a link to the correct touchpanel input device.
You need to find out wich input device is the correct one on your system.
Use `evtest /dev/input/by-path/xxxx` and replace XX with the available options.
While the command is running, you need to touch the screen to see if it's the right one.
Both HDMI ports create a event entry and your touch should be the third.
Unfortunately they are in random order on each system start. 
Therefore we make sure it will work always.

When you found the correct one, create a symlink like this:
```
mkdir -p /usr/lib/rv-hud/bin/
ln -s /dev/input/by-path/platform-*.i2c-event /usr/lib/rv-hud/bin/touchscreen
```

Now that the touchscreen is ready, we can install the GUI.

```
apt -y install cmake extra-cmake-modules cmake-extras libsdl2-2.0-0 libsdl2-dev
cd /usr/src/
git clone --recurse-submodules git@github.com:MartinVerges/rv-hud.git
cd rv-hud/
cmake -DCMAKE_BUILD_TYPE=Release .
make
make install
```

Warning: The service will start up directly and you can't stop it from the tty.
This will install the display as a system service.
In addition it configures it to start on boot.

# Installation of the MQTT Broker

All available information of your sensors will be managed inside the MQTT broker.
If you have none available, installing it on the Raspberry PI could be a good choice.

```
apt -y install mosquitto mosquitto-clients
mosquitto_passwd -c -b /etc/mosquitto/passwd gui abcd1234
cat > /etc/mosquitto/conf.d/rv-hud.conf << EOL
listener 1883 0.0.0.0
allow_anonymous false
password_file /etc/mosquitto/passwd
EOL
systemctl restart mosquitto.service
```
