#pragma once

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>
#include <FastLED.h>
#include <NTPClient.h>
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

#include "callbacksIrKeys.h"
#include "callbacksStates.h"
#include "callbacksModes.h"
#include "callbacksOther.h"


// Global variable declarations
AsyncWebServer server(80);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER, 0, TIME_SYNC_INTERVAL);

TimeChangeRule cestRule = { "CEST", Last, Sun, Mar, 2, 120 };   // central european summer time
TimeChangeRule cetRule = { "CET",  Last, Sun, Oct, 3,  60 };    // central european time
Timezone germanTimeZone(cestRule, cetRule);

NTPLedClock ledClock(&timeClient, &germanTimeZone, NUM_LEDS);

StateManager stateManager(INDEPENDENT);
StateManager modeManager(CYCLIC);

LightLayerManager lightLayerManager(NUM_LEDS);

LightLayer* pLayerClockFace;
LightLayer* pLayerHandHour;
LightLayer* pLayerHandMinute;
LightLayer* pLayerHandSecond;
LightLayer* pLayerHandMillis;

State* pStateConfig;
State* pStatePlay;
State* pStateStandby;

State* pModePlain;
State* pModeSmooth;
State* pModeFastDark;
State* pModeFastBright;
State* pModeSum;
State* pModeTest;

CRGB leds[NUM_LEDS];
ClampedInteger brightness(MIN_BRIGHTNESS, MAX_BRIGHTNESS, DEFAULT_BRIGHTNESS);
