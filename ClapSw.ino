// Clap Light Switch
// Serhii Bazavluk | March 2021
// YouTube: https://www.youtube.com/electricalpro

int mic = 2;       // microphone module
int indicLED = 13; // indication pin
int lightPin = 9;  // relay (lights control)
bool lightState = true;
bool ignoreInt = false;
bool ClapDetected = false;
uint32_t ClapDetetedTime [3] {};

void setup() {
  Serial.begin(115200);
  pinMode(indicLED, OUTPUT);    
  pinMode(lightPin, OUTPUT);  
  digitalWrite(lightPin, lightState);
  attachInterrupt(digitalPinToInterrupt(mic), ISR_ClapDetected, FALLING);
}

void loop() {
delay(2);

if(millis() - ClapDetetedTime[2] >= 800)
{
  digitalWrite(indicLED, LOW);
}

if(millis() - ClapDetetedTime[2] < 800 && millis() - ClapDetetedTime[1] < 800 && ClapDetected && ClapDetetedTime[1] - ClapDetetedTime[0]>=800)
  {
    Serial.println("double clap detected");
    digitalWrite(indicLED, LOW);
    Serial.print("Setting light to ");
    Serial.println(String(!lightState));
    digitalWrite(lightPin, lightState);
    lightState=!lightState;
    ClapDetected = false;
  }
}

void ISR_ClapDetected()
{
  if(millis() - ClapDetetedTime[2] > 200){ // debounce

  for (int i = 0; i != 2; i++) {
  ClapDetetedTime[i] = ClapDetetedTime[i + 1];
  }
  
  ClapDetetedTime[2] = millis();
  ClapDetected = true;
  Serial.println("clap detected");
  digitalWrite(indicLED, HIGH);
  }
}
