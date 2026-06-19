# nRF24 BLE Interferer

<div align="center">

![Version](https://img.shields.io/badge/version-1.0-blue)
![Platform](https://img.shields.io/badge/platform-Arduino-lightgrey)
![License](https://img.shields.io/badge/license-MIT-yellow)

**Professional-grade firmware to flood the 2.4GHz spectrum and disable Bluetooth in a localized area.**

</div>

---

## 📋 Overview

This project provides firmware for an Arduino-based system using the **nRF24L01+** radio module to act as a spectrum jammer. By broadcasting at maximum power and high data rates, it floods the air with radio packets, effectively causing nearby Bluetooth (BLE) devices to disconnect or fail to connect.

*   **Power Level:** Maximum (RF24_PA_MAX)
*   **Data Rate:** 2Mbps (High traffic)
*   **Mode:** Continuous Transmission

---

## 🛠️ Hardware Requirements

Before starting, ensure you have the following components:

*   **Microcontroller:** Arduino Uno, Nano, or Pro Mini
*   **Radio Module:** nRF24L01+ (The **+** version is required for maximum output)
*   **Power Source:** USB power bank or 3.7V Li-Ion battery with TP4056 charger
*   **Capacitor:** 10µF Electrolytic (Highly recommended for stability)
*   **Computer:** For uploading code

---

## 🔌 Wiring Diagram

The nRF24L01+ operates at **3.3V**. Do not connect VCC directly to Arduino 5V.

| nRF24L01 Pin | Arduino Pin | Description |
| :--- | :--- | :--- |
| **VCC** | **3.3V** | **Critical:** Must be 3.3V |
| **GND** | **GND** | Ground |
| **CE** | **Pin 7** | Chip Enable |
| **CSN** | **Pin 8** | Chip Select Not |
| **SCK** | **Pin 13** | SPI Clock |
| **MOSI** | **Pin 11** | SPI Data Out |
| **MISO** | **Pin 12** | SPI Data In |

**💡 Pro Tip:** Solder a 10µF capacitor across the VCC and GND pins of the nRF24 module to prevent power fluctuations.

---

## 🚀 Installation

1.  Open the **Arduino IDE**.
2.  Go to **Sketch** > **Include Library** > **Manage Libraries**.
3.  Search for **"RF24"** by **TMRh20**.
4.  Click **Install**.
5.  Create a new sketch and paste the code below.

---

## 💻 Firmware Code

```cpp
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Configure CE and CSN pins
// Pin assignments can vary by Arduino board
const int CE_PIN = 7;
const int CSN_PIN = 8;

// Create the nRF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Define a dummy address
const byte address[][6] = {"FLOOD"};

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  
  // Initialize the radio
  radio.begin();
  
  // --- INTERFERENCE SETTINGS ---
  
  // Set PA Level to MAX (31dBm)
  // This is crucial for overpowering BLE signals
  radio.setPALevel(RF24_PA_MAX);
  
  // Set Data Rate to 2Mbps
  // Higher rate = more packets per second = more noise
  radio.setDataRate(RF24_2MBPS);
  
  // Open a writing pipe to a specific address
  radio.openWritingPipe(address[0]);
  
  // Stop listening so we can transmit continuously
  radio.stopListening();

  // Power up the radio
}

void loop() {
  // Create a dummy payload to transmit
  const char text[] = "JAM"; 
  
  // Transmit the text continuously
  bool result = radio.write(&text, sizeof(text));
  
  // (Optional) Blink an LED to indicate activity
  // digitalWrite(LED_BUILTIN, result ? HIGH : LOW);
  
  // Small delay to prevent overwhelming the MCU
  delay(10); 
}
