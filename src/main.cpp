#include "main.h"

/*
 * ----------------------------------------------------------------------------
 * Project:       LED Infinity Clock
 * Description:   Software for my mostly 3D printed DIY LED Clock, 
 *                that creates the issusion of depth in a thin Mirror. 
 *                Using a normal and a half transparent mirror each of 60 LED is reflected 
 *                multiple times making it look like a tunnel of bulbs representing the current time.
 *                (supports IR control, OTA updates, Wifi, NTP servers and multiple light patterns)
 *
 * Platform:      ESP32 / Arduino Framework
 * Author:        Stefan Conrad
 * Created:       26.05.2025
 * Comments:      Minimal due to private project ;)
 * ----------------------------------------------------------------------------
 */

 void setup() {

  Serial.begin(115200);

  LittleFsHelper::begin();

  FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setTemperature(COLOR_TEMPERATURE);
  FastLED.clear();
  FastLED.show();

  WifiManager.begin(MDNS_HOST_NAME, AP_SSID, AP_PASS);

  WiFi.onEvent(onWiFiConnected, ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(onWiFiDisconnected, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  WiFi.onEvent(onApConnected, ARDUINO_EVENT_WIFI_AP_STACONNECTED);

  // the IrManager will look for these keys in the file and create them with default values if not present
  IrManager.addIrKey(IR_KEY_ONOFF, IR_KEY_DEFAULT_PLAY, onClickIrKeyPlay);
  IrManager.addIrKey(IR_KEY_CONFIG, IR_KEY_DEFAULT_CONFIG, onClickIrConfig);
  IrManager.addIrKey(IR_KEY_OK, IR_KEY_DEFAULT_OK, onClickIrOk);
  IrManager.addIrKey(IR_KEY_UP, IR_KEY_DEFAULT_UP, onClickIrKeyUp);
  IrManager.addIrKey(IR_KEY_DOWN, IR_KEY_DEFAULT_DOWN, onClickIrKeyDown);
  IrManager.addIrKey(IR_KEY_RIGHT, IR_KEY_DEFAULT_RIGHT, onClickIrKeyRight);
  IrManager.addIrKey(IR_KEY_LEFT, IR_KEY_DEFAULT_LEFT, onClickIrKeyLeft);
  IrManager.begin(IR_RECEIVE_PIN, IR_KEYS_FILE);

  // stateManager is defined with Independent mode in main.h (states are not sorted)
  pStatePlay = stateManager.addState();     pStatePlay->onStart(onStartStatePlay);              pStatePlay->onLoop(onLoopStatePlay);              pStatePlay->onEnd(onEndStatePlay);
  pStateConfig = stateManager.addState();   pStateConfig->onStart(onStartStateConfig);          pStateConfig->onLoop(onLoopStateConfig);          pStateConfig->onEnd(onEndStateConfig);
  pStateStandby = stateManager.addState();

  // modeManager is another instance of the class StateManager organizing the light patterns within the state pStatePlay. It runs in circular mode (states are sorted)
  pModePlain = modeManager.addState();      pModePlain->onStart(onStartModePlain);            pModePlain->onLoop(onLoopModePlain);            pModePlain->onEnd(onEndAnyMode);
  pModeSmooth = modeManager.addState();     pModeSmooth->onStart(onStartModeSmooth);          pModeSmooth->onLoop(onLoopModeSmooth);          pModeSmooth->onEnd(onEndAnyMode);
  pModeFastDark = modeManager.addState();   pModeFastDark->onStart(onStartModeFastDark);      pModeFastDark->onLoop(onLoopModeFastDark);      pModeFastDark->onEnd(onEndAnyMode);
  pModeFastBright = modeManager.addState(); pModeFastBright->onStart(onStartModeFastBright);  pModeFastBright->onLoop(onLoopModeFastBright);  pModeFastBright->onEnd(onEndAnyMode);
  pModeSum = modeManager.addState();        pModeSum->onStart(onStartModeSum);                pModeSum->onLoop(onLoopModeSum);                pModeSum->onEnd(onEndAnyMode);

  // lightLayerManager is defined in main.h and handles the different overlaying LED colors
  pLayerClockFace = lightLayerManager.addLayer();
  pLayerHandHour = lightLayerManager.addLayer();
  pLayerHandMinute = lightLayerManager.addLayer();
  pLayerHandSecond = lightLayerManager.addLayer();
  pLayerHandMillis = lightLayerManager.addLayer();

  lightLayerManager.setBrightness(255);

  WebPageSetup.begin(DEVICE_NAME, &server);
  WebPageSetup.onUploadStart(onUploadStart);
  WebPageSetup.onUploadProgress(onUploadProgress);
  WebPageSetup.onUploadEnd(onUploadEnd);

  // ledClock is an instance of the class NTPLedClock and handles the syncronization with the NTP server and provides the time for the LEDs
  ledClock.begin(NTP_SERVER, TIMEZONE_STRING);

  pStatePlay->activate();
}

void loop() {
  WifiManager.loop();
  WebPageSetup.loop();
}
