#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int lm35Pin = 0;

// segments
int a = 5;
int b = 13;
int c = 10;
int d = 8;
int e = 7;
int f = 4;
int g = 11;
int pt = 9;

int d1 = 6;
int d2 = 3;
int d3 = 2;
int d4 = 12;


const int DELAYTIME = 1000;
int counter = 0;

float voltage = 5;
float temperature = 20.0;

void setup()
{
  Serial.begin(9600);
  lcd.begin();

  // LCD
  lcd.backlight();
  lcd.print("Hello, world!");

  // LM35
  for(int i = 2; i < 14; i++)
  {
    pinMode(i, OUTPUT);
  }

  delay(1000);
}

void loop()
{
  // loop문 500번 반복할 때 마다 온도를 한 번 체크
  if(counter%500 == 0)
  {
    float LM35_SensorValue = analogRead(A0);
    temperature = (LM35_SensorValue / 1023) * voltage * 100;

    Serial.print("temperature : ");
    Serial.println(temperature);
    
    counter = 0;
  }
  counter++;

  // 00.0C 형태로 출력

  // 세그먼트를 HIGH로 만듦
  selectDigit(1);
  // HIGH 세그먼트에 적절한 자리값의 숫자를 보냄
  sendDigit(Get_Ten_Digit(temperature));
  delayMicroseconds(DELAYTIME);
  // LOW 상태로 만듦
  digitalWrite(d1, LOW);
  
  selectDigit(2);
  sendDigit(Get_One_Digit(temperature));
  // 소수점 자리를 위한 점 출력
  point();
  delayMicroseconds(DELAYTIME);
  digitalWrite(d2, LOW);

  selectDigit(3);
  sendDigit(Get_Decimal_Digit(temperature));
  delayMicroseconds(DELAYTIME);
  digitalWrite(d3, LOW);

  digitalWrite(pt, LOW);
  
  selectDigit(4);
  // 섭씨를 나타낼 C 문자 출력
  Degree();
  delayMicroseconds(DELAYTIME);
  digitalWrite(d4, LOW);
}

// 숫자
void One()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(pt, HIGH);
}

void Two()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
  digitalWrite(pt, HIGH);
}

void Three()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
  digitalWrite(pt, HIGH);
}

void Four()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(pt, HIGH);
}

void Five()
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(pt, HIGH);
}
void Six()
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(pt, HIGH);
}
void Seven()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(pt, HIGH);
}

void Eight()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(pt, HIGH);
}

void Nine()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(pt, HIGH);
}
void Zero()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
  digitalWrite(pt, HIGH);
}

// C문자 출력
void Degree()
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
  digitalWrite(pt, HIGH);
}

void point()
{
  digitalWrite(pt, LOW);
}

// 세그먼트의 자리 수 정하기
// 해당 자리를 HIGH 상태로 바꿈
void selectDigit(int d)
{
  switch(d)
  {
    case 1: digitalWrite(d1, HIGH); break;
    case 2: digitalWrite(d2, HIGH); break;
    case 3: digitalWrite(d3, HIGH); break;
    default: digitalWrite(d4, HIGH); break;
  }
}

// HIGH상태의 세그먼트에 정해진 문자(숫자)를 넣음
void sendDigit(int d)
{
  switch(d)
  {
    case 1:  One();      break;
    case 2:  Two();      break;
    case 3:  Three();    break;
    case 4:  Four();     break;
    case 5:  Five();     break;
    case 6:  Six();      break;
    case 7:  Seven();    break;
    case 8:  Eight();    break;
    case 9:  Nine();     break;
    case 10: Degree();   break;
    default: Zero();     break;
  }
}

// 십의 자리수 구하기
int Get_Ten_Digit(float f)
{
  float div = f / 10.0;
  return (int)div;
}

//일의 자리수 구하기
int Get_One_Digit(float f)
{
  float div = f - (10.0 * Get_Ten_Digit(f));

  return div;
}

//소수점 첫자리 구하기
int Get_Decimal_Digit(float f)
{
  float div = f - (10.0 * Get_Ten_Digit(f)) - Get_One_Digit(f);
  
  return (int)(div * 10);
}