FOSDEM-MUSIC-BOX software for Arduino IDE 1.8.10

Notice that the chip comes pre-loaded and to play the demo sound you don't need to 
reprogram it - just touch the light sensor!

You need to install the Olimex package first, else you would encounter compilation issues.

Please do the following:

1) Navigate to Main Menu --> File --> Preferences

In "Additional Boards Managers IRLs" add our JSON link:

https://raw.githubusercontent.com/OLIMEX/Arduino_configurations/master/AVR/package_olimex_avr_index.json

2) Navigate to Main Menu --> Tools --> Board --> Boards Manager (if you want to filter the packages you can type in the search "Olimex")

Select Olimex AVR boards and then install (up to 2020/01/30 the latest version is 2.0.2)

3) Main Menu --> Tools --> Board --> Olimexino-85

4) Compile

5) Unplug the board

6) Upload

7) Plug the board to the USB

8) Wait until the program uploads and then few seconds to leave the bootloader mode (at the start of the program the red LED should blink once)

9) After the LED blinks the program will get some samples from the light sensor and then when it's dimmed a simple track will be played (by default it's short version of Mario bros theme).

10) You can change it by comment/uncomment different tracks within the loop function or create your own using the available ones in the "Tracks" folder as an example.

YYYY/MM/DD
2020/01/30
