#define ECHO 13
#define TRIG 12

#define RED   10
#define GREEN 9
#define BLUE  8

// shiftOut
int latchPin = 4;
int clockPin = 3;
int dataPin = 2;

int CDS = A0;
int CDS_LED_ON = 128;
int CDS_LED_OFF = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(CDS, INPUT);

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);

  pinMode(latchPin,OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop()
{
  // ECO DISTANCE
  long dist = Get_Eco_Distance(TRIG, ECHO);

  LED_off();

  if(dist < 10) LED_color(0,255,255);      //red
  else if(dist < 20) LED_color(255,0,255); //green
  else if(dist < 30) LED_color(255,255,0); //blue
  else LED_off();

  // CDS DETECT
  int val = analogRead(CDS);
  CDS_LED_Control(val);

  delay(100);
}

void CDS_LED_Control(int val)
{
  digitalWrite(latchPin, LOW);
  if(val <= 30)
  {
    shiftOut(dataPin, clockPin, LSBFIRST, CDS_LED_ON);
  }
  else
  {
    shiftOut(dataPin, clockPin, LSBFIRST, CDS_LED_OFF);
  }

  digitalWrite(latchPin, HIGH);
  delay(1000);
}

long Get_Eco_Distance(int trig, int echo)
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  return pulseIn(echo, HIGH) / 58.2; 
}


void LED_off()
{
  analogWrite(
    
    
    , 255);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 255);
}

void LED_color(int r, int g, int b)
{
  analogWrite(RED, r);
  analogWrite(GREEN, g);
  analogWrite(BLUE, b);
}


