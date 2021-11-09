void AllOff() {
  for (int i = 0; i < NUM_LEDS; i++) {
    // Now turn the LED off, then pause
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}

void InitLeds(){
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness(254);
  AllOff();
}

void ChaseLoop(int interval, int ledAmount, CRGB myColor) {
  CRGB targetColor = myColor;
  if (millis() - timer[0] > interval) {
    timer[0] = millis();

    // Set LED color
    //    leds[ledIndex[0]] = CRGB(0, 255, 255);
    leds[ledIndex[0]] = targetColor;
    FastLED.show();

    // Increment led index
    ledIndex[0]++;
//    Serial.println(ledIndex[0]);

    // Loop to start
    if (ledIndex[0] > NUM_LEDS) {
      AllOff();
      ledIndex[0] = 0;
    } else if (ledAmount = 0 && ledIndex[0] > ledAmount) {
      AllOff();
      ledIndex[0] = 0;
    }
  }
}

void DisplayConnectionCode(int code) {
  switch (code) {
    case 0: // Connecting
      ChaseLoop(500, NUM_LEDS, CRGB::Blue);
      break;
    case 1: // Connection Established
      ChaseLoop(500, NUM_LEDS, CRGB::Green);
      break;
    case 2: // Connection Error
      ChaseLoop(500, NUM_LEDS, CRGB::Red);
      break;
  }
}

//void Flash(int interval, int startLED, int endLED, CRGB color) {
//  CRGB targetColor = color;
//
//  if (millis() - timer[1] > interval) {
//    timer[1] = millis();
//
//    if (!flashState) {
//      for (int i = startLED; i < endLED; i++) {
//        leds[i] = color;
//        FastLED.show();
//      }
//      flashState = true;
//    } else {
//      for (int i = startLED; i < endLED; i++) {
//        leds[i] = CRGB::Black;
//        FastLED.show();
//      }
//      flashState = false;
//    }
//
//    // DEBUG
//    //    Serial.print("Flash: ");
//    //    Serial.print(flashState, DEC);
//    //    Serial.println("");
//  }
//}
