// Do not remove the include below
#include "arduino_6dof_test.h"

#include "Mmi.h"
#include "AMmiAdapter.h"
#include "Timer.h"
#include "CommunicationUtils.h"
#include "FreeSixIMU.h"
#include "RamUtils.h"
#include <Wire.h>

#define DEBUG_RAM 1  //Printing free Ram space with serial monitor

float q[4]; //hold q values

// Set the FreeSixIMU object
FreeSixIMU* my3IMU = 0;

Mmi* mmi = 0;
AMmiAdapter* aMmiAdapter = 0;

Timer* ramDebugTimer = 0;
const unsigned int c_ramDbgInterval = 10000;
class RamDebugTimerAdapter : public TimerAdapter
{
  void timeExpired()
  {
    Serial.print("Free RAM: ");
    Serial.println(RamUtils::getFreeRam(), DEC);
  }
};

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

#if DEBUG_RAM
  // Print free RAM periodically
  Serial.print("Free RAM: ");
  Serial.println(RamUtils::getFreeRam(), DEC);
  ramDebugTimer = new Timer(new RamDebugTimerAdapter(), Timer::IS_RECURRING, c_ramDbgInterval);
#endif
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
