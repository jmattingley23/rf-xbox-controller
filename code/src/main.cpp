#include <Arduino.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_NeoPixel.h>

#include "Controller.h"
#include "Colors.h"
#include "ControllerData.h"

RF24 radio(2, 12);  // CE, CSN
const byte address[5] = {'j', 'm', 'a', 't', 't'};

const float LOOP_INTERVAL = 16.666;  //60Hz in ms; how often to transmit new data
const short FAIL_INTERVAL = 250;  //250 ms; minimum period of consecutive failed transmissions before we consider connection lost
long previousMillis = 0;
long lastConnected = 0;
bool writeStatus = false;
const byte LED_PIN = 11;

Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);
Controller controller;
ControllerData::ControllerDataStruct controllerData;

void setLED(const byte channels[3]);

void setup() {
    Serial.begin(9600);
    pixel.begin();
    radio.begin();
    radio.setPALevel(RF24_PA_MAX);
    radio.setDataRate(RF24_250KBPS); //low data rate improves range
    radio.openWritingPipe(address);
    radio.setRetries(3, 3); //1ms delay, 3 retries
    radio.stopListening();
    setLED(Colors::getInstance().RED); //start LED red until connection is made
    // TCCR2B = (TCCR2B & 0b11111000) | 0x01; //adjust PWM frequency for trigger motor whine
    Serial.println("starting up...");
}

void loop() {
    if((millis() - previousMillis) < LOOP_INTERVAL) {
        return;
    }
    previousMillis = millis();

    controller.gatherAllInputs();
    // controller.doRumbleMotors();
    controllerData = controller.getStruct();
    // Serial.println(controllerData.toString());

    writeStatus = radio.write(&controllerData, sizeof(controllerData));

    if(writeStatus == 1) {
        lastConnected = millis();
        setLED(Colors::getInstance().GREEN);
    } else {
        if((millis() - lastConnected) >= FAIL_INTERVAL) {
            setLED(Colors::getInstance().RED);
        }
    }
}

/**
 * Sets the onboard RGB led to the given color
 * 
 * @param channels Red, green, & blue color channels for the LED
 */
void setLED(const byte channels[3]) {
    pixel.setPixelColor(0, pixel.Color(channels[0], channels[1], channels[2]));
    pixel.show();
}
