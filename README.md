
# 🌀 Infinity Clock – AI-Powered LED Tunnel Clock

The Infinity Clock creates the illusion of infinite depth using two mirrors and programmable LEDs, while displaying synced real time. Built on an ESP32, it supports multiple light display modes, IR remote control, and OTA updates via a responsive web interface.

![Lighting Effect Demo](ClockDemo.gif)

---

## 🧠 Project Overview

The Infinity Clock combines microcontroller programming, layered LED animations, and real-time synchronization in a compact device:

* Displays the current time using layered LED effects in an "infinity mirror" setup
* Multiple animated lighting modes for hours, minutes, and seconds
* Real-time synchronization via NTP with automatic daylight saving adjustments
* Fully controllable via IR remote or web UI, including OTA firmware updates
* Adjustable brightness and animation modes via state machines

---

## ⚙️ Hardware Requirements

* ESP32 development board (tested on `nodemcu-32s`)
* 60x WS2812B (or compatible) addressable RGB LEDs
* Two mirrors (standard + semi-transparent) to create the tunnel illusion
* IR receiver and remote
* USB-C power supply
* 3D-printed case to house the clock and mirrors

---

## 🔧 PlatformIO Configuration

The development environment is defined in `platformio.ini`:

```ini
[env:nodemcu-32s]
platform = espressif32
board = nodemcu-32s
framework = arduino
board_build.filesystem = littlefs
monitor_speed = 115200
upload_speed = 1000000

lib_deps = 
  bblanchon/ArduinoJson@^7.2.0
  fastled/FastLED@^3.7.8
  z3t0/IRremote@^4.4.1
  esphome/AsyncTCP-esphome@2.1.4
  esphome/ESPAsyncWebServer-esphome@^3.2.2
  arduino-libraries/NTPClient@^3.2.1
  jchristensen/Timezone@^1.2.4
  fbiego/ESP32Time@^2.0.6
```

---

## 🧩 Key Components

### 1. State and Mode Management

* **States:** `Play`, `Config`, `Standby`
* **Modes within Play:** `Plain`, `Smooth`, `FastDark`, `FastBright`, `Sum`, optionally `Test`
* Transitions are controlled via IR or web UI
* `StateManager` and `ModeManager` handle transitions and loops

### 2. LED Layers

* **Layers:** Background, Hour hand, Minute hand, Second hand, Millisecond hand
* Managed by `LightLayerManager` for smooth transitions and overlapping effects

### 3. Time Synchronization

* NTP server: `de.pool.ntp.org`
* Local timezone handling using the `Timezone` library (CET/CEST)
* Time values are mapped to corresponding LED indices

---

## 🌐 Web Interface & OTA

* Fully asynchronous web interface (based on ESPAsyncWebServer)
* Routes:

  * `/`: Main page
  * `/setup`: OTA and device setup
* Web UI allows drag-and-drop firmware updates
* mDNS (via `clock.local`) is supported for easy access

---

## 🔢 IR Remote Integration

Default IR key mappings:

| Key   | IR Code |
| ----- | ------- |
| Play  | `0x5E`  |
| Menu  | `0x02`  |
| Up    | `0x0B`  |
| Down  | `0x0D`  |
| Right | `0x07`  |
| Left  | `0x08`  |
| OK    | `0x5D`  |

You can customize keys via /setup Web UI.

---

## 💡 Lighting Modes

Each mode defines how the clock displays time with different visual characteristics:

| Mode       | Description                                     |
| ---------- | ----------------------------------------------- |
| Plain      | Static, minimal LED hands                       |
| Smooth     | Smooth transitions and soft color fades         |
| FastDark   | Fast, high-contrast dim display                 |
| FastBright | Vivid and reactive hand movement                |
| Sum        | Cumulative display showing progression per unit |

---

## 🙏 Credits

* **Stefan Conrad** – Creator & Developer
* **FastLED**, **ESPAsyncWebServer**, **ArduinoJson**, **NTPClient**, **Timezone** – Open-source libraries

---
