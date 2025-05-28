#pragma once

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>
#include <FastLED.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Timezone.h>

#include "LittleFsHelper.h"
#include "IrManager.h"
#include "StateManager.h"
#include "LightLayerManager.h"
#include "WifiManager.h"
#include "WebPageSetup.h"
#include "NTPLedClock.h"
#include "ClampedInteger.h"
#include "CyclicInteger.h"

#include "pins.h"
#include "definitions.h"

extern LightLayerManager lightLayerManager;
extern StateManager modeManager;

extern NTPLedClock ledClock;

extern State* pStatePlay;
extern State* pStateStandby;
extern State* pStateConfig;

extern ClampedInteger brightness;

void onClickIrKeyPlay();
void onClickIrConfig();
void onClickIrOk();
void onClickIrKeyUp();
void onClickIrKeyDown();
void onClickIrKeyRight();
void onClickIrKeyLeft();
