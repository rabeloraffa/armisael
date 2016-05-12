#include <SoftwareSerial.h>
#include <Wire.h>
#include <HDC1000.h>

SoftwareSerial BTSerial(10, 11);
HDC1000 mySeneor;
const int risPin = 12;
const int ledPin = 13;
int heartCounter = 0;
int risState = 0;
int lastRisState = 0;
int tCounter = 0;
int temptime = 0;
int prevtime = 0;
int state = 0;
int total[6] = {0, 0, 0, 0, 0, 0};
int sum = 0;
int attempt = 0;
boolean showr = true;
char c;
char d;
String sumstring;
void setup() {
  // put your setup code here, to run once:
  pinMode(risPin, INPUT);
  pinMode(ledPin, OUTPUT);
  //Serial.begin(9600);
  //BTSerial.begin(9600);
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  //Serial.println("Hi");
  BTSerial.begin(9600);
  mySensor.begin();
  //BTSerial.write("Hello");
}

void loop() {
  // put your main code here, to run repeatedly:
  risState = digitalRead(risPin);
  state = shu(risState, lastRisState);
  heartCounter = heartCounter + state;
  queuer();
  tCounter = tCounter + 4;
  delay(4);
}

int shu(int i, int j) {
  int z;
  if (i != j) {
    prevtime = temptime;
    temptime = tCounter;
    if (i == HIGH) {
      if (abs(temptime - prevtime) <= 10 || abs(temptime + 10000 - prevtime) <= 10) {
        z = 0;
      } else {
        z = 1;
      }
    }
    i = j;
  }
  return z;
}

boolean checkrate(int i) {
  if (i <= 4 || i >= 40) {
    return false;
  } else {
    return true;
  }
}

void queuer() {
  if (tCounter == 10000) {
    if (total[0] == 0) {
      if (checkrate(heartCounter)) {
        total[0] = heartCounter;
        BTSerial.write("initialization first step...");
        BTSerial.write("\n");
      } else {
        BTSerial.write("first step initialization failed...");
        BTSerial.write("\n");
      }
    } else if (total[1] == 0) {
      if (checkrate(heartCounter)) {
        total[1] = heartCounter;
        BTSerial.write("initialization second step...");
        BTSerial.write("\n");
      } else {
        BTSerial.write("second step initialization failed...");
        BTSerial.write("\n");
      }
    } else if (total[2] == 0) {
      if (checkrate(heartCounter)) {
        total[2] = heartCounter;
        BTSerial.write("initialization third step...");
        BTSerial.write("\n");
      } else {
        BTSerial.write("third step initialization failed...");
        BTSerial.write("\n");
      }
    } else if (total[3] == 0) {
      if (checkrate(heartCounter)) {
        total[3] = heartCounter;
        BTSerial.write("initialization forth step...");
        BTSerial.write("\n");
      } else {
        BTSerial.write("forth step initialization failed...");
        BTSerial.write("\n");
      }
    } else if (total[4] == 0) {
      if (checkrate(heartCounter)) {
        total[4] = heartCounter;
        BTSerial.write("its almost done hold on...");
      } else {
        BTSerial.write("fifth step initialization failed...");
      }
    } else if (total[5] == 0) {
      if (checkrate(heartCounter)) {
        total[5] = heartCounter;
        sum = total[0] + total[1] + total[2] + total[3] + total[4] + total[5];
        //sumstring = String(sum);
        //BTSerial.print(attempt);
        BTSerial.write("heartrate is:");
        BTSerial.print(sum);
        BTSerial.write("\n");
      } else {
        BTSerial.write("fall on the last step!");
        BTSerial.write("\n");
      }
    } else {
      if (checkrate(heartCounter)) {
        total[0] = total[1];
        total[1] = total[2];
        total[2] = total[3];
        total[3] = total[4];
        total[4] = total[5];
        total[5] = heartCounter;
      }
      sum = total[0] + total[1] + total[2] + total[3] + total[4] + total[5];
      attempt++;
      if (sum >= 120 && sum < 160) {
        c = 'B';
      } else if (sum >= 160 ) {
        c = 'C';
      } else {
        c = 'A';
      }
      showr = not showr;
      if (showr) {
        digitalWrite(12, HIGH);
      } else {
        digitalWrite(12, LOW);
      }

      //sumstring = String(sum);
      // BTSerial.print(attempt);
     // if (BTSerial.available() > 0) {
        BTSerial.write("heartrate is ");
        BTSerial.print(sum);
        BTSerial.print(c);
        BTSerial.write("\n");
        d = BTSerial.read();
        BTSerial.write("temperature: ");
        BTSerial.print(mySensor.getTemp());
        BTSerial.write("\n");
        BTSerial.write("humidity: ");
        BTSerial.print(mySensor.getHumi());
        BTSerial.write("\n");
        //Serial.println(d);
      //}

    }
    heartCounter = 0;
    tCounter = 0;
  }
}

