#pragma once

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>
#include <FastLED.h>

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

extern LightLayer* pLayerClockFace;
extern LightLayer* pLayerHandHour;
extern LightLayer* pLayerHandMinute;
extern LightLayer* pLayerHandSecond;
extern LightLayer* pLayerHandMillis;

extern NTPLedClock ledClock;

void onStartModePlain(State* pLastState);
void onLoopModePlain();

void onStartModeSmooth(State* pLastState);
void onLoopModeSmooth();

void onStartModeFastDark(State* pLastState);
void onLoopModeFastDark();

void onStartModeFastBright(State* pLastState);
void onLoopModeFastBright();

void onStartModeSum(State* pLastState);
void onLoopModeSum();

void onStartModeTest(State* pLastState);
void onLoopModeTest();

void onEndAnyMode(State* pNextMode);
