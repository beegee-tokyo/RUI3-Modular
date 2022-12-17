#include <Wire.h>
#include "LPS35HW.h"

LPS35HW lps;

void setup() {
    while(!Serial);

    Serial.begin(115200);
    Serial.println("LPS barometer fast reading test");

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

    lps.setLowPassFilter(LPS35HW::LowPassFilter_ODR20);  // filter last 20 samples, default off
    lps.setOutputRate(LPS35HW::OutputRate_75Hz);  // optional, default is 10Hz
}

void loop() {
    float pressure = lps.readPressure();  // hPa

    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.println("hPa\n");

    delay(14);
}
