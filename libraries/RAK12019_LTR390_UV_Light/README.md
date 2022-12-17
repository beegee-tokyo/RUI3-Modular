| <center><img src="./assets/rakstar.jpg" alt="RAKstar" width=25%></center>  | ![RAKWireless](./assets/RAK-Whirls.png) | [![Build Status](https://github.com/RAKWireless/RAK12019_LTR390/workflows/RAK%20Library%20Build%20CI/badge.svg)](https://github.com/RAKWireless/RAK12019_LTR390/actions) |
| -- | -- | -- |

# Library for WisBlock Sensor RAK12019 LTR-390UV-01 Optical Sensor

The LTR-390UV-01 is an integrated low-voltage I2C ambient light sensor and ultraviolet light sensor in a single lead-free surface mount package. This sensor converts light intensity to a digital output signal capable of direct I2C interface. It provides a linear ALS response over a wide dynamic range, and is well suited to applications under high ambient brightness.

The sensor has a programmable interrupt with hysteresis to response to events. This removes the need to poll the sensor for a reading, which improves system efficiency. This CMOS design and factory-set one-time trimming capability ensure minimal sensor-to-sensor variations for ease of manufacturability to the end customers.

_**See licence information in [License](#license)**_

# Documentation

* **[Product Repository](https://github.com/RAKWireless/RAK12019_LTR390)** - Product repository for the RAKWireless RAK12019 Optical Sensor.
* **[Documentation](https://docs.rakwireless.com/Product-Categories/WisBlock/RAK12019/Quickstart/)** - Documentation and Quick Start Guide for the RAK12019 Optical Sensor.

## INSTALLATION

### Arduino IDE

In Arduino IDE open `Sketch->Include Library->Manage Libraries` then search for RAK12019.

![ManageLibraries](assets/ManageLibraries.png)

![SearchResult](assets/SearchResult.png)

You can also install it manually:

* Method 1: download the archive, unzip it and place the RAK12019_LTR390 folder into the library directory.

* Method 2: In the terminal, if you have git installed, go to the libraries folder and do:

```bash
git clone https://github.com/RAKWireless/RAK12019_LTR390
```

You should get an output similar to this:

```bash
Cloning into 'RAK12019_LTR390'...
remote: Enumerating objects: 20, done.
remote: Counting objects: 100% (20/20), done.
remote: Compressing objects: 100% (15/15), done.
remote: Total 20 (delta 0), reused 14 (delta 0), pack-reused 0
Receiving objects: 100% (20/20), 263.40 KiB | 500.00 KiB/s, done.
```

### PlatformIO

In PlatformIO, open PlatformIO Home, switch to libraries and search for RAK12019. Or install the library project dependencies by adding the following into `platformio.ini`:

```
lib_deps =
  rakwireless/RAK12019_LTR390
```

You can also install it manually:

Download the archive, unzip it and place the RAK12019-LTR390-Library folder into the library directory: in PlatformIO this is usually in `<user/.platformio/lib>`.

## BASICS

### Init

The I2C address is `0x53` as defined in the header file:

```c
#define LTR390_ADDRESS 0x53
```

As mentioned aboved, it has two modes: ambient light sensor (ALS) and ultraviolet light sensor (UVS). These two modes are defined in the `ltr390_mode_t` enum, and passed to the `void UVlight_LTR390::setMode(ltr390_mode_t mode)` command:

```c
typedef enum {
  LTR390_MODE_ALS,
  LTR390_MODE_UVS,
} ltr390_mode_t;
```

The module uses `WB_IO2` to power up and is conflicting with INT1, so it's better to use it in Slot C and Slot D. So your turn on the module with:

```c
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
```

Then, initializing the module is simple enough. Given a `UVlight_LTR390` object called `ltr`, all you have to do is this:

```c
UVlight_LTR390 ltr = UVlight_LTR390();

[...]

  if (! ltr.init()) {
    Serial.println("Couldn't find LTR sensor!");
    while (1) delay(10);
  }
  Serial.println("Found LTR390 sensor!");
  // if set to LTR390_MODE_ALS, get ambient light data; if set to LTR390_MODE_UVS, get ultraviolet light data.
  ltr.setMode(LTR390_MODE_ALS);//LTR390_MODE_UVS
```

You then need to set the gain and resolution:

```c
  ltr.setGain(LTR390_GAIN_3);
  ltr.setResolution(LTR390_RESOLUTION_16BIT);
```

Options for the gain are:

```c
typedef enum {
  LTR390_GAIN_1 = 0,
  LTR390_GAIN_3,
  LTR390_GAIN_6,
  LTR390_GAIN_9,
  LTR390_GAIN_18,
} ltr390_gain_t;
```

And for the resolution:

```c
typedef enum {
  LTR390_RESOLUTION_20BIT,
  LTR390_RESOLUTION_19BIT,
  LTR390_RESOLUTION_18BIT,
  LTR390_RESOLUTION_17BIT,
  LTR390_RESOLUTION_16BIT,
  LTR390_RESOLUTION_13BIT,
} ltr390_resolution_t;
```

Finally, you need to set the lower and upper interrupt output thresholds, and configure the interrupt based on the thresholds.

```c
  ltr.setThresholds(100, 1000);
  if (ltr.getMode() == LTR390_MODE_ALS) {
    ltr.configInterrupt(true, LTR390_MODE_ALS);
  } else {
    ltr.configInterrupt(true, LTR390_MODE_UVS);
  }
```

### Data collection

You need an array of 8 unsigned bytes to collect the data, `static uint8_t lightdata[8] = {0}`. In [the RAK12019_UVlight_LTR390_BLE example](examples/RAK4631/RAK12019_UVlight_LTR390_BLE/RAK12019_UVlight_LTR390_BLE.ino), for instance, there is a `void UVlight_Ltr390_GetData()` command that fills the array based on the selected mode.

```c
void UVlight_Ltr390_GetData(void) {
  if (ltr.getMode() == LTR390_MODE_ALS) {
    uint32_t sendlux = 0;
    uint32_t sendals = 0;
    uint8_t count = 0;
    ALS = ltr.readALS();
    LUX = ltr.getLUX();
    sendlux = LUX * 100;
    sendals = ALS ;
    data = "Lux = " + String(LUX) + " " + "sendals=" + String(sendals) + " ";
    Serial.println(data);
    data = "";
    lightdata[count++] = (uint8_t)((sendlux & 0xFF000000) >> 24);
    lightdata[count++] = (uint8_t)((sendlux & 0x00FF0000) >> 16);
    lightdata[count++] = (uint8_t)((sendlux & 0x0000FF00) >> 8);
    lightdata[count++] = (uint8_t)(sendlux & 0x000000FF);
    lightdata[count++] = (uint8_t)((sendals & 0xFF000000) >> 24);
    lightdata[count++] = (uint8_t)((sendals & 0x00FF0000) >> 16);
    lightdata[count++] = (uint8_t)((sendals & 0x0000FF00) >> 8);
    lightdata[count++] = (uint8_t)(sendals & 0x000000FF);
    ALS = 0;
    LUX = 0;
  } else {
    uint32_t senduvs = 0;
    uint32_t senduvi = 0;
    uint8_t count = 0;
    UVS = ltr.readUVS();
    UVI = ltr.getUVI(); //calculate the UVI
    senduvi = UVI * 100;
    senduvs = UVS ;
    data = "UVI = " + String(UVI) + " " + " UVS=" + String(senduvs) + " ";
    Serial.println(data);
    data = "";
    lightdata[count++] = (uint8_t)((senduvi & 0xFF000000) >> 24);
    lightdata[count++] = (uint8_t)((senduvi & 0x00FF0000) >> 16);
    lightdata[count++] = (uint8_t)((senduvi & 0x0000FF00) >> 8);
    lightdata[count++] = (uint8_t)(senduvi & 0x000000FF);
    lightdata[count++] = (uint8_t)((senduvs & 0xFF000000) >> 24);
    lightdata[count++] = (uint8_t)((senduvs & 0x00FF0000) >> 16);
    lightdata[count++] = (uint8_t)((senduvs & 0x0000FF00) >> 8);
    lightdata[count++] = (uint8_t)(senduvs & 0x000000FF);
    UVS = 0;
    LUX = 0;
  }
}
```

This example uses BLE's GATT Characteristic and Object Type `0x2A76`, "UV Index", aka `UUID16_CHR_UV_INDEX`, which depends on the `UUID16_SVC_ENVIRONMENTAL_SENSING` BLE Service:

```c
BLEService envms = BLEService(UUID16_SVC_ENVIRONMENTAL_SENSING);
BLECharacteristic environment_UVlight = BLECharacteristic(UUID16_CHR_UV_INDEX);
```

So quite conveniently, all you have to do is send the data with `environment_UVlight.notify(lightdata, 8);`. Adafruit's Bluefruit app will pick up the data and display it on your phone.

***MAYBE ADD A SCREENSHOT***

## Functions

* `UVlight_LTR390()`;
* `UVlight_LTR390(TwoWire *w)`;
* `UVlight_LTR390(int addr)`;
* `UVlight_LTR390(TwoWire *w, int addr)`;
  Constructor
  
* `bool init()`;
  Initialization. Returns true on success, or false.

* `bool reset(void)`;
  Performs a soft reset with a 10-ms delay. Returns true on success, or false.

* `void enable(bool en)`;
  Enables or disables the light sensor.

* `bool enabled(void)`;
  Reads the enabled-bit from the sensor.

* `void setMode(ltr390_mode_t mode)`;
  Sets the sensor mode to either ambient (`LTR390_MODE_ALS`) or UV (`LTR390_MODE_UVS`).

* `ltr390_mode_t getMode(void)`;
  Gets the current mode: `LTR390_MODE_UVS` or `LTR390_MODE_ALS`.

* `void setGain(ltr390_gain_t gain)`;
  Sets the sensor gain. See `ltr390_gain_t`.

* `ltr390_gain_t getGain(void)`;
  Gets the current gain.

* `void setResolution(ltr390_resolution_t res)`;
  Sets the sensor resolution. Note: higher resolutions take longer to read. See `ltr390_resolution_t`.

* `ltr390_resolution_t getResolution(void)`;
  Gets the sensor resolution.

* `void setThresholds(uint32_t lower, uint32_t higher)`;
  Sets the lower and upper interrupt output threshold ranges. When the sensor is below the lower threshold, or above the upper threshold, interrupt will fire.

* `void configInterrupt(bool enable, ltr390_mode_t source, uint8_t persistance = 0)`;
  Configures the interrupt based on the thresholds in `setThresholds()`. When the sensor is below the lower threshold, or above the upper threshold, interrupt will fire.

* `bool newDataAvailable(void)`;
  Checks whether new data is available in the data register.

* `uint32_t readUVS(void)`;
  Reads 3 bytes out of UV data register, but does not check if data is new.

* `uint32_t readALS(void)`;
  Reads 3 bytes out of ambient data register, but does not check if data is new.

* `float getLUX(void)`;
  Gets lux data. Returns the ambient light data in lux.

* `float getUVI(void)`;
  Gets UVI data. Returns the ultraviolet light data in uw/cm2.

* `uint8_t writeRegister(uint8_t reg, uint8_t data)`;
  Writes one byte to a register.

* `uint8_t readRegister(uint8_t reg)`;
  Writes a register's value.

# License

This code is partly based on the [Adafruit_LTR390 library](https://github.com/adafruit/Adafruit_LTR390) and following their requirements, here is the Adafruit README file:

Adafruit_LTR390 [![Build Status](https://github.com/adafruit/Adafruit_LTR390/workflows/Arduino%20Library%20CI/badge.svg)](https://github.com/adafruit/Adafruit_LTR390/actions)/[![Documentation](https://github.com/adafruit/ci-arduino/blob/master/assets/doxygen_badge.svg)](http://adafruit.github.io/Adafruit_LTR390/html/index.html)
================

This is the Adafruit LTR390 UV sensor library

Tested and works great with the [Adafruit LTR390 Breakout Board](https://www.adafruit.com/product/4831)

[<img src="assets/board.png?raw=true" width="500px">](https://www.adafruit.com/products/4831)

This chip uses I2C to communicate, 2 pins are required to interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

# Installation
To install, use the Arduino Library Manager and search for "Adafruit LTR390" and install the library.

# Dependencies
* [Adafruit_BusIO](https://github.com/adafruit/Adafruit_BusIO)

# Contributing

Contributions are welcome! Please read our [Code of Conduct](https://github.com/adafruit/Adafruit_LTR390/blob/master/CODE_OF_CONDUCT.md>)
before contributing to help this project stay welcoming.

## Documentation and doxygen
Documentation is produced by doxygen. Contributions should include documentation for any new code added.

Some examples of how to use doxygen can be found in these guide pages:

https://learn.adafruit.com/the-well-automated-arduino-library/doxygen

https://learn.adafruit.com/the-well-automated-arduino-library/doxygen-tips

## Formatting and clang-format
This library uses [`clang-format`](https://releases.llvm.org/download.html) to standardize the formatting of `.cpp` and `.h` files.
Contributions should be formatted using `clang-format`:

The `-i` flag will make the changes to the file.
```bash
clang-format -i *.cpp *.h
```
If you prefer to make the changes yourself, running `clang-format` without the `-i` flag will print out a formatted version of the file. You can save this to a file and diff it against the original to see the changes.

Note that the formatting output by `clang-format` is what the automated formatting checker will expect. Any diffs from this formatting will result in a failed build until they are addressed. Using the `-i` flag is highly recommended.

### clang-format resources
  * [Binary builds and source available on the LLVM downloads page](https://releases.llvm.org/download.html)
  * [Documentation and IDE integration](https://clang.llvm.org/docs/ClangFormat.html)

## About this Driver
Written by Limor Fried for Adafruit Industries.  
BSD license, check license.txt for more information
All text above must be included in any redistribution
