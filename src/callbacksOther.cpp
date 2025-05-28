#include "callbacksOther.h"

void onWiFiConnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  server.begin();
}

void onWiFiDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  server.end();
}

void onApConnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  server.begin();
}

void onUploadStart() {
  stateManager.deactivate();
  // pStateUpload->activate();
}

void onUploadProgress(size_t current, size_t final) {

  current = min(current, final);

  size_t numBrightLeds = map(current, 0, final + 1, 0, NUM_LEDS);
  byte colorFracGreen = map(current, 0, final + 1, 0, 256);
  byte colorFracRed = 255 - colorFracGreen;

  fill_solid(leds, NUM_LEDS, CRGB::Black);

  for (size_t i = 0; i <= numBrightLeds; i++) {
    leds[i] = CRGB(colorFracRed, colorFracGreen, 0);
  }

  FastLED.show();
}

void onUploadEnd(bool success) {
  pStatePlay->activate();
}
