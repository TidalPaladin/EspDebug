#define ARDUHAL_LOG_LEVEL ARDUHAL_LOG_LEVEL_VERBOSE

#include <Arduino.h>
#include "EspDebug.h"


int x = 0;

void setup() {
    Serial.begin(115200);
    Serial.println("Hello");
    ESP_LOGE("main","STARTED");
    pinMode(LED_BUILTIN, OUTPUT);

}

void foo() {
    int x = 2;
    int y = 1;
    x+= 3;
}

void loop() {
    x++;
    ESP_LOGW("main","x: %i", x); 
    ESP_LOGE("main","x: %i", x); 
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(1000);
}  