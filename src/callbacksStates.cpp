#include "callbacksStates.h"

void onStartStatePlay(State* pLastState) {

  if (!modeManager.restoreLastState()) {
    DEFAULT_MODE->activate();
  }
}

void onLoopStatePlay() {

  lightLayerManager.getTotalLedColors(leds);
  FastLED.show();
}

void onEndStatePlay(State* pNextState) {

  lightLayerManager.fadeAllToBlack();
  modeManager.deactivate();
  
  FastLED.clear();
  FastLED.show();
}

void onStartStateConfig(State* pLastState) {

  pLayerClockFace->setDefaultSpeed(1.0);
  pLayerHandHour->setDefaultSpeed(1.0);
  pLayerHandMinute->setDefaultSpeed(1.0);

  for (size_t i = 0; i <= NUM_LEDS - 1; i = i + 5) {
    pLayerClockFace->fadeLedTo(i, CRGB(60, 30, 0));
  }

  for (size_t i = 0; i <= NUM_LEDS - 1; i = i + 15) {
    pLayerClockFace->fadeLedTo(i, CRGB(30, 30, 30));
  }
}

void onLoopStateConfig() {

  pLayerHandHour->fadeAllLedsToBlack();
  pLayerHandMinute->fadeAllLedsToBlack();
  
  pLayerHandHour->fadeLedTo(ledClock.getHrLed(), CRGB(255, 0, 0));
  pLayerHandMinute->fadeLedTo(ledClock.getMinLed(), CRGB(0, 255, 0));

  lightLayerManager.getTotalLedColors(leds);
  FastLED.show();
}

void onEndStateConfig(State* pNextState) {

  lightLayerManager.fadeAllToBlack();
  
  FastLED.clear();
  FastLED.show();
}
