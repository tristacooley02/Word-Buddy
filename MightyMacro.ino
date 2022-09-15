// MightyMacro Code
// ESP32-Enabled Macro Keyboard
// Trista || September 14th

// Buttons
#include <Bounce2.h>                      // Bounce2 Library
const uint8_t buttonPins[9] = {35,16,33,32,17,27,19,18,26};     // Fill in { } with list of GPIO pins
Bounce * buttons = new Bounce[8];         // Creates an array of Bounce objects

// Bluetooth
// Additional documentation available here:  https://github.com/T-vK/ESP32-BLE-Keyboard
#include <BleKeyboard.h>                                      // BleKeyboard Library          
BleKeyboard bleKeyboard("Word Buddy", "Trista360", 100); 

void setup() {
  initButtons();                      // Initialize Buttons on Startup
  initBattery();                      // Initialize Battery on Startup
  bleKeyboard.begin();                // Begin Bluetooth Connection
}

void loop() {
  if(bleKeyboard.isConnected()){      // If Bluetooth is Connected
    readButtons();                    // Read State of Buttons and Perform Functions
    updateBattery();                  // Update Battery Status if Needed
  }
}
