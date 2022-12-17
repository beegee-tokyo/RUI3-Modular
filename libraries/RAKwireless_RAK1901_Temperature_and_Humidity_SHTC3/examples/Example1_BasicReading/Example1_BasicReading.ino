#include "rak1901.h"

rak1901 rak1901;

int loopCounter = 0;

void setup()
{
    // begin and set baudrate for Serial
    Serial.begin(115200);//UART0 baudrate 115200

    // begin for I2C
    Wire.begin();

    // check if snesor Rak1901 is work
    Serial.printf("RAK1901 init %s\r\n", rak1901.init() ? "Success" : "Fail");
}

void loop()
{
    Serial.printf("===============timer:%d===============\r\n", loopCounter);

    //Check if sensor Rak1901 update data is work
    //And print the data
    if (rak1901.update()) {
        Serial.printf("Temperature = %.2f。C\r\n", rak1901.temperature());
        Serial.printf("Humidity = %.2f%%\r\n", rak1901.humidity());
    } else {
        Serial.println("Please plug in the sensor RAK1901 and Reboot");
    }
    
    loopCounter++;
    delay(5000);
}
