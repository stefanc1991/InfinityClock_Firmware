#include "callbacksModes.h"

void onStartModePlain(State* pLastState) {

  pLayerClockFace->setDefaultSpeed(1.0);
  pLayerHandHour->setDefaultSpeed(0.0);
  pLayerHandMinute->setDefaultSpeed(0.0);
  pLayerHandSecond->setDefaultSpeed(0.0);

  for (size_t i = 0; i <= NUM_LEDS - 1; i = i + 5) {
    pLayerClockFace->fadeLedTo(i, CRGB(70, 57, 17));
    // pLayerClockFace->fadeLedTo(i, CRGB(90, 45, 0));
  }
}

void onLoopModePlain() {

  pLayerHandHour->fadeAllLedsToBlack();
  pLayerHandMinute->fadeAllLedsToBlack();
  pLayerHandSecond->fadeAllLedsToBlack();
  pLayerHandMillis->fadeAllLedsToBlack();

  pLayerHandHour->fadeLedTo(ledClock.getHrLed(), CRGB(255, 0, 0));
  pLayerHandMinute->fadeLedTo(ledClock.getMinLed(), CRGB(0, 255, 0));
  pLayerHandSecond->fadeLedTo(ledClock.getSecLed(), CRGB(0, 0, 255));

}

void onStartModeSmooth(State* pLastState) {

  pLayerClockFace->setDefaultSpeed(1.0);
  pLayerHandHour->setDefaultSpeed(0.4);
  pLayerHandMinute->setDefaultSpeed(0.4);
  pLayerHandSecond->setDefaultSpeed(0.4);

  for (size_t i = 0; i <= NUM_LEDS - 1; i = i + 5) {
    pLayerClockFace->fadeLedTo(i, CRGB(70, 57, 17));
  }

  for (size_t i = 0; i <= NUM_LEDS - 1; i = i + 15) {
    pLayerClockFace->fadeLedTo(i, CRGB(60, 60, 60));
  }
}

void onLoopModeSmooth() {

  pLayerHandHour->fadeAllLedsToBlack();
  pLayerHandMinute->fadeAllLedsToBlack();
  pLayerHandSecond->fadeAllLedsToBlack();
  pLayerHandMillis->fadeAllLedsToBlack();

  pLayerHandHour->fadeLedTo(ledClock.getHrLed() - 1, CRGB(100, 0, 0), 1.0);
  pLayerHandHour->fadeLedTo(ledClock.getHrLed(), CRGB(255, 0, 0), 1.0);
  pLayerHandHour->fadeLedTo(ledClock.getHrLed() + 1, CRGB(100, 0, 0), 1.0);

  pLayerHandMinute->fadeLedTo(ledClock.getMinLed(), CRGB(0, 255, 0), 1.0);

  pLayerHandSecond->fadeLedTo(ledClock.getSecLed(), CRGB(0, 0, 255), 1.0);
}

void onStartModeFastDark(State* pLastState) {

  pLayerClockFace->setDefaultSpeed(1.0);
  pLayerHandHour->setDefaultSpeed(0.4);
  pLayerHandMinute->setDefaultSpeed(0.4);
  pLayerHandSecond->setDefaultSpeed(0.0);
  pLayerHandMillis->setDefaultSpeed(0.0);
}

void onLoopModeFastDark() {

  pLayerHandHour->fadeAllLedsToBlack();
  pLayerHandMinute->fadeAllLedsToBlack();
  pLayerHandSecond->fadeAllLedsToBlack();
  pLayerHandMillis->fadeAllLedsToBlack();

  pLayerHandHour->fadeLedTo(ledClock.getHrLed() + 1, CRGB(100, 0, 0));
  pLayerHandHour->fadeLedTo(ledClock.getHrLed(), CRGB(255, 0, 0));
  pLayerHandHour->fadeLedTo(ledClock.getHrLed() - 1, CRGB(100, 0, 0));

  pLayerHandMinute->fadeLedTo(ledClock.getMinLed(), CRGB(0, 255, 0));

  pLayerHandSecond->fadeLedTo(ledClock.getSecLed(), CRGB(0, 0, 255));

  pLayerHandMillis->fadeLedTo(ledClock.getSecLed() + ledClock.getMilliSecLed() + 1, CRGB(60, 60, 60));
}

void onStartModeFastBright(State* pLastState) {

  pLayerClockFace->setDefaultSpeed(1.0);
  pLayerHandHour->setDefaultSpeed(1.0);
  pLayerHandMinute->setDefaultSpeed(1.0);
  pLayerHandSecond->setDefaultSpeed(0.0);
  pLayerHandMillis->setDefaultSpeed(0.5);
}

void onLoopModeFastBright() {

  pLayerHandHour->fadeAllLedsToBlack();
  pLayerHandMinute->fadeAllLedsToBlack();
  pLayerHandSecond->fadeAllLedsToBlack();
  pLayerHandMillis->fadeAllLedsToBlack();

  pLayerHandHour->fadeLedTo(ledClock.getHrLed() + 1, CRGB(100, 0, 0));
  pLayerHandHour->fadeLedTo(ledClock.getHrLed(), CRGB(255, 0, 0));
  pLayerHandHour->fadeLedTo(ledClock.getHrLed() - 1, CRGB(100, 0, 0));

  pLayerHandMinute->fadeLedTo(ledClock.getMinLed(), CRGB(0, 255, 0));

  pLayerHandSecond->fadeLedTo(ledClock.getSecLed(), CRGB(0, 0, 255));

  pLayerHandMillis->fadeLedTo(ledClock.getSecLed() + ledClock.getMilliSecLed() + 1, CRGB(60, 60, 60), 0);
}

void onStartModeSum(State* pLastState) {

  pLayerClockFace->setDefaultSpeed(1.0);
  pLayerHandHour->setDefaultSpeed(0.5);
  pLayerHandMinute->setDefaultSpeed(0.5);
  pLayerHandSecond->setDefaultSpeed(0.5);
  pLayerHandMillis->setDefaultSpeed(0.5);
}

void onLoopModeSum() {

  pLayerHandHour->fadeAllLedsToBlack();
  pLayerHandMinute->fadeAllLedsToBlack();
  pLayerHandSecond->fadeAllLedsToBlack();
  pLayerHandMillis->fadeAllLedsToBlack();

  for (size_t i = 0; i <= ledClock.getHrLed(); i++) {
      pLayerHandHour->fadeLedTo(i, CRGB(255, 0, 0), 1.0);
  }

  for (size_t i = 0; i <= ledClock.getMinLed(); i++) {
      pLayerHandMinute->fadeLedTo(i, CRGB(0, 255, 0), 1.0);
  }

  for (size_t i = 0; i <= ledClock.getSecLed(); i++) {
      pLayerHandSecond->fadeLedTo(i, CRGB(0, 0, 255), 1.0);
  }
}

void onStartModeTest(State* pLastState) {

  // pLayerClockFace->setAllColors(CRGB(0, 10, 0));

  // for (size_t i = 0; i <= NUM_LEDS - 1; i = i + 5) {
  //   pLayerClockFace->setColor(i, CRGB(30, 0, 0));
  // }
}

void onLoopModeTest() {

  // if (!pLayerClockFace->isColorTransitionComplete()) {
  //   return;
  // }

  // // if (!ledClock.update())
  // //   return;

  // if (ledClock.hasHourLedChanged()) {
  //   pLayerHandHour->startColorTransition(ledClock.getHrLed(), CRGB(255, 200, 0), 500);
  //   pLayerHandHour->startColorTransition(ledClock.getHrLed() - 1, CRGB::Black, 500);
  // }

  // if (ledClock.hasMinuteLedChanged()) {
  //   pLayerHandMinute->startColorTransition(ledClock.getMinLed(), CRGB(0, 0, 200), 500);
  //   pLayerHandMinute->startColorTransition(ledClock.getMinLed() - 1, CRGB::Black, 500);
  // }

  // if (ledClock.hasSecondLedChanged()) {
  //   pLayerHandSecond->setColor(ledClock.getSecLed(), CRGB(1, 1, 1));
  //   pLayerHandSecond->setColor(ledClock.getSecLed() - 1, CRGB::Black);
  // }
}

void onEndAnyMode(State* pLastState) {
  pLayerClockFace->fadeAllLedsToBlack(2.0);
  // pLayerHandHour->fadeAllLedsToBlack(2.0);
  // pLayerHandMinute->fadeAllLedsToBlack(2.0);
  // pLayerHandSecond->fadeAllLedsToBlack(2.0);
  // pLayerHandMillis->fadeAllLedsToBlack(2.0);
}
