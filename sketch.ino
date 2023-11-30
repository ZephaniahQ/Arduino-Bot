#include <NewPing.h>
#include <Servo.h>
#include <AFMotor.h>

 //hc-sr04 sensor
#define TRIGGER_PIN A1
#define ECHO_PIN A0
#define max_distance 80

//ir sensor
#define irLeft A2
#define irRight A3

//buzzer
#define buzzer A4

//motor
#define MAX_SPEED 180
#define MAX_SPEED_OFFSET 20

Servo servo;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, max_distance);

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

int distance = 0;
int leftDistance;
int rightDistance;
boolean object;

void setup() {
  Serial.begin(9600);
  pinMode(irLeft, INPUT);
  pinMode(irRight, INPUT);
  servo.attach(9);
  servo.write(83);
  pinMode(buzzer, OUTPUT);
  motor1.setSpeed(115);
  motor2.setSpeed(115);
  motor3.setSpeed(115);
  motor4.setSpeed(115);
}

void loop() {
  if (digitalRead(irLeft) == 0 && digitalRead(irRight) == 0) {
    objectAvoid();
    //forword
  } else if (digitalRead(irLeft) == 0 && digitalRead(irRight) == 1) {
    objectAvoid();
    Serial.println("TL");
    //leftturn
    moveLeft();
  } else if (digitalRead(irLeft) == 1 && digitalRead(irRight) == 0) {
    objectAvoid();
    Serial.println("TR");
    //rightturn
    moveRight();
  } else if (digitalRead(irLeft) == 1 && digitalRead(irRight) == 1) {
    //Stop
    Stop();
  }
}

void objectAvoid() {
  distance = getDistance();
  if (distance <= 40) {
    //stop
    Stop();
    beep(2);
    Serial.println("Stop");
    
    lookLeft();
    lookRight();
    delay(100);
    if (rightDistance <= leftDistance) {
      //left
      object = true;
      turn();
      Serial.println("moveLeft");
    } else {
      //right
      object = false;
      turn();
      Serial.println("moveRight");
    }
    delay(100);
  } else {
    //forword
    Serial.println("moveforword");
    moveForward();
  }
}

int getDistance() {
  delay(50);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 100;
  }
  return cm;
}

int lookLeft() {
  //lock left
  servo.write(130);
  delay(500);
  leftDistance = getDistance();
  delay(150);
  servo.write(83);
  Serial.print("Left:");
  Serial.print(leftDistance);
  return leftDistance;
  delay(100);
}

int lookRight() {
  //lock right
  servo.write(40);
  delay(500);
  rightDistance = getDistance();
  delay(150);
  servo.write(83);
  Serial.print(" ");
  Serial.print("Right:");
  Serial.println(rightDistance);
  return rightDistance;
  delay(100);
}

void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveBackward() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void turn() {
  if (object == false) {
    Serial.println("turn Right");
    moveBackward();
    delay(500);
    moveLeft();
    delay(850);
    moveForward();
    delay(1220);
    moveRight();
    delay(800);
    if (digitalRead(irRight) == 1) {
      loop();
    } else {
      moveForward();
    }
  } else {
    Serial.println("turn left");
    moveBackward();
    delay(500);
    moveRight();
    delay(980);
    moveForward();
    delay(1250);
    moveLeft();
    delay(800);
    if (digitalRead(irLeft) == 1) {
      loop();
    } else {
      moveForward();
    }
  }
}

void moveRight() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveLeft() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void beep(int t) {
  switch (t) {
    case 1: {
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
      break;
    }
    case 2: {
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
    }
  }
}
