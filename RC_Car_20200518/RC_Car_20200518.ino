#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2); // RX, TX

#define TRIG 11
#define ECHO 12

int in1 = 5;
int in2 = 6;
int in3 = 9;
int in4 = 10;
int vel = 255;
int count = 0;

char input = 'g';



void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }

  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}


void loop() { // run over and over

  // 트리거 초기화 작업
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long distance = pulseIn(ECHO, HIGH) / 58.2;
  delay(1);

  if (mySerial.available()) {
    input = mySerial.read();
    Serial.println(input);
  }
  if (Serial.available()) {
    mySerial.println(Serial.read());
  }

  if (distance < 40) {
    if (input == '1') {
      input = '0';
    }
  } else {

    //전진
    if (input == '1') {
      analogWrite(in1, 0);
      analogWrite(in3, 0);
      analogWrite(in2, vel);
      analogWrite(in4, vel);
    }


    //전진 조금
    if (input == '8') {
      if (count < 3) {
        analogWrite(in1, 0);
        analogWrite(in3, 0);
        analogWrite(in2, vel);
        analogWrite(in4, vel);
        delay(50);
        count++;
      } else {
        input = '0';
        count = 0;
      }
    }


  }



  //후진
  if (input == '2') {
    analogWrite(in1, vel);
    analogWrite(in3, vel);
    analogWrite(in2, 0);
    analogWrite(in4, 0);
  }

  //좌회전
  if (input == '3') {
    if (count < 2) {
      analogWrite(in1, 0);
      analogWrite(in3, 0);
      analogWrite(in2, 0);
      analogWrite(in4, vel * 0.7);
      delay(100);
      count++;
    } else {
      input = '1';
      count = 0;
    }
  }


  //우회전
  if (input == '4') {
    if (count < 2) {
      analogWrite(in1, 0);
      analogWrite(in3, 0);
      analogWrite(in2, vel * 0.7);
      analogWrite(in4, 0);
      delay(100);
      count++;
    } else {
      input = '1';
      count = 0;
    }
  }


  //멈춤
  if (input == '0') {
    analogWrite(in1, 0);
    analogWrite(in2, 0);
    analogWrite(in3, 0);
    analogWrite(in4, 0);
  }


  //좌회전 뒤로 조금
  if (input == '6') {
    if (count < 3) {
      analogWrite(in1, 0);
      analogWrite(in3, vel * 0.7);
      analogWrite(in2, 0);
      analogWrite(in4, 0);
      delay(50);
      count++;
    } else {
      input = '0';
      count = 0;
    }
  }

  //우회전 뒤로 조금
  if (input == '7') {
    if (count < 3) {
      analogWrite(in1, vel * 0.7);
      analogWrite(in3, 0);
      analogWrite(in2, 0);
      analogWrite(in4, 0);
      delay(50);
      count++;
    } else {
      input = '0';
      count = 0;
    }
  }




  //후진 조금
  if (input == '9') {
    if (count < 3) {

      analogWrite(in1, vel);
      analogWrite(in3, vel);
      analogWrite(in2, 0);
      analogWrite(in4, 0);
      delay(50);
      count++;
    } else {
      input = '0';
      count = 0;
    }
  }

  //자동 모드
  if (input == '5') {
    autoMode();
    autoMode();
    autoMode2();
    autoMode2();
  }
}



void autoMode() {
  analogWrite(in1, 0);
  analogWrite(in3, 0);
  analogWrite(in2, vel * 0.7);
  analogWrite(in4, 0);
  delay(2000);

  analogWrite(in1, 0);
  analogWrite(in3, 0);
  analogWrite(in2, vel);
  analogWrite(in4, vel);
  delay(500);

  analogWrite(in1, 0);
  analogWrite(in3, 0);
  analogWrite(in2, 0);
  analogWrite(in4, vel * 0.7);
  delay(2000);

  analogWrite(in1, 0);
  analogWrite(in3, 0);
  analogWrite(in2, vel);
  analogWrite(in4, vel);
  delay(500);

}

void autoMode2() {
  
  analogWrite(in1, 0);
  analogWrite(in3, 0);
  analogWrite(in2, vel);
  analogWrite(in4, vel);
  delay(50);

  analogWrite(in1, vel);
  analogWrite(in3, vel);
  analogWrite(in2, 0);
  analogWrite(in4, 0);
  delay(50);

}
