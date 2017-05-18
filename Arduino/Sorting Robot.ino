/*
  Debugging Mode , Waiting Mode (DEFAULT) , Collecting Mode , Sorting Mode
*/

#include <Servo.h>

// Defining LEDs pins
const int waitLED = 8;
const int sortLED = 9;

// Create Servo objects
Servo baseServo;
Servo mainPairServo;
Servo midServo;
Servo endServo;
Servo actServo;

// Wait position
const int basePos = 80;
const int mainPairPos = 150;
const int midPos = 160;
const int endPos = 150;
const int actPos = 50;

// Variables for last and current mode
int currentMode = 1;
int lastMode;

// Delay time betweein servo movements
const int waitForServo = 100;

// Object data
String catchedString;
char data[2];


void setup()
{
  Serial.begin(9600);

  // set starting positions
  baseServo.attach(31);
  baseServo.write(basePos);
  delay(1000);

  mainPairServo.attach(33);
  mainPairServo.write(mainPairPos);

  delay(1000);

  midServo.attach(35);
  midServo.write(midPos);
  delay(1000);

  endServo.attach(37);
  endServo.write(endPos);
  delay(1000);

  actServo.attach(39);
  actServo.write(actPos);

  // defining pins modes for LEDs
  pinMode(waitLED , OUTPUT);
  pinMode(sortLED , OUTPUT);
}


void loop ()
{
  while (currentMode == 1) // Waiting Mode
  {
    if (lastMode != currentMode)
    {
      Serial.println("<####  WAITING MODE  ####>");
      // Changing LEDs
      digitalWrite(waitLED , HIGH);
      digitalWrite(sortLED , LOW);
      lastMode = currentMode;
    }
    wait();
  }

  while (currentMode == 2) // Collecting Mode
  {
    if (lastMode != currentMode)
    {
      Serial.println("<####  Collecting Mode  ####>");
      // Changing LEDs
      digitalWrite(waitLED , LOW);
      digitalWrite(sortLED , HIGH);
      lastMode = currentMode;
    }
    if (data[0] == 'L')
    {
      Serial.println("<         Collecting from LEFT          >");
      delay(1000);
      collectLeft();
    }

    else if (data[0] == 'C')
    {
      Serial.println("<         Collecting from MIDDLE          >");
      delay(1000);
      collectMiddle();
    }
    else if (data[0] == 'R')
    {
      Serial.println("<         Collecting from RIGHT          >");
      delay(1000);
      collectRight();
    }
    delay(1000);
    Serial.println("<         Object Collected          >");
    currentMode = 3;
    break;
  }

  while (currentMode == 3) // Sorting Mode
  {
    if (lastMode != currentMode)
    {
      Serial.println("<####  Sorting Mode  ####>");
      // Changing LEDs
      digitalWrite(waitLED , LOW);
      digitalWrite(sortLED , HIGH);
      lastMode = currentMode;
    }

    if (data[1] == 'R')
    {
      Serial.println("<         Sorting RED          >");
      sortRed();
    }
    else if (data[1] == 'B')
    {
      Serial.println("<         Sorting Blue          >");
      sortBlue();
    }
    else if (data[1] == 'G')
    {
      Serial.println("<         Sorting Green          >");
      sortGreen();
    }

    delay(1000);
    Serial.println("<         Object Sorted          >");

    data[0] = 0;
    data[1] = 0;

    goToWaitPosition();
    currentMode = 1;

  }

  while (currentMode == 5)
  {
    if (Serial.available())
    {
      delay(1000);
      collectMiddle();
      delay(1000);
      goToWaitPosition();
      delay(1000);
      sortGreen();
      delay(1000);
      goToWaitPosition();
      currentMode++;
      Serial.flush();
      break;
    }

  }

}

void wait()
{
  if (Serial.available() == 2)
  {
    delay(100);
    data[0] = Serial.read();
    data[1] = Serial.read();
    Serial.println("<         READINGS COLLECTED          >");
    currentMode = 2;
    Serial.flush();
  }

  if (data[0] == 0 || data[1] == 0) {
    Serial.println("<         WAITING FOR READINGS          >");
    Serial.flush();
    delay(1000);
  }


}

void collectLeft()
{
  moveMotor(baseServo , 140);
  moveMotor(endServo , 30);
  delay(500);
  moveMotor(mainPairServo , 87);
  moveMotor(midServo , 110);
  moveMotor(actServo , 50);
  delay(1000);
  moveMotor(endServo , 60);
  delay(1000);
  moveMotor(actServo , 130);
  delay(1000);
  goToWaitPosition();

}

void collectMiddle()
{
  moveMotor(baseServo , 160);
  moveMotor(endServo , 10);
  delay(500);
  moveMotor(mainPairServo , 87);
  moveMotor(midServo , 90);
  moveMotor(actServo , 50);
  delay(1000);
  moveMotor(endServo , 33);
  delay(1000);
  moveMotor(actServo , 130);
  delay(1000);
  goToWaitPosition();
}

void collectRight()
{
  moveMotor(baseServo , 180);
  moveMotor(endServo , 30);
  delay(500);
  moveMotor(mainPairServo , 95);
  moveMotor(midServo , 90);
  moveMotor(actServo , 50);
  delay(1000);
  moveMotor(endServo , 45);
  delay(1000);
  moveMotor(actServo , 130);
  delay(1000);
  goToWaitPosition();

}

void sortRed()
{
  moveMotor(baseServo , 53);
  moveMotor(endServo , 60);
  delay(500);
  moveMotor(mainPairServo , 85);
  moveMotor(midServo , 110);
  moveMotor(actServo , 50);
  delay(1000);
  moveMotor(actServo , 50);
  delay(1000);
  goToWaitPosition();
}

void sortGreen()
{
  moveMotor(baseServo , 70);
  moveMotor(endServo , 35);
  delay(500);
  moveMotor(mainPairServo , 85);
  moveMotor(midServo , 100);
  moveMotor(actServo , 50);
  delay(1000);
  moveMotor(actServo , 50);
  delay(1000);
  goToWaitPosition();
}

void sortBlue()
{
  moveMotor(baseServo , 95);
  moveMotor(endServo , 45);
  delay(500);
  moveMotor(mainPairServo , 85);
  moveMotor(midServo , 110);
  moveMotor(actServo , 50);
  delay(1000);
  moveMotor(actServo , 50);
  delay(1000);
  goToWaitPosition();
}

void goToWaitPosition()
{
  moveMotor(midServo , 160);
  delay(500);
  moveMotor(mainPairServo , 150);
  delay(500);
  moveMotor(endServo , 140);
  delay(500);
  moveMotor(baseServo , 80);
}


void moveMotor(Servo ser , int deg)
{
  int currentPos = ser.read();

  if (currentPos < deg)
  {
    for (int i = currentPos ; i < deg ; i ++)
    {
      ser.write(i);
      delay(10);
    }
  }

  else if (currentPos > deg)
  {
    for (int i = currentPos ; i > deg ; i--)
    {
      ser.write(i);
      delay(10);
    }
  }
}

