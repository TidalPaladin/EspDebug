#include <Arduino.h>
#include "EspDebug.h"


int x = 0;

void setup() {
    Serial.begin(115200);
    Serial.println("Hello");
    ESP_LOGE("main","STARTED");
    pinMode(LED_BUILTIN, OUTPUT);

}

void bar();

void foo() {
    int x = 2;
    delay(1);
    if(x == 3)
        panic();
    bar();
}

void bar() {
    int y = 5;
    Serial.println(y);
}

void loop() {
    x++;
    foo();
    ESP_LOGW("main","x: %i", x); 
    ESP_LOGE("main","x: %i", x); 
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(1000);
    ESP.wdtFeed();
}  