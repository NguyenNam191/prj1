#include <Arduino.h>
#include <OneButton.h>

#define BUTTON_PIN 22   
#define LED_PIN 5       

OneButton button(BUTTON_PIN, true); 

bool ledState = false;    
bool blinkMode = false;    
unsigned long previousMillis = 0;
const long interval = 500;

void handleSingleClick();
void handleDoubleClick();

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

 
  button.attachClick(handleSingleClick);     
  button.attachDoubleClick(handleDoubleClick); 

  Serial.begin(115200);
  Serial.println("Ready...");
}

void loop() {
  button.tick();

  
  if (blinkMode) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
    }
  }
}



void handleSingleClick() {
  if (blinkMode) {
   
    blinkMode = false;
    ledState = false;
    digitalWrite(LED_PIN, LOW);
    Serial.println("Exit blink mode");
  } else {
 
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    Serial.print("LED: ");
    Serial.println(ledState ? "ON" : "OFF");
  }
}

void handleDoubleClick() {
  blinkMode = true;
  Serial.println("Blink mode ON");
}
