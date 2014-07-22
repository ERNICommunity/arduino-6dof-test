/*
 * Mmi.cpp
 *
 *  Created on: 22.07.2014
 *      Author: niklausd
 */

#include "Arduino.h"
#include "Timer.h"
#include "LcdKeypad.h"
#include "Mmi.h"

//-----------------------------------------------------------------------------

const unsigned int cUpdateDisplayInterval = 200; // Display update interval [ms]
class DisplayTimerAdapter : public TimerAdapter
{
private:
  Mmi* m_mmi;

public:
  DisplayTimerAdapter(Mmi* mmi)
  : m_mmi(mmi)
  { }

  void timeExpired()
  {
    if (0 != m_mmi)
    {
      m_mmi->updateDisplay();
    }
  }
};

//-----------------------------------------------------------------------------

class MyLcdKeypadAdapter : public LcdKeypadAdapter
{
public:
  MyLcdKeypadAdapter(Mmi* mmi)
  : m_mmi(mmi)
  { }

private:
  Mmi* m_mmi;

public:
  void handleKeyChanged(LcdKeypad::Key newKey)
  {
    Serial.print("MyLcdKeypadAdapter::handleKeyChanged(), newKey: ");
    Serial.println((LcdKeypad::NO_KEY == newKey)     ? "NO_KEY"     :
                   (LcdKeypad::SELECT_KEY == newKey) ? "SELECT_KEY" :
                   (LcdKeypad::LEFT_KEY == newKey)   ? "LEFT_KEY"   :
                   (LcdKeypad::UP_KEY == newKey)     ? "UP_KEY"     :
                   (LcdKeypad::DOWN_KEY == newKey)   ? "DOWN_KEY"   :
                   (LcdKeypad::RIGHT_KEY == newKey)  ? "RIGHT_KEY"  : "OOPS!! Invalid value!!");

    if ((0 != m_mmi) && (0 != m_mmi->adapter()) && (0 != m_mmi->lcdKeypad()))
    {
      if (LcdKeypad::UP_KEY == newKey)
      {
        m_mmi->lcdKeypad()->setBackLightOn(true);
      }
      else if (LcdKeypad::DOWN_KEY == newKey)
      {
        m_mmi->lcdKeypad()->setBackLightOn(false);
      }
      else if (LcdKeypad::LEFT_KEY == newKey)
      {
        // set Yaw angle to zero
        m_mmi->adapter()->resetYaw();
      }
    }
  }
};

//-----------------------------------------------------------------------------

Mmi::Mmi(MmiAdapter* adapter)
: m_lcdKeypad(new LcdKeypad())
, m_adapter(adapter)
, m_displayTimer(new Timer(new DisplayTimerAdapter(this), Timer::IS_RECURRING, cUpdateDisplayInterval))
{
  if (0 != m_lcdKeypad)
  {
    m_lcdKeypad->attachAdapter(new MyLcdKeypadAdapter(this));
    m_lcdKeypad->setBackLightOn(true);
  }
}

Mmi::~Mmi()
{
  delete m_lcdKeypad->adapter();
  m_lcdKeypad->attachAdapter(0);

  delete m_lcdKeypad;
  m_lcdKeypad = 0;

  delete m_displayTimer->adapter();
  m_displayTimer->attachAdapter(0);

  delete m_displayTimer;
  m_displayTimer = 0;
}

void Mmi::attachAdapter(MmiAdapter* adapter)
{
  m_adapter = adapter;
}

MmiAdapter* Mmi::adapter()
{
  return m_adapter;
}

LcdKeypad* Mmi::lcdKeypad()
{
  return m_lcdKeypad;
}

void Mmi::updateDisplay()
{
  if ((0 != m_adapter) && (0 != m_lcdKeypad))
  {
    m_lcdKeypad->setCursor(0, 0);

    m_lcdKeypad->print("Yaw: ");
    m_lcdKeypad->print(m_adapter->getYawAngle(), 1);
    m_lcdKeypad->print("\337"); // print the degree character °
    m_lcdKeypad->print("                ");
  }
}

