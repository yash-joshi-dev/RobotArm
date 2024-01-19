#include <Servo.h>

const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = A0; // analog pin connected to X output
const int Y_pin = A1; // analog pin connected to Y output

Servo rotation, outIn, height, claw;
int x, y;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  rotation.attach(9);
  outIn.attach(10);
  height.attach(11);
  claw.attach(3);
}

void direction(Servo & servo, int t) {
  int curr = servo.read();

  if(t < 500) {
    servo.write(curr == 0 ? 0 : curr - 1);  
  }
  else if (t > 522) {
    servo.write(curr < 180 ? curr + 1 : 180);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  x = analogRead(X_pin);  
  y = analogRead(Y_pin);
  bool pressed = !digitalRead(SW_pin);
  Serial.print("Switch: ");
  Serial.println(pressed);
  if (pressed) {
    direction(height, 1023-x);
    direction(claw, y);
  } else {
    direction(rotation, y);
    direction(outIn, 1023-x);
  }

  
  delay(10);
}
