#include <VirtualWire.h>

// --- Pin Definitions ---
const int potPin = A0;       // פין אנלוגי עבור הפוטנציומטר
const int buttonPin = 4;     // Digital pin for the confirmation button
const int txPin = 8;         // RF Transmitter Data Pin

int lastButtonState = HIGH;
bool pendingButtonPress = false; // דגל שיזכור אם הכפתור נלחץ

unsigned long previousMillis = 0; // משתנה לשמירת הזמן של השליחה האחרונה
const long interval = 1000;       // מרווח של 1 שנייה (1000 מילישניות) בין שליחות

void setup() {
  Serial.begin(9600);
  
  // Use internal pull-up resistor for the button
  pinMode(buttonPin, INPUT_PULLUP); 

  // Initialize VirtualWire RF communication
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(txPin);
  vw_setup(4000); // Speed of data transfer
  
  Serial.println("Uno Transmitter Ready.");
}

// פונקציית עזר קטנה כדי לחסוך קוד כפול לשליחת המסרים
void sendMessage(const char* message) {
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
  Serial.print("Message sent: ");
  Serial.println(message);
}

void loop() {
  unsigned long currentMillis = millis(); // קריאת הזמן הנוכחי

  // 1. קריאת הכפתור באופן רציף כדי לא לפספס לחיצות
  int buttonState = digitalRead(buttonPin);

  // זיהוי לחיצה (מעבר מ-HIGH ל-LOW)
  if (buttonState == LOW && lastButtonState == HIGH) {
    pendingButtonPress = true; // נדליק את הדגל ונשמור את הלחיצה לפעימה הבאה
    delay(50); // Debounce קטן למניעת קריאה כפולה של אותה לחיצה (לא יפריע ל-millis)
  }
  lastButtonState = buttonState;

  // 2. בדיקה האם חלפה שניה (1000 מילישניות) לפחות מאז השליחה האחרונה
  if (currentMillis - previousMillis >= interval) {
    
    // אם הכפתור נלחץ במהלך השנייה הזו, נשלח 'S'
    if (pendingButtonPress) {
      sendMessage("S");
      pendingButtonPress = false; // נאפס את הדגל אחרי השליחה
    } 
    // אם לא נלחץ כפתור, נבדוק את הפוטנציומטר ונשלח את המצב שלו
    else {
      int potValue = analogRead(potPin); 
      const char *message;

      if (potValue < 409) {
        message = "R";
      } else if (potValue < 914) {
        message = "N"; 
      } else {
        message = "L"; 
      }

      sendMessage(message);
    }
    
    // נעדכן את הזמן של השליחה הנוכחית כדי להתחיל לספור שניה חדשה
    previousMillis = currentMillis; 
  }
}