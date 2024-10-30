#define ECHO 13
#define TRIG 12

#define RED   10
#define GREEN 9
#define BLUE  8


void setup()
{
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop()
{
  long dist = Get_Eco_Distance(TRIG, ECHO);

  LED_off();

  if(dist < 10) LED_color(0,255,255);      //red
  else if(dist < 20) LED_color(255,0,255); //green
  else if(dist < 30) LED_color(255,255,0); //blue
  else LED_off();

  delay(100);
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
  analogWrite(RED, 255);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 255);
}

void LED_color(int r, int g, int b)
{
  analogWrite(RED, r);
  analogWrite(GREEN, g);
  analogWrite(BLUE, b);
}


