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

extern StateManager stateManager;

extern State* pStatePlay;
extern State* pStateConfig;
// extern State* pStateUpload;
extern State* pStateStandby;

extern AsyncWebServer server;
extern NTPClient timeClient;

extern CRGB leds[NUM_LEDS];

void onWiFiConnected(WiFiEvent_t event, WiFiEventInfo_t info);
void onWiFiDisconnected(WiFiEvent_t event, WiFiEventInfo_t info);
void onApConnected(WiFiEvent_t event, WiFiEventInfo_t info);
void onUploadStart();
void onUploadProgress(size_t current, size_t final);
void onUploadEnd(bool success);
