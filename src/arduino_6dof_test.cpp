// Do not remove the include below
#include "arduino_6dof_test.h"

#include "Mmi.h"
#include "AMmiAdapter.h"
#include "Timer.h"
#include "CommunicationUtils.h"
#include "FreeSixIMU.h"
#include <Wire.h>

float q[4]; //hold q values

// Set the FreeSixIMU object
FreeSixIMU* my3IMU = 0;

Mmi* mmi = 0;
AMmiAdapter* aMmiAdapter = 0;

//The setup function is called once at startup of the sketch
void setup()
{
  my3IMU = new FreeSixIMU();

  aMmiAdapter = new AMmiAdapter(my3IMU);
  mmi = new Mmi(aMmiAdapter);

  Serial.begin(115200);
  Wire.begin();

  delay(5);
  my3IMU->init(); //begin the IMU
  delay(5);
}

// The loop function is called in an endless loop
void loop()
{
  my3IMU->getQ(q);
  serialPrintFloatArr(q, 4);
  Serial.println("");

  delay(60);
  yield();
}
