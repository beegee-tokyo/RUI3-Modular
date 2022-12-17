#include <Wire.h>
#include "LPS35HW.h"

LPS35HW lps;

void setup() {
    Serial.begin(9600);
    Serial.println("LPS barometer test");

#if defined(ESP8266)
    Wire.begin(SDA, SCL);
    Wire.setClock(400000);

    if (!lps.begin(&Wire)) {  // pass already began Wire
        Serial.println("Could not find a LPS barometer, check wiring!");
        while (1) {}
    }
#else
    if (!lps.begin()) {
        Serial.println("Could not find a LPS barometer, check wiring!");
        while (1) {}
    }
#endif

    lps.setLowPassFilter(LPS35HW::LowPassFilter_ODR9);  // filter last 9 samples, default off
    lps.setOutputRate(LPS35HW::OutputRate_1Hz);  // optional, default is 10Hz
    // lps.setLowPower(true);  // optional, default is off
}

void loop() {
    float pressure = lps.readPressure();  // hPa
    float temp = lps.readTemp();  // °C

    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.print("hPa\ttemperature: ");
    Serial.print(temp);
    Serial.println("*C\n");

    delay(1000);
}
