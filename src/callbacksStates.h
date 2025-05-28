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

extern State* pModeTest;
extern State* pModePlain;
extern State* pModeSmooth;
extern State* pModeFastDark;
extern State* pModeFastBright;
extern State* pModeSum;

extern CRGB leds[NUM_LEDS];

extern LightLayer* pLayerClockFace;
extern LightLayer* pLayerHandHour;
extern LightLayer* pLayerHandMinute;

void onStartStatePlay(State * pLastState);
void onLoopStatePlay();
void onEndStatePlay(State* pNextState);

void onStartStateConfig(State* pLastState);
void onLoopStateConfig();
void onEndStateConfig(State* pNextState);
