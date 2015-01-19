/*
 * Mmi.h
 *
 *  Created on: 22.07.2014
 *      Author: niklausd
 */

#ifndef MMI_H_
#define MMI_H_

class LcdKeypad;
class Timer;

//-----------------------------------------------------------------------------

class MmiAdapter
{
public:
  virtual ~MmiAdapter() { }

  virtual void sampleAngles() = 0;

  virtual float getYawAngle() = 0;
  virtual float getRollAngle() = 0;
  virtual float getPitchAngle() = 0;

  virtual void resetAngles() = 0;

protected:
  MmiAdapter() { }

private: // forbidden default functions
  MmiAdapter& operator = (const MmiAdapter& src);  // assignment operator
  MmiAdapter(const MmiAdapter& src);               // copy constructor
};

//-----------------------------------------------------------------------------

class Mmi
{
public:
  Mmi(MmiAdapter* adapter);
  virtual ~Mmi();

  void attachAdapter(MmiAdapter* adapter);
  MmiAdapter* adapter();

  LcdKeypad* lcdKeypad();

  void updateDisplay();

private:
  LcdKeypad* m_lcdKeypad;
  MmiAdapter* m_adapter;
  Timer* m_displayTimer;

private: // forbidden default functions
  Mmi& operator = (const Mmi& src); // assignment operator
  Mmi(const Mmi& src);              // copy constructor
};

#endif /* MMI_H_ */
