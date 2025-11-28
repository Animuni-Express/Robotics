//Maze solver robot with 3 ultrasonic sound sensors
//Notes are present to explain the lines
//Self-Explainatory lines are not commented

//Code is from below{
//defining right, left and center values

//Right HC-SR04
float rightdu = 0;
float rightdi = 0;

//Center HC-SR04
float centerdu = 0;
float centerdi = 0;

//Left HC-SRO4
float leftdu = 0;
float leftdi = 0;

void setup(){
 //Defining HC-SR04 pins
 //Right 
 pinMode(8, OUTPUT);//Trig
 pinMode(11, INPUT);//Echo
 //Center
 pinMode(12, OUTPUT);//Trig
 pinMode(9, INPUT);//Echo
 //Left
 pinMode(10, OUTPUT);//Trig
 pinMode(6, INPUT);//Echo
  
 //Defining Motor Driver pins
 pinMode(2, OUTPUT);//Input 1
 pinMode(3, OUTPUT);//Input 2
 pinMode(4, OUTPUT);//Input 3
 pinMode(5, OUTPUT);//Input 4
  
 Serial.begin(9600);//Booting serial monitor for debugging
}

void loop(){
  
 //Defining the functions(check below)
 Right();
 Center();
 Left();
 RobotMovement();
}

void Right() //The code to get Right sensor value
{
  //Sending the signal
  digitalWrite(8,LOW);
  delayMicroseconds(2);
  digitalWrite(8,HIGH);
  delayMicroseconds(10);
  digitalWrite(8,LOW);
  
  //Recieveing the signal 
  rightdu=pulseIn(11,HIGH);
    
  //Math to calculate distance
  rightdi=(rightdu/2)*(0.0343);
  //Printing distance in Serial Monitor
  Serial.print("Right HC-SRO4 Value=");
  Serial.println(rightdi);
}

void Center()
{
//Sending the signal
  digitalWrite(12,LOW);
  delayMicroseconds(2);
  digitalWrite(12,HIGH);
  delayMicroseconds(10);
  digitalWrite(12,LOW);
  
  //Recieveing the signal 
  centerdu=pulseIn(9,HIGH);
   
  //Math to calculate distance
  centerdi=(centerdu/2)*(0.0343);
  //Printing distance in Serial Monitor
  Serial.print("Center HC-SRO4 Value=");
  Serial.println(centerdi);  
}

void Left()
{
  //Sending the signal
  digitalWrite(10,LOW);
  delayMicroseconds(2);
  digitalWrite(10,HIGH);
  delayMicroseconds(10);
  digitalWrite(10,LOW);
  
  //Recieveing the signal 
  leftdu=pulseIn(6,HIGH);
    
  //Math to calculate distance
  leftdi=(leftdu/2)*(0.0343);
  //Printing distance in Serial Monitor
  Serial.print("Left HC-SRO4 Value=");
  Serial.println(leftdi);
}

void RobotMovement()// The main movements of the robot
{
  if (centerdi > 10)//Checking if gap is PRESENT in center HC-SR04
  {
    //Code to make robot move straight
    digitalWrite(2, HIGH);//input 1 
    digitalWrite(3, LOW);//input 2
    digitalWrite(4, HIGH);//input 3
    digitalWrite(5, LOW);//input 4
    Serial.println("Robot moving straight ");
  }
  
  else if(centerdi < 10)//Checking if gap is NOT PRESENT in center HC-SR04
  Serial.println("Wall at front");
  {
    
    if(leftdi > rightdi);//Comparing right and left HC-SR04
    Serial.println("Wall at Right");
    {
     digitalWrite(2, HIGH);//input 1
     digitalWrite(3, LOW);//input 2
     digitalWrite(4, HIGH);//input 3
     digitalWrite(5, HIGH);//input 4
     Serial.println("Robot turning left");
    }
    
    if (leftdi < rightdi);//Comparing right and left HC-SR04
    Serial.println("Wall at left");
    {
     digitalWrite(2, HIGH);//input 1 
     digitalWrite(3, HIGH);//input 2
     digitalWrite(4, LOW);//input 3
     digitalWrite(5, HIGH);//input 4
     Serial.println("Robot Turning Right");
    }
    
    if (leftdi<10 && rightdi<10)//When Robot reaches Dead End
    Serial.println("Robot At Dead End, Wall at all 3 sides");
    {
     digitalWrite(2, LOW);//input 1
     digitalWrite(3, HIGH);//input 2
     digitalWrite(4, LOW);//input 3
     digitalWrite(5, HIGH);//input 4
     Serial.println("Robot Moving Reverse");
    }
   }
  delay(1000);
}


