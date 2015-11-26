Robot Wifi Revision 1
=====================

* ESP8266 (Huzzah board)

This package sets up an Access Point and waits for UDP datagrams from a client. Those
datagrams are sent out UART1 (mux with GPIO2). There is no RX for UART1, so we can
only send messages.

The intention is to connect GPIO2 to the RX of the Teensy LC controller of our Robot.
This allows us to send Robot Messages over UDP. Since the ESP8266 has the speed and
the timers, we should be able to control servos. That would remove the need for the
Teensy LC. Right now we are keeping it in favor of completing revision 1 even if it
isn't perfect.

* https://github.com/CuriousLLC/CuriousRobot - Teensy LC message controller

Build
=====

Obtain a copy of the ESP IoT SDK, version 1.3.0. Version 1.4.0 has some bug somewhere
that prevents SOFTAP mode from working. Switching to 1.3.0 works with the same code.

* https://github.com/espressif/ESP8266_RTOS_SDK

Obtain pfalcon's esp-open-sdk.

* https://github.com/pfalcon/esp-open-sdk

The Makefile will use the toolchain in the esp-open-sdk and look for the IOT sdk in
the esp_iot_sdk_v1.3.0 directory.

To write the binary to flash, I am using Arduino's packaged esptool. The Python
script times out on my Huzzah board, but the Arduino tool work each time.
