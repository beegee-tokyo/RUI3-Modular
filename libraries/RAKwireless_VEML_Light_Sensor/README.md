| <center><img src="./assets/rakstar.jpg" alt="RAKstar" width=25%></center>  | ![RAKWireless](./assets/RAK-Whirls.png) | [![Build Status](https://github.com/RAKWireless/RAK12010-VEML7700-Library/workflows/RAK%20Library%20Build%20CI/badge.svg)](https://github.com/RAKWireless/RAK12010-VEML7700-Library/actions) |
| -- | -- | -- |

# RAK12010-VEML7700-Library

RAKwireless Arduino Library for the RAK12010 Ambient Light sensor.

VEML7700 is a high-accuracy ambient light digital sensor with a 16-bit resolution. It includes a high sensitive photo diode, a low noise amplifier, a 16-bit A/D converter and supports an easy-to-use I2C bus communication interface (I2C address: `0x10`).

# Documentation

* **[Product Repository](https://github.com/RAKWireless/RAK12010-VEML7700-Library)** - Product repository for the RAKWireless RAK12010 ambient light light sensor.
* **[Documentation](https://docs.rakwireless.com/Product-Categories/WisBlock/RAK12010/Quickstart/)** - Documentation and Quick Start Guide for the RAK12010 ambient light light sensor.

## INSTALLATION

### Arduino IDE

In Arduino IDE open `Sketch->Include Library->Manage Libraries` then search for RAK12010.

![ManageLibraries](assets/ManageLibraries.png)

![SearchResult](assets/SearchResult.png)

You can also install it manually:

* Method 1: download the archive, unzip it and place the RAK12010-VEML7700-Library folder into the library directory.

* Method 2: In the terminal, if you have git installed, go to the libraries folder and do:

```bash
git clone https://github.com/RAKWireless/RAK12010-VEML7700-Library
```

You should get an output similar to this:

```bash
Cloning into 'RAK12010-VEML7700-Library'...
remote: Enumerating objects: 20, done.
remote: Counting objects: 100% (20/20), done.
remote: Compressing objects: 100% (15/15), done.
remote: Total 20 (delta 0), reused 14 (delta 0), pack-reused 0
Receiving objects: 100% (20/20), 263.40 KiB | 500.00 KiB/s, done.
```

### PlatformIO

In PlatformIO, open PlatformIO Home, switch to libraries and search for RAK12010. Or install the library project dependencies by adding the following into `platformio.ini`:

```
lib_deps =
  rakwireless/RAKwireless VEML7700 ambient light light sensor
```

You can also install it manually:

Download the archive, unzip it and place the RAK12010-VEML7700-Library folder into the library directory: in PlatformIO this is usually in `<user/.platformio/lib>`.

# Usage

The library provides a `Light_VEML7700` class, which allows communication to the RAK12010 UV light sensor. Check out the [examples](https://github.com/RAKWireless/RAK12010-VEML7700-Library/tree/main/examples/VEML7700) on how to use the library.

## This class provides the following methods:

* `bool begin(TwoWire *theWire = &Wire)`

Constructor: Sets up the hardware for talking to the VEML7700.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        | theWire | (optional) pointer to an I2C interface |
| return    |  | True if initialization was successful, otherwise false. |

* `uint8_t enable(bool enable)`

Enables or disables the sensor.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        | enable | The flag to enable/disable |
| return    |  | status |

* `uint8_t interruptEnable(bool enable)`

Enables or disables the interrupt.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        | enable | The flag to enable/disable |
| return    |  | status |

* `uint8_t setPersistence(uint8_t pers)`

Set the ALS IRQ setting.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        | pers | Persistance constant, can be VEML7700_PERS_1, VEML7700_PERS_2, VEML7700_PERS_4 or VEML7700_PERS_8 |
| return    |  | status |

* `uint8_t setIntegrationTime(uint8_t it)`

Sets the ALS integration time.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        | it | Can be VEML7700_IT_100MS, VEML7700_IT_200MS, VEML7700_IT_400MS, VEML7700_IT_800MS, VEML7700_IT_50MS or VEML7700_IT_25MS |
| return    |  | status |

* `uint8_t getIntegrationTime(void)`

Gets the ALS integration time.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        |  |  |
| return    |  | index, can be VEML7700_IT_100MS, VEML7700_IT_200MS, VEML7700_IT_400MS, VEML7700_IT_800MS, VEML7700_IT_50MS or VEML7700_IT_25MS |

* `uint8_t setGain(uint8_t gain)`

Sets the ALS gain.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        | gain | Can be VEML7700_GAIN_1, VEML7700_GAIN_2, VEML7700_GAIN_1_8 or VEML7700_GAIN_1_4 |
| return    |  | status |

* `uint8_t getGain(void)`

Gets the ALS gain.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        |  |  |
| return    |  | index, can be VEML7700_GAIN_1, VEML7700_GAIN_2, VEML7700_GAIN_1_8 or VEML7700_GAIN_1_4 |

* `uint8_t powerSaveEnable(bool enable)`

Enables power save mode

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        | enable | True if power save should be enabled |
| return    |  | status |

* `uint8_t setPowerSaveMode(uint8_t mode)`

Assigns the power save register data.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        | mode | The 16-bit data to write to VEML7700_ALS_POWER_SAVE |
| return    |  | status |

* `uint8_t getPowerSaveMode(void)`

Retrieves the power save register data.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        |  |  |
| return    |  | 16-bit data from VEML7700_ALS_POWER_SAVE |

* `uint8_t setLowThreshold(uint16_t value)`

Assigns the low threshold register data.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        | mode | The 16-bit data to write to VEML7700_ALS_POWER_SAVE |
| return    |  | status |

* `uint16_t getLowThreshold(void)`

Retrieves the low threshold register data.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        |  |  |
| return    |  | 16-bit data from VEML7700_ALS_THREHOLD_LOW |

* `uint8_t setHighThreshold(uint16_t value)`

Assigns the high threshold register data.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        | value | The 16-bit data to write to VEML7700_ALS_THREHOLD_HIGH |
| return    |  | status |

* `uint16_t getHighThreshold(void)`

Retrieves the high threshold register data.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        |  |  |
| return    |  | 16-bit data from VEML7700_ALS_THREHOLD_HIGH |

* `uint16_t interruptStatus(void)`

Retrieves the interrupt status register data.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        |  |  |
| return    |  | 16-bit data from VEML7700_INTERRUPTSTATUS |

* `float readLux()`

Reads the calibrated lux value.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        |  |  |
| return    |  | Floating point Lux data (ALS multiplied by 0.0576) |

* `float readLuxNormalized()`

Reads the lux value with correction for non-linearity at high-lux settings.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        |  |  |
| return    |  | Floating point Lux data (ALS multiplied by 0.0576 and corrected for high-lux settings) |

* `uint16_t readALS()`

Reads the raw ALS data.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        |  |  |
| return    |  | 16-bit data value from the ALS register |

* `float readWhite()`

Reads the white light data.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        |  |  |
| return    |  | Floating point 'white light' data multiplied by 0.0576 |

* `float readWhiteNormalized()`

Reads the 'white light' value with correction for non-linearity at high-lux settings.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        |  |  |
| return    |  | Floating point 'white light' data multiplied by 0.0576 and corrected for high-lux settings |

* `float normalize_resolution(float value)`

Chooses a different resolution.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        | value | New resolution |
| return    |  | Status_OK or STATUS_ERROR |

* `uint8_t GetAutoLux(float& lux)`

Adjusts gain and integration times to adjust to different light situations.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        |  |  |
| return    | lux | STATUS_ERROR or STATUS_OK |

* `void sampleDelay(void)`

Extends nominal delay to ensure a new sample is generated.

* `uint8_t sendData(uint8_t command, uint16_t data = 0)`

Sends I2C data.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        | command | command |
| in        | data | data to be sent |
| return    |  | Status_OK or STATUS_ERROR |

* `uint8_t receiveData(uint8_t command, uint16_t& data)`

Receives I2C data.

Parameters:

| Direction | Name | Function | 
| --------- | ---- | -------- |
| in        | command | command |
| in        | data | data to be received |
| return    |  | Status_OK or STATUS_ERROR |

![Lux](assets/Lux.png)
