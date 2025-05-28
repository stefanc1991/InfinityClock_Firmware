#include "callbacksIrKeys.h"

// Infrared-Keys available for this project

void onClickIrKeyPlay() {
  if (!pStatePlay->isActive()) {
    pStatePlay->activate();
  }
  else {
    pStateStandby->activate();
  }
}

void onClickIrConfig() {
  if (!pStateConfig->isActive()) {
    pStateConfig->activate();
  }
  else {
    pStatePlay->activate();
  }
}

void onClickIrOk() {
  if (pStatePlay->isActive()) {
    pStateStandby->activate();
  }
  else if (pStateStandby->isActive()) {
    pStatePlay->activate();
  }
  else if (pStateConfig->isActive()) {
    pStatePlay->activate();
  }
}

void onClickIrKeyUp() {
  if (pStatePlay->isActive()) {
    // brightness += BRIGHTNESS_INCREMENT;
    // lightLayerManager.setBrightness(brightness);
  }
  else if (pStateConfig->isActive()) {
    ledClock.addHour();
  }
}

void onClickIrKeyDown() {
  if (pStatePlay->isActive()) {
    // brightness -= BRIGHTNESS_INCREMENT;
    // lightLayerManager.setBrightness(brightness);
  }
  else if (pStateConfig->isActive()) {
    ledClock.subHour();
  }
}

void onClickIrKeyRight() {
  if (pStatePlay->isActive()) {
    modeManager.nextState();
  }
  else if (pStateConfig->isActive()) {
    ledClock.addMinute();
  }
}

void onClickIrKeyLeft() {
  if (pStatePlay->isActive()) {
    modeManager.previousState();
  }
  else if (pStateConfig->isActive()) {
    ledClock.subMinute();
  }
}
