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
  // This is crucial for overpowering BLE devices
  radio.setPALevel(RF24_PA_MAX);
  
  // Set Data Rate to 2Mbps
  // Higher rate = more packets per second = more noise
  radio.setDataRate(RF24_2MBPS);
  
  // Open a writing pipe to a specific address
  radio.openWritingPipe(address[0]);
  
  // Stop listening so we can transmit continuously
  radio.stopListening();

  // Power up the radio