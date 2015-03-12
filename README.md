# Raspi-Rollo
Raspberry PI controll of 433MHz roller shutters from Acomax, Rohrmotor24 &amp; Alusel

Webfrontend Python based with a rcswitch-pi c++ backend for sending the codes.
Arduino sketch for finding the codes from your remote. Thanks to IngTimo from Udo's Blog http://physudo.blogspot.de/2013/08/home-automation-mit-dem-arduino-und-433_17.html

You need
- RaspberryPi with Raspian and wiringPi installed
- Python installed with flask (pip install flask)
- 433 MHz sender and receiver
- Arduino Nano or other for reading your remote
