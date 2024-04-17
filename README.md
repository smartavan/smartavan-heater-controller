# Smartavan Heater Controller

This repository contains ESPHome config for Smartavan heater controller.

Product is available for purchase at https://shop.smartavan.com/products/smartavan-heater-controller

Device itself is connected between Truma CP Plus (this or newer "iNET READY" control panel is required).

![Smartavan heater controller (front)](img/smartavan-heater-controller-front.jpg)

![Smartavan heater controller (back)](img/smartavan-heater-controller-back.jpg)

It is used to control Truma/Alde and other possibly supported RV heaters (and ACs).

Thanks to @Fabian-Schmidt for creating [custom component](https://github.com/Fabian-Schmidt/esphome-truma_inetbox) which enables communication with the heater.

## Physical device installation

1. Disconnect the RJ-12 cable from Truma CP Plus and connect it to Smartavan Heater Controller IN -port
2. Attach RJ-12 cable coming from Smartavan Heater Controller OUT -port to Truma CP Plus
3. Disconnect the JST power cable from Truma CP Plus and connect it to Smartavan Heater Controller IN -port
4. Attach JST cable coming from Smartavan Heater Controller OUT -port to Truma CP Plus

## Connecting to Wifi

With your mobile phone/computer, connect to `smartavan-heater-XXXXX` network. Page `http://192.168.4.1` should open automatically (if not, go to that address manually).

Then connect Smartavan Heater Controller to your WiFi network.

It will by default get IP Address from your DHCP server.

Then, you will be able to open up web page of the device, showing its current status.

If you want to define static IP address for it, modify config file accordingly.

## Enabling control from Truma CP Plus

If you want to watch video how it is done, see https://www.youtube.com/shorts/HoGUFc7grXM

1. Go to settings on Truma CP Plus
2. Scroll to `RESET` and press button
3. Press button again (selects `PR SET`)
4. Screen will show `INIT..` and it searches for the device, screen will flicker few times and finally it will reboot

Confirm the connection:
1. Go to settings
2. Go to `INDEX`
3. You see version numbers here. First one is F4.XX.XX, second one is H5.YY.YY (or H4) and the third one, `T23.ZZZ` is the Smartavan Heater Controller

Now you should be able to control device from ESPHome web page.

## Integrating with Home Assistant

Go to Settings -> Integrations on Home Assistant. There you should see immediately the new ESPHome device.

## Operating without Home Assistant integration

If you want to use the device without Home Assistant integration as a standalone device - or integrate it via MQTT to some other platform, modify the ESPHome config to fullfill your needs.

Note: remove `api: ` line from config, as otherwise it will reboot the device every 15 minutes when there is no Home Assistant connection.

## Modifying ESPHome config

The [config file](https://github.com/smartavan/smartavan-heater-controller/blob/main/smartavan-heater-controller.yaml) contains everything needed for the operation.

File is currently somewhat commented, most of the settings should be self-explanatory.

In case you want to change the settings, you have few options:
1. [Install ESPHome manually](https://esphome.io/guides/installing_esphome.html) on your workstation and then run `esphome run smartavan-heater-controller.yaml` and it will build&upload new firmware to device
2. Install ESPHome Add-On to your Home Assistant OS instance and modify&upload firmware from there

For uploading the firmware, Smartavan Heater Controller can be connected either with WiFi or USB connection.