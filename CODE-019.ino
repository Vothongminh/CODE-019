//#VTM https://www.youtube.com/c/VTMVlogVoThongMinh
#include <Wire.h>
#include <LiquidCrystal_I2C.h>                        //https://drive.google.com/file/d/1lpJyuODmZXfi7wwBM2B79BqBIBmBfanS/view?usp=sharing
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define stepPin  4 //clk+
#define dirPin  5 //cw+
boolean demStart = 0;
unsigned long int time1, a, b, aa, bb, V, S = 0;
#define start 12
#define stopp 11
//...............................................
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(start, INPUT_PULLUP);
  pinMode(stopp, INPUT_PULLUP);
  lcd.setCursor(4, 0);
  lcd.print("Breathing");
  delay(700);
  //chaychu();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Speed :");
  lcd.setCursor(0, 1);
  lcd.print("Volume:");
  lcd.setCursor(11, 0);
  lcd.print("(t/m)");
  lcd.setCursor(11, 1);
  lcd.print("(%)");
}
//...............................................
void loop() {
  Var();
  sw();
  while (demStart == 1) {
    Serial.println("Forward");
    digitalWrite(dirPin, LOW);
    for (int x = 0; x < bb; x++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(3125 / aa);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(3125 / aa);
      sw();
    }
    Serial.println("delay");
    time1 = millis();
    while ((millis() - time1) < 1000) {
      sw();
    }
    Serial.println("Reverse");
    digitalWrite(dirPin, HIGH);
    for (int x = 0; x < bb; x++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(3125 / aa);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(3125 / aa);
      sw();
    }
    Serial.println("delay");
    time1 = millis();
    while ((millis() - time1) < 1000) {
      sw();
      Var();
    }
  }
}
//...............................................
void Var() {
  a = analogRead(A0);            // speed
  aa = map(a, 0, 1023, 1, 30);   //0.1 - 3rps
  b = analogRead(A1);            //interval
  bb = map(b, 0, 1023, 0, 10400);// 0 - 6.5r 1:16step
  V = map(bb, 0, 10400, 0, 90);  //Volume(%)
  S = 60000000 / (2 * (1000000 + 2 * bb * 3125 / aa));

  Serial.print("speed: ");
  Serial.print(aa);
  Serial.print(" ,interval: ");
  Serial.println(bb);

  lcd.setCursor(8, 0);
  lcd.print(S);
  lcd.setCursor(8, 1);
  lcd.print(V);
  if (S < 10 ) {
    lcd.setCursor(9, 0);
    lcd.print(' ');
  }
  if (V < 10 ) {
    lcd.setCursor(9, 1);
    lcd.print(' ');
  }
}
//...............................................
void sw() {
  if (digitalRead(start) == 0) {
    demStart = 1;
  }
  if (digitalRead(stopp) == 0) {
    Serial.println("stop");
    demStart = 0;
  }
}
//.........................................................................
void chaychu()
{
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    lcd.scrollDisplayRight();
    delay(150);
  }
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }
}
