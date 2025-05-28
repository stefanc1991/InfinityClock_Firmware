#pragma once

 // Device
#define MDNS_HOST_NAME                  "clock"                 // Host name
#define DEVICE_NAME                     "Infinity Clock"        // Device name

// Wifi
#define AP_SSID                         "Clock-AP"              // SSID Name
#define AP_PASS                         NULL                    // SSID Password - Set to NULL to have an open AP
#define AP_CHANNEL                      10                      // WiFi Channel number between 1 and 13
#define AP_HIDE_SSID                    false                   // To disable SSID broadcast -> SSID will not appear in a basic WiFi scan
#define AP_MAX_CONNECTIONS              1                       // Maximum simultaneous connected clients on the AP

// General
#define NUM_LEDS                        60
#define COLOR_TEMPERATURE               CarbonArc

#define DEFAULT_BRIGHTNESS              255
#define MIN_BRIGHTNESS                  63
#define MAX_BRIGHTNESS                  127
#define BRIGHTNESS_INCREMENT            32

#define DEFAULT_MODE                    pModePlain

// IR Keys
#define IR_KEY_ONOFF                    "IR_KEY_ONOFF"
#define IR_KEY_CONFIG                   "IR_KEY_CONFIG"
#define IR_KEY_OK                       "IR_KEY_OK"
#define IR_KEY_UP                       "IR_KEY_UP"
#define IR_KEY_DOWN                     "IR_KEY_DOWN"
#define IR_KEY_RIGHT                    "IR_KEY_RIGHT"
#define IR_KEY_LEFT                     "IR_KEY_LEFT"

#define IR_KEY_DEFAULT_PLAY             0x5E
#define IR_KEY_DEFAULT_CONFIG           0x02
#define IR_KEY_DEFAULT_OK               0x5d
#define IR_KEY_DEFAULT_UP               0x0B
#define IR_KEY_DEFAULT_DOWN             0x0D
#define IR_KEY_DEFAULT_RIGHT            0x07
#define IR_KEY_DEFAULT_LEFT             0x08

#define IR_KEYS_FILE                    "/ir_codes.json"

// Time Settings
#define NTP_SERVER                      "de.pool.ntp.org"
#define TIMEZONE_STRING                 "CET-1CEST,M3.5.0/02,M10.5.0/03"   

