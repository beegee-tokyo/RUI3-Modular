#ifndef _LIGHT_VEML7700_H
#define _LIGHT_VEML7700_H

#include "Arduino.h"
#include <Wire.h>

#define VEML7700_I2CADDR_DEFAULT 0x10 ///< I2C address
#define VEML7700_ALS_CONFIG 0x00        ///< Light configuration register
#define VEML7700_ALS_THREHOLD_HIGH 0x01 ///< Light high threshold for irq
#define VEML7700_ALS_THREHOLD_LOW 0x02  ///< Light low threshold for irq
#define VEML7700_ALS_POWER_SAVE 0x03    ///< Power save regiester
#define VEML7700_ALS_DATA 0x04          ///< The light data output
#define VEML7700_WHITE_DATA 0x05        ///< The white light data output
#define VEML7700_INTERRUPTSTATUS 0x06   ///< What IRQ (if any)

#define VEML7700_INTERRUPT_HIGH 0x4000 ///< Interrupt status for high threshold
#define VEML7700_INTERRUPT_LOW 0x8000  ///< Interrupt status for low threshold

#define VEML7700_GAIN_1 0x00   ///< ALS gain 1x
#define VEML7700_GAIN_2 0x01   ///< ALS gain 2x
#define VEML7700_GAIN_1_8 0x02 ///< ALS gain 1/8x
#define VEML7700_GAIN_1_4 0x03 ///< ALS gain 1/4x

#define VEML7700_IT_100MS 0x00 ///< ALS intetgration time 100ms
#define VEML7700_IT_200MS 0x01 ///< ALS intetgration time 200ms
#define VEML7700_IT_400MS 0x02 ///< ALS intetgration time 400ms
#define VEML7700_IT_800MS 0x03 ///< ALS intetgration time 800ms
#define VEML7700_IT_50MS 0x08  ///< ALS intetgration time 50ms
#define VEML7700_IT_25MS 0x0C  ///< ALS intetgration time 25ms

#define VEML7700_PERS_1 0x00 ///< ALS irq persisance 1 sample
#define VEML7700_PERS_2 0x01 ///< ALS irq persisance 2 samples
#define VEML7700_PERS_4 0x02 ///< ALS irq persisance 4 samples
#define VEML7700_PERS_8 0x03 ///< ALS irq persisance 8 samples

#define VEML7700_POWERSAVE_MODE1 0x00 ///< Power saving mode 1
#define VEML7700_POWERSAVE_MODE2 0x01 ///< Power saving mode 2
#define VEML7700_POWERSAVE_MODE3 0x02 ///< Power saving mode 3
#define VEML7700_POWERSAVE_MODE4 0x03 ///< Power saving mode 4

/*!
      @brief  Class that stores state and functions for interacting with
              VEML7700 Temp Sensor
*/
class Light_VEML7700 {
  public:
    Light_VEML7700();
    bool begin(TwoWire *theWire = &Wire);
    uint8_t enable(bool enable);
    uint8_t interruptEnable(bool enable);
    uint8_t setPersistence(uint8_t pers);
    uint8_t setIntegrationTime(uint8_t it);
    uint8_t getIntegrationTime(void);
    uint8_t setGain(uint8_t gain);
    uint8_t getGain(void);

    uint8_t powerSaveEnable(bool enable);
    uint8_t setPowerSaveMode(uint8_t mode);
    uint8_t getPowerSaveMode(void);

    uint8_t setLowThreshold(uint16_t value);
    uint16_t getLowThreshold(void);
    uint8_t setHighThreshold(uint16_t value);
    uint16_t getHighThreshold(void);
    uint16_t interruptStatus(void);

    float readLux();
    float readLuxNormalized();
    uint16_t readALS();
    float readWhite();
    float readWhiteNormalized();
    float normalize_resolution(float value);
    uint8_t GetAutoLux(float& lux);
    void sampleDelay(void);
    uint8_t sendData(uint8_t command, uint16_t data = 0);
    uint8_t receiveData(uint8_t command, uint16_t& data);
    enum { STATUS_OK = 0, STATUS_ERROR = 0xff };
    enum { I2C_ADDRESS = 0x10 };
    uint8_t gains[4] = {
      VEML7700_GAIN_1_8,
      VEML7700_GAIN_1_4,
      VEML7700_GAIN_1,
      VEML7700_GAIN_2
    };
    int8_t itimes[6] = {
      VEML7700_IT_25MS,
      VEML7700_IT_50MS,
      VEML7700_IT_100MS,
      VEML7700_IT_200MS,
      VEML7700_IT_400MS,
      VEML7700_IT_800MS
    };
  private:
    typedef uint8_t (Light_VEML7700::*getCountsFunction)(uint16_t& counts);
    enum { COMMAND_ALS_SM = 0x00, ALS_SM_MASK = 0x1800, ALS_SM_SHIFT = 11 };
    enum { COMMAND_ALS_IT = 0x00, ALS_IT_MASK = 0x03c0, ALS_IT_SHIFT = 6 };
    enum { COMMAND_ALS_PERS = 0x00, ALS_PERS_MASK = 0x0030, ALS_PERS_SHIFT = 4 };
    enum { COMMAND_ALS_INT_EN = 0x00, ALS_INT_EN_MASK = 0x0002,
           ALS_INT_EN_SHIFT = 1
         };
    enum { COMMAND_ALS_SD = 0x00,  ALS_SD_MASK = 0x0001, ALS_SD_SHIFT = 0 };
    enum { COMMAND_ALS_WH = 0x01 };
    enum { COMMAND_ALS_WL = 0x02 };
    enum { COMMAND_PSM = 0x03, PSM_MASK = 0x0006, PSM_SHIFT = 1 };
    enum { COMMAND_PSM_EN = 0x03, PSM_EN_MASK = 0x0001, PSM_EN_SHIFT = 0 };
    enum { COMMAND_ALS = 0x04 };
    enum { COMMAND_WHITE = 0x05 };
    enum { COMMAND_ALS_IF_L = 0x06, ALS_IF_L_MASK = 0x8000, ALS_IF_L_SHIFT = 15 };
    enum { COMMAND_ALS_IF_H = 0x06, ALS_IF_H_MASK = 0x4000, ALS_IF_H_SHIFT = 14 };
    uint16_t register_cache[4];
};
#endif
