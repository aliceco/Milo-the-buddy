#include <FastLED.h>

#define DATA_PIN 5
#define CLOCK_PIN 13
#define headButtonPin 2
#define heartButtonPin 7   // Added second button pin

#define NUM_LEDS 10

CRGB leds[NUM_LEDS];

int fadeAmount = 5;
int brightness = 0;
bool breathing = false;
bool secondBreathing = false;
bool letGo = false;

int headButtonCounter = 0;

//old colours
//fill_solid(leds, 3, CRGB(255, 70, 0));  // warm yellow
//leds[i].setRGB(255, 141, 59); // base color
//fill_solid(leds + 4, 3, CRGB(255, 50, 59));

void setup() {
  Serial.begin(9600);
  //Serial.println("resetting");
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  FastLED.setBrightness(80);

  pinMode(headButtonPin, INPUT_PULLUP);
  pinMode(heartButtonPin, INPUT_PULLUP);
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

void loop() {
  // Read both butons
  int headPressed = digitalRead(headButtonPin) == LOW;
  int heartPressed = digitalRead(heartButtonPin) == LOW;

  // --- HEAD BUTTON ACTION ---
  if (headPressed && headButtonCounter == 0) {
    // Step 1: Turn on first 3 LEDs for 3 seconds
    fill_solid(leds, 3, CRGB(255, 100, 59));  // warm yellow
    FastLED.show();
    //Serial.println("asks first question");
    Serial.println("1");
    delay(4000);

    // Step 2: Start breathing
    breathing = true;
    brightness = 0;
    fadeAmount = 5;
    headButtonCounter++;
  } else if (headPressed && headButtonCounter == 1) {
    // Step 1: Turn on first 3 LEDs for 3 seconds
    secondBreathing = false; // stop breathing
    Serial.println("4");
    fill_solid(leds, NUM_LEDS, CRGB(255, 70, 0));
    FastLED.show();
    
    //Serial.println("Thank you for your thougts");
    delay(3500);
    FastLED.clear();
    FastLED.show();
    //Serial.println("Done");
    headButtonCounter = 0;
  }

  // --- BREATHING EFFECT ---
  if (breathing) {
    // fade all 3 LEDs together
    for (int i = 0; i < 3; i++) {
      leds[i].setRGB(255, 100, 59); // base color
      leds[i].fadeLightBy(255 - brightness); // scale brightness
    }
    FastLED.show();

    brightness += fadeAmount;
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount; // reverse direction
    }
    delay(20);
  }

  // --- HEART BUTTON ACTION ---
  //Second stage. check out question
  if (heartPressed && breathing) {
    
    breathing = false; // stop breathing
    fill_solid(leds, 3, CRGB::Black); // turn them off
    FastLED.show();
    //whole array
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i] = CRGB(255, 100, 59);
      FastLED.show();
      fadeall();
      delay(150);
    }

    Serial.println("2");
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i] = CRGB::Black; // turn them off
      FastLED.show();
      fadeall();
      delay(150);
    }
    letGo = true;
  }

  if (letGo){
    Serial.println("3");
    //4-7 leds for heart
    fill_solid(leds + 4, 3, CRGB(255, 70, 0));
    FastLED.show();
    //Serial.println("asks second question");
    delay(3000);
    headButtonCounter++;
    secondBreathing = true;
  }

  if (secondBreathing) {
    letGo = false;
    // fade all 3 LEDs together
    for (int i = 4; i < 7; i++) {
      leds[i].setRGB(255, 70, 0); // base color
      leds[i].fadeLightBy(255 - brightness); // scale brightness
    }
    FastLED.show();

    brightness += fadeAmount;
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount; // reverse direction
    }
    delay(20);
  }
}