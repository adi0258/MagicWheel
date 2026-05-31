#include <Keyboard.h>
#include <KeyboardLayout.h>
#include <Keyboard_da_DK.h>
#include <Keyboard_de_DE.h>
#include <Keyboard_es_ES.h>
#include <Keyboard_fr_FR.h>
#include <Keyboard_hu_HU.h>
#include <Keyboard_it_IT.h>
#include <Keyboard_pt_PT.h>
#include <Keyboard_sv_SE.h>

#include <VirtualWire.h>

// --- Pin Definitions ---
const int rxPin = 11;        // RF Receiver Data Pin (Based on your presentation)
const int safetyPin = 12;    // Safety Pin: MUST be connected to GND to allow keyboard typing

void setup() {
  Serial.begin(9600);
  
  // Initialize Safety Pin as INPUT_PULLUP
  // This prevents the Leonardo from typing wildly if you lose control
  pinMode(safetyPin, INPUT_PULLUP);
  
  // Initialize VirtualWire RF communication
  vw_set_ptt_inverted(true);
  vw_set_rx_pin(rxPin);
  vw_setup(4000);
  vw_rx_start(); // Start listening for RF messages
  
  // Initialize Keyboard emulation
  Keyboard.begin();
  
  Serial.println("Leonardo Receiver Ready. Waiting for signals...");
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  // Check if a message has been received
  if (vw_get_message(buf, &buflen)) {
    char receivedChar = (char)buf[0];
    
    Serial.print("Received: ");
    Serial.println(receivedChar);

    // IMPORTANT: Only type on the keyboard if the Safety Pin is connected to GND
    if (digitalRead(safetyPin) == LOW) {
      
      // Execute a different keyboard press based on the received character
      if (receivedChar == 'L') {
        Keyboard.press(KEY_LEFT_ARROW);
        delay(100);
        Keyboard.releaseAll();
      } 
      if (receivedChar == 'N') {
        //Keyboard.press(KEY_UP_ARROW);
        delay(100);
        Keyboard.releaseAll();
      } 
      if (receivedChar == 'R') {
        Keyboard.press(KEY_RIGHT_ARROW);
        delay(100);
        Keyboard.releaseAll();
      }
      // הוספת התנאי עבור לחיצת הכפתור (Enter)
      if (receivedChar == 'S') {
        Keyboard.press(KEY_RETURN); // KEY_RETURN הוא הערך למקש אנטר בספריית Keyboard
        delay(100);
        Keyboard.releaseAll();
      }

    } else {
      // Warning if we receive a command but the jumper isn't connected
      Serial.println("Command received, but Safety Pin is HIGH! Keyboard input ignored.");
    }
  }
}