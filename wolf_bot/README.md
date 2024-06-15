# TTGO
>The documentation for this chip is actually really terrible so anything that you find that is usefully throw in here

The Amazon comments have some helpful explanations: [link](https://www.amazon.com/HiLetgo-Display-Bluetooth-Internet-Development/dp/B07X1W16QS)



## Directory Structure
To allow us to test individual components of the code we can break them out into individual modules 

```
wolf_bot
├── Wolf_Bot (Master TTGO code)
│   ├── platformio.ini
├── IR (IR testing code)
│   ├── IR_rx (IR receiver testing)
│   │   ├── platformio.ini
│   ├── IR_tx (IR transmitter testing)
│   │   ├── platformio.ini
├── WiFi (WiFi/API testing code)
│   ├── platformio.ini
├── Desplay (LCD testing code)
│   ├── platformio.ini
├── README.md 
```

## PlatformIO project structure
```
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
```

The board is the `espressif ESP32 DEV Moduel` when creating the project

## PlatformIO Libraries
These are the libraries and dependencies for different functionalities

### T-display
```
lib_deps = 
    bodmer/TFT_eSPI@^2.4.76 ; Core library
    SPI
    SPIFFS
    FS
```
For now the display library is working by un-defining the `USER_SETUP_LOADED` definition in the `User_Setup_Select.h` file. This is a hacky solution but it works for now. 

Also had to comment out the default `user_setup.h` file, and uncomment the `Setup25_TTGO_T_Display.h` include.

The proper way would be to define these things in the platform.ini file but can't figure it out.

### IRremote
```
lib_deps = 
    Arduino-IRremote/Arduino-IRremote@3.9.0 ; IR remote library
```
## Pinout
![pic](https://m.media-amazon.com/images/I/61U7dm3G3ZL._AC_SL1010_.jpg)


## Resources
### Display drivers

Arduino supported: https://github.com/Bodmer/TFT_eSPI

LillyGO alternative: https://github.com/Xinyuan-LilyGO/TTGO-T-Display

### Documentation
https://f6czv.fr/en/documentation-on-esp32-and-the-ttgo-t-display

https://sites.google.com/site/jmaathuis/arduino/lilygo-ttgo-t-display-esp32

https://jonstephensonsblog.com/2019/12/06/using-the-ttgo-t-display-board/


### PIO CLI commands
```shell
> $pio run -t upload # look for port automatically
> $pio run -e esp32dev -t upload
> $pio device monitor
```

### NU-IoT Passwords
TTGO-1 : `vpxdxtnp`



