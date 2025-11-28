#include <Servo.h> 
#include <NewPing.h>

int trigPin = 2;   
int echoPin = 3;   
int in1 = 4;  
int in2 = 5;
int in3 = 6;
int in4 = 7;
int lduration = 0;
int ldistance = 0;
int duration = 0;
int distance = 0;
int rduration = 0;
int rdistance = 0;

NewPing sonar(trigPin, echoPin, 200);
Servo proservo;

void setup() {
  //pins
  Serial.begin(9600);
  pinMode(in1, OUTPUT);  
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT); 

  //servo  
  proservo.attach(9);
  proservo.write(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  ldistance=0;
  rdistance=0;
  delay(40);
  if (distance < 20)
  {
    //stop
    digitalWrite(in4, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in1, LOW);
    delay(100);
    //move back
    digitalWrite(in4, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in1, HIGH);
    delay(300);
    //stop
    digitalWrite(in4, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in1, LOW);
    delay(200);
    rdistance=lookRight();
    delay(200);
    ldistance=lookLeft();
    Serial.println("Object at front");
    if (rdistance > ldistance)
    {
      //move right
      digitalWrite(in4, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in1, HIGH);
      delay(1000);
      //stop
      digitalWrite(in4, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in1, LOW);
      delay(100);
      Serial.println("Object at left");
    }else{
      //move left
      digitalWrite(in4, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in2, HIGH);
      digitalWrite(in1, LOW);
      delay(1000);
      //stop
      digitalWrite(in4, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in1, LOW); 
      delay(100);
      Serial.println("Object at right");     
    }
  }
    else{
      //moveForward
      digitalWrite(in4, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in1, LOW);
      Serial.println("Object not detected moving front.");
    }
  distance=readPing();
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  Serial.println(cm);
  return cm;
}

int lookRight()
{
    proservo.write(25); 
    delay(500);
    int rdistance = readPing();
    delay(100);
    proservo.write(100); 
    return rdistance;
}

int lookLeft()
{
    proservo.write(170); 
    delay(500);
    int ldistance = readPing();
    delay(100);
    proservo.write(100); 
    return ldistance;
}