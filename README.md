# muzio26
Arduino based VU meter

# History
* This code is a spinoff of great contribution done by [Cine-Lights](https://www.youtube.com/channel/UCOG6Bi2kvpDa1c8gHWZI5CQ) 
* It has been tuned to fit [Muzio26 packeg](https://www.kickstarter.com/projects/1936020118/muzio-music-visualization-animated/description), a nawesome VU metter based on top of CineLights code.
* But it can re-used for any setup with an arduino and a LED strip.


# Difference with Cine-Lights version
* Add a visual indicator to show which pattern has been selected
* NeoPixel has been removed to leverage only on [FastLED](http://fastled.io/) (only one framework to learn)
* Source code has been re-arranged, one VU pattern into one header
* Adding some struct array to easily add / remove  pattern
* Optionnaly print a nice pattern name on Serial.

# TODO
* Some cleaning in gloable variable
* Add other pattern
* Make sure it works on ESP8266 / ESP32 / Teensy
* Add other Fx.
* Add line in

# VS Code
* The project is build with Visual Studio Code and PlatformIO extension
* Have a look to *platformio.ini* to change targeted board and USB port 

# Arduino IDE
* I switch from ArduinoIDE to VSCode 'cause when your project is growing up Arduino IDE still too basic.
* Anyway it should remains compatible with Arduino IDE:
  * put all fils in same directory
  * rename *muzio26.cpp* to *muzio26.ino*
  * Then it should work


