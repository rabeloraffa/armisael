#include <SoftwareSerial.h>

#include <Servo.h>
SoftwareSerial BTSerial(10,11);
Servo myservo;
int pos = 0;
char a;
int b = 0;
String c;
int motor = 0;
char z[3];
void setup() {
  myservo.attach(7);
 Serial.begin(115200);
  while(!Serial){
    ;
  }
  BTSerial.begin(9600);
  
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
      //Connection(BTSerial);
      if(BTSerial.available()>0){
        a = BTSerial.read();
        Serial.write(a);
        
       //BTSerial.write(a);
        if(a == 'A'){
          myservo.write(90);
          BTSerial.flush();
          delay(1000);
        }else if(a == 'B'){
          myservo.write(120);
          BTSerial.flush();
          delay(1000);
        }else if(a == 'Z'){
          myservo.write(150);
          BTSerial.flush();
          delay(1000);
          
        }
        }
        
        /*a = BTSerial.read();
        pos = BTSerial.parseInt();
        c = String(a);
        if(c.indexOf('\n') == 1
          //BTSerial.read() == '\n'
          ){
          myservo.write(pos);
          delay(15);
          Serial.print("Data Response: ");
          Serial.print(motor,DEC);
          Serial.print(pos,DEC);
        }*/
        
       // delay(4);
    /* a = a + BTSerial.read();
     Serial.println("ds:" + BTSerial.read());
     c = c + BTSerial.read();
     b = (int) BTSerial.parseInt();*/  
      //}
     /*if(BTSerial.read() == '\n'){
      pos = constrain(b, 0, 180);
      Serial.println("also:" + c);
      Serial.println(String(a));
      c = "";
      Serial.println("as:" + String(b));
      myservo.write(pos);
      Serial.println(pos);
      BTSerial.println("received:" + String(pos)); 
     }*/
  }
/*void Connection(SoftwareSerial ble){
  while(ble.available()>0){
    go();
    myservo.write(pos);
    ble.print(pos);
  }
}

void go(){
 int b = BTSerial.parseInt();
 if(BTSerial.read() == '\n'){
  if(pos != b){
   pos = b; 
  }
 }
  
}*/

