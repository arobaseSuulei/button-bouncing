// C++ code
//

int ledPin=10;
int buttonPin=5;
bool etatLED=false;

int lastButtonState=HIGH;

unsigned long lastDebounceTime = 0;
int debounceDelay = 200;



void setup()
{
 
  
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin,INPUT_PULLUP);
}

void loop()
{
  bool currentButtonState=digitalRead(buttonPin);
  
  if(currentButtonState==LOW && lastButtonState){

    if(millis() - lastDebounceTime > debounceDelay){

      etatLED = !etatLED;
      digitalWrite(ledPin, etatLED);
      lastDebounceTime = millis();
    }
    
    
  
  
  
}
}