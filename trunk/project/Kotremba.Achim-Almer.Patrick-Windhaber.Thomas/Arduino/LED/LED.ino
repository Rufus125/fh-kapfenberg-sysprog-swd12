// YELLOW LED
int LED_YELLOW = 13;      // yellow output pin
int IN_YELLOW = 2;        // yellow input pin
int stateYellow = HIGH;   // the current state of the yellow output pin
int readingYellow;        // the current reading from the yellow input pin
int previousYellow = LOW; // the previous reading from the yellow input pin
long timeYellow = 0;      // the last time the yellow output pin was toggled

// RED LED
int LED_RED = 12;         // red output pin
int IN_RED = 4;           // red input pin
int stateRed = HIGH;      // the current state of the red output pin
int readingRed;           // the current reading from the red input pin
int previousRed = LOW;    // the previous reading from the red input pin
long timeRed = 0;         // the last time the yellow output pin was toggled

long debounce = 200;      // the debounce time, increase if the output flickers

void setup()
{
  pinMode(IN_YELLOW, INPUT);
  pinMode(LED_YELLOW, OUTPUT);
  
  pinMode(IN_RED, INPUT);
  pinMode(LED_RED, OUTPUT);
  
  Serial.begin(9600); // initializes the USB as a serial port
}

void loop()
{
  /* YELLOW */
  ReadYellow();
  
  /* RED */
  ReadRed();
}

void ReadYellow()
{
  readingYellow = digitalRead(IN_YELLOW);

  if (readingYellow == HIGH && previousYellow == LOW && millis() - timeYellow > debounce)
  {
    if (stateYellow == HIGH)
      stateYellow = LOW;
    else
      stateYellow = HIGH;

    timeYellow = millis();
    SendData(LED_YELLOW, stateYellow);
  }

  digitalWrite(LED_YELLOW, stateYellow);

  previousYellow = readingYellow;
}

void ReadRed()
{
  readingRed = digitalRead(IN_RED);

  if (readingRed == HIGH && previousRed == LOW && millis() - timeRed > debounce)
  {
    if (stateRed == HIGH)
      stateRed = LOW;
    else
      stateRed = HIGH;

    timeRed = millis();
    SendData(LED_RED, stateRed); 
  }

  digitalWrite(LED_RED, stateRed);

  previousRed = readingRed;
}

void SendData(int led, int state)
{
  String message = "";
  message += led;
  message += state;
  
  Serial.print(message);
  //Serial.print('c');
}
