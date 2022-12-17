#include "Arduino.h"
#include <Wire.h>

#include "Light_VEML7700.h"

/*!
      @brief  Instantiates a new VEML7700 class
*/
Light_VEML7700::Light_VEML7700(void) {}

/*!
      @brief  Setups the hardware for talking to the VEML7700
      @param  theWire An optional pointer to an I2C interface
      @return True if initialization was successful, otherwise false.
*/
bool Light_VEML7700::begin(TwoWire *theWire) {
  Wire.begin();
  // write initial state to VEML7700
  register_cache[0] = ( (uint16_t(VEML7700_GAIN_1) << ALS_SM_SHIFT) |
                        (uint16_t(VEML7700_IT_100MS) << ALS_IT_SHIFT) |
                        (uint16_t(VEML7700_GAIN_1) << ALS_PERS_SHIFT) |
                        (uint16_t(0) << ALS_INT_EN_SHIFT) |
                        (uint16_t(0) << ALS_SD_SHIFT) );
  register_cache[1] = 0x0000;
  register_cache[2] = 0xffff;
  register_cache[3] = ( (uint16_t(VEML7700_POWERSAVE_MODE3) << PSM_SHIFT) |
                        (uint16_t(0) << PSM_EN_SHIFT) );
  for (uint8_t i = 0; i < 4; i++) {
    if (sendData(i, register_cache[i])) //send successfully
    {
      return false;
    }
  }
  // wait at least 2.5ms as per datasheet
  delay(3);
  return true;
}

/*!
      @brief Enable or disable the sensor
      @param enable The flag to enable/disable
*/
uint8_t Light_VEML7700::enable(bool enable)
{
  uint8_t rData;
  if (enable) {
    rData = 1;
  }
  else {
    rData = 0;
  }
  uint16_t reg = ( (register_cache[COMMAND_ALS_SD] & ~ALS_SD_MASK) |
                   ((uint16_t(~rData) << ALS_SD_SHIFT) & ALS_SD_MASK) );
  register_cache[COMMAND_ALS_SD] = reg;
  uint8_t status = sendData(COMMAND_ALS_SD, reg);
  if (rData) {
    delay(3); // minimu 2.5us delay per datasheet
  }
  return status;
}

/*!
      @brief Enable or disable the interrupt
      @param enable The flag to enable/disable
*/
uint8_t Light_VEML7700::interruptEnable(bool enable) {
  uint8_t interruptData;
  if (enable) {
    interruptData = 1;
  }
  else {
    interruptData = 0;
  }
  uint16_t reg = ( (register_cache[COMMAND_ALS_INT_EN] & ~ALS_INT_EN_MASK) |
                   ((uint16_t(interruptData) << ALS_INT_EN_SHIFT) &
                    ALS_INT_EN_MASK) );
  register_cache[COMMAND_ALS_INT_EN] = reg;
  return sendData(COMMAND_ALS_INT_EN, reg);
}

/*!
      @brief Set the ALS IRQ
  setting
      @param pers Persistance constant, can be VEML7700_PERS_1, VEML7700_PERS_2,
      VEML7700_PERS_4 or VEML7700_PERS_8
*/
uint8_t Light_VEML7700::setPersistence(uint8_t pers) {
  uint16_t reg = ( (register_cache[COMMAND_ALS_PERS] & ~ALS_PERS_MASK) |
                   ((uint16_t(pers) << ALS_PERS_SHIFT) & ALS_PERS_MASK) );
  register_cache[COMMAND_ALS_PERS] = reg;
  return sendData(COMMAND_ALS_PERS, reg);
}

/*!
      @brief Set ALS integration time
      @param it Can be VEML7700_IT_100MS, VEML7700_IT_200MS, VEML7700_IT_400MS,
      VEML7700_IT_800MS, VEML7700_IT_50MS or VEML7700_IT_25MS
*/
uint8_t Light_VEML7700::setIntegrationTime(uint8_t it) {
  uint16_t reg = ( (register_cache[COMMAND_ALS_IT] & ~ALS_IT_MASK) |
                   ((uint16_t(it) << ALS_IT_SHIFT) & ALS_IT_MASK) );
  register_cache[COMMAND_ALS_IT] = reg;
  return sendData(COMMAND_ALS_IT, reg);
}

/*!
      @brief Get ALS integration time
      @returns IT index, can be VEML7700_IT_100MS, VEML7700_IT_200MS,
   VEML7700_IT_400MS, VEML7700_IT_800MS, VEML7700_IT_50MS or VEML7700_IT_25MS
*/
uint8_t Light_VEML7700::getIntegrationTime(void) {
  uint16_t GetTimeData = 0;
  if (receiveData(COMMAND_ALS_IT, GetTimeData))
  {
    return  0XFF;
  }
  return (uint8_t)(GetTimeData >> ALS_IT_SHIFT) & 0x0F;
}

/*!
      @brief Set ALS gain
      @param gain Can be VEML7700_GAIN_1, VEML7700_GAIN_2, VEML7700_GAIN_1_8 or
   VEML7700_GAIN_1_4
*/
uint8_t Light_VEML7700::setGain(uint8_t gain) {
  uint16_t reg = ( (register_cache[COMMAND_ALS_SM] & ~ALS_SM_MASK) |
                   ((uint16_t(gain) << ALS_SM_SHIFT) & ALS_SM_MASK) );
  register_cache[COMMAND_ALS_SM] = reg;
  return sendData(COMMAND_ALS_SM, reg);
}

/*!
      @brief Get ALS gain
      @returns Gain index, can be VEML7700_GAIN_1, VEML7700_GAIN_2,
   VEML7700_GAIN_1_8 or VEML7700_GAIN_1_4
*/
uint8_t Light_VEML7700::getGain(void) {
  uint16_t GetGainData = 0;
  if (receiveData(COMMAND_ALS_SM, GetGainData))
  {
    return  0XFF;
  }
  return (uint8_t)(GetGainData >> ALS_SM_SHIFT) & 0x0F;
}

/*!
      @brief Enable power save mode
      @param enable True if power save should be enabled
*/
uint8_t Light_VEML7700::powerSaveEnable(bool enable) {
  uint8_t PowerData;
  if (enable) {
    PowerData = 1;
  }
  else {
    PowerData = 0;
  }
  uint16_t reg = ( (register_cache[COMMAND_PSM_EN] & ~PSM_EN_MASK) |
                   ((uint16_t(PowerData) << PSM_EN_SHIFT) & PSM_EN_MASK) );
  register_cache[COMMAND_PSM_EN] = reg;
  return sendData(COMMAND_PSM_EN, reg);

}

/*!
      @brief Assign the power save register data
      @param mode The 16-bit data to write to VEML7700_ALS_POWER_SAVE
*/
uint8_t Light_VEML7700::setPowerSaveMode(uint8_t mode) {
  uint16_t reg = ( (register_cache[COMMAND_PSM] & ~PSM_MASK) |
                   ((uint16_t(mode) << PSM_SHIFT) & PSM_MASK) );
  register_cache[COMMAND_PSM] = reg;
  return sendData(COMMAND_PSM, reg);
}

/*!
      @brief  Retrieve the power save register data
      @return 16-bit data from VEML7700_ALS_POWER_SAVE
*/
uint8_t Light_VEML7700::getPowerSaveMode(void) {
  uint16_t getPowerSaveData = 0;
  if (receiveData(COMMAND_PSM, getPowerSaveData))
  {
    return  0XFF;
  }
  return (uint8_t)(getPowerSaveData >> PSM_SHIFT) & 0x0F;
}

/*!
      @brief Assign the low threshold register data
      @param value The 16-bit data to write to VEML7700_ALS_THREHOLD_LOW
*/
uint8_t Light_VEML7700::setLowThreshold(uint16_t value) {
  return sendData(COMMAND_ALS_WL, value);
}

/*!
      @brief  Retrieve the low threshold register data
      @return 16-bit data from VEML7700_ALS_THREHOLD_LOW
*/
uint16_t Light_VEML7700::getLowThreshold(void) {
  uint16_t getLowThresholdData = 0;
  if (receiveData(COMMAND_ALS_WL, getLowThresholdData))
  {
    return  0XFF;
  }
  return getLowThresholdData;
}

/*!
      @brief Assign the high threshold register data
      @param value The 16-bit data to write to VEML7700_ALS_THREHOLD_HIGH
*/
uint8_t Light_VEML7700::setHighThreshold(uint16_t value) {
  return sendData(COMMAND_ALS_WH, value);
}

/*!
      @brief  Retrieve the high threshold register data
      @return 16-bit data from VEML7700_ALS_THREHOLD_HIGH
*/
uint16_t Light_VEML7700::getHighThreshold(void) {
  uint16_t getHighThresholdData = 0;
  if (receiveData(COMMAND_ALS_WH, getHighThresholdData))
  {
    return  0XFF;
  }
}

/*!
      @brief  Retrieve the interrupt status register data
      @return 16-bit data from VEML7700_INTERRUPTSTATUS
*/
uint16_t Light_VEML7700::interruptStatus(void) {
  uint16_t interruptStatusData = 0;
  if (receiveData(COMMAND_ALS_IF_H, interruptStatusData))
  {
    return  0XFF;
  }
  return interruptStatusData;
}

/*!
      @brief  IIC send data
      @return Status_OK or STATUS_ERROR
*/
uint8_t Light_VEML7700::sendData(uint8_t command, uint16_t data)
{
  Wire.beginTransmission(I2C_ADDRESS);
  if (Wire.write(command) != 1) {
    return STATUS_ERROR;
  }
  if (Wire.write(uint8_t(data & 0xff)) != 1) {
    return STATUS_ERROR;
  }
  if (Wire.write(uint8_t(data >> 8)) != 1) {
    return STATUS_ERROR;
  }
  if (Wire.endTransmission()) {
    return STATUS_ERROR;
  }
  return STATUS_OK;
}

/*!
      @brief  IIC receive data
      @return Status_OK or STATUS_ERROR
*/
uint8_t Light_VEML7700::receiveData(uint8_t command, uint16_t& data)
{
  Wire.beginTransmission(I2C_ADDRESS);
  if (Wire.write(command) != 1) {
    return STATUS_ERROR;
  }
  if (Wire.endTransmission(false)) { // NB: don't send stop here
    return STATUS_ERROR;
  }
  if (Wire.requestFrom(uint8_t(I2C_ADDRESS), uint8_t(2)) != 2) {
    return STATUS_ERROR;
  }
  data = Wire.read();
  data |= uint16_t(Wire.read()) << 8;
  return STATUS_OK;
}


/*!
      @brief  choose different resolution
      @return Status_OK or STATUS_ERROR
*/
float Light_VEML7700::normalize_resolution(float value) {
  // adjust for gain (1x is normalized)
  switch (getGain()) {
    case VEML7700_GAIN_2:
      value /= 2.0;
      break;
    case VEML7700_GAIN_1_4:
      value *= 4;
      break;
    case VEML7700_GAIN_1_8:
      value *= 8;
      break;
  }
  // adjust for integrationtime (100ms is normalized)
  switch (getIntegrationTime()) {
    case VEML7700_IT_25MS:
      value *= 4;
      break;
    case VEML7700_IT_50MS:
      value *= 2;
      break;
    case VEML7700_IT_200MS:
      value /= 2.0;
      break;
    case VEML7700_IT_400MS:
      value /= 4.0;
      break;
    case VEML7700_IT_800MS:
      value /= 8.0;
      break;
  }
  return value;
}

/*!
      @brief Read the calibrated lux value. See app note lux table on page 5
      @returns Floating point Lux data (ALS multiplied by 0.0576)
*/
float Light_VEML7700::readLux() {
  uint16_t als = 0;
  if (receiveData(COMMAND_ALS, als))
  {
    return 0;
  }
  if ((getGain() == VEML7700_GAIN_1_8) &&
      (getIntegrationTime() == VEML7700_IT_25MS)) {
    float lux = normalize_resolution(als) * 0.0576;
    lux = 6.0135e-13 * pow(lux, 4) - 9.3924e-9 * pow(lux, 3) +
          8.1488e-5 * pow(lux, 2) + 1.0023 * lux;
    return lux;
  }
  else
  {
    return (normalize_resolution(als) * 0.0576); // see app note lux table on page 5
  }
}

/*!
      @brief Read the lux value with correction for non-linearity at high-lux
   settings
      @returns Floating point Lux data (ALS multiplied by 0.0576 and corrected
   for high-lux settings)
*/
float Light_VEML7700::readLuxNormalized() {
  float lux = readLux();
  // user-provided correction for non-linearities at high lux/white values:
  // https://forums.adafruit.com/viewtopic.php?f=19&t=152997&p=758582#p759346
  if ((getGain() == VEML7700_GAIN_1_8) &&
      (getIntegrationTime() == VEML7700_IT_25MS)) {
    lux = 6.0135e-13 * pow(lux, 4) - 9.3924e-9 * pow(lux, 3) +
          8.1488e-5 * pow(lux, 2) + 1.0023 * lux;
  }
  return lux;
}

/*!
      @brief Read the raw ALS data
      @returns 16-bit data value from the ALS register
*/
uint16_t Light_VEML7700::readALS() {
  uint16_t alsData = 0;
  if (receiveData(COMMAND_ALS, alsData))
  {
    return 0;
  }
  return alsData;
}

/*!
      @brief Read the white light data
      @returns Floating point 'white light' data multiplied by 0.0576
*/
float Light_VEML7700::readWhite() {
  uint16_t whiteData = 0;
  if (receiveData(COMMAND_WHITE, whiteData))
  {
    return 0;
  }
  return (normalize_resolution(whiteData) *0.0576); // see app note lux table on page 5
}

/*!
      @brief Read the 'white light' value with correction for non-linearity at
   high-lux settings
      @returns Floating point 'white light' data multiplied by 0.0576 and
   corrected for high-lux settings
*/
float Light_VEML7700::readWhiteNormalized() {
  float white = readWhite();
  // user-provided correction for non-linearities at high lux values:
  // https://forums.adafruit.com/viewtopic.php?f=19&t=152997&p=758582#p759346
  if ((getGain() == VEML7700_GAIN_1_8) &&
      (getIntegrationTime() == VEML7700_IT_25MS)) {
    white = 2E-15 * pow(white, 4) + 4E-12 * pow(white, 3) +
            9E-06 * pow(white, 2) + 1.0179 * white - 11.052;
  }
  return white;
}


/*!
      @brief  extend nominal delay to ensure new sample is generated
*/
void Light_VEML7700::sampleDelay(void) {
  // extend nominal delay to ensure new sample is generated
#define extended_delay(ms) delay(2*(ms))
  switch (getIntegrationTime()) {
    case VEML7700_IT_25MS:
      extended_delay(25);
      break;
    case VEML7700_IT_50MS:
      extended_delay(50);
      break;
    case VEML7700_IT_100MS:
      extended_delay(100);
      break;
    case VEML7700_IT_200MS:
      extended_delay(200);
      break;
    case VEML7700_IT_400MS:
      extended_delay(400);
      break;
    case VEML7700_IT_800MS:
      extended_delay(800);
      break;
    default:
      extended_delay(100);
      break;
  }
}

/*!
      @brief  adjust gain and integration times to adjust to different light situations
       @returns return STATUS_ERROR or STATUS_OK
*/
uint8_t Light_VEML7700::GetAutoLux(float& lux)
{
  int8_t itime_idx;
  uint8_t gain_idx;
  if (enable(false)) {
    return STATUS_ERROR;
  }
  for (itime_idx = 2; itime_idx < 6; itime_idx++) {
    if (setIntegrationTime(itimes[itime_idx])) {
      return STATUS_ERROR;
    }
    for (gain_idx = 0; gain_idx < 4; gain_idx++) {
      if (setGain(gains[gain_idx])) {
        return STATUS_ERROR;
      }
      if (enable(true)) {
        return STATUS_ERROR;
      }
      sampleDelay();
      if (readALS() >= 100) {
        do {
          if (readALS() < 10000) {
            lux = readLux();
            return STATUS_OK;
          }
          if (enable(false)) {
            return STATUS_ERROR;
          }
          itime_idx--;
          if (setIntegrationTime(itimes[itime_idx])) {
            return STATUS_ERROR;
          }
          if (enable(true)) {
            return STATUS_ERROR;
          }
          sampleDelay();
          // ALS = VMEL.readALS();
        } while (itime_idx > 0);
        lux = readLux();
        return STATUS_ERROR;
      }
      if (enable(false)) {
        return STATUS_ERROR;
      }
    }
  }
  lux = readLux();
  return STATUS_OK;
}
