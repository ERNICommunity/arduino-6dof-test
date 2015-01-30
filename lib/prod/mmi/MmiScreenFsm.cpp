/*
 * MmiScreenFsm.cpp
 *
 *  Created on: 30.01.2015
 *      Author: scan
 */

#include "Arduino.h"

#include <Mmi.h>
#include <MmiScreen.h>
#include <MmiScreenFsm.h>
#include <MmiScreenState.h>

MmiScreenFsm::MmiScreenFsm(Mmi* mmi)
: m_state(0)
{
  m_state = MmiAngleScreenState::Instance();
  m_state->attachScreen(new MmiAngleScreen(mmi));
  Serial.print("MmiScreenFsm ctor: created state ");
  Serial.println(m_state->toString());

  m_state = MmiAccelScreenState::Instance();
  m_state->attachScreen(new MmiAccelScreen(mmi));
  Serial.print("MmiScreenFsm ctor: created state ");
  Serial.println(m_state->toString());

}

MmiScreenFsm::~MmiScreenFsm()
{
  delete MmiAngleScreenState::Instance()->screen();
  MmiAngleScreenState::Instance()->attachScreen(0);

  delete MmiAccelScreenState::Instance()->screen();
  MmiAccelScreenState::Instance()->attachScreen(0);
}

void MmiScreenFsm::select()
{
  if (0 != m_state)
  {
    Serial.print("MmiScreenFsm::select() on state: ");
    Serial.println(m_state->toString());
    m_state->select(this);
  }
}

void MmiScreenFsm::left()
{
  if (0 != m_state)
  {
    m_state->left(this);
  }
}

void MmiScreenFsm::right()
{
  if (0 != m_state)
  {
    m_state->right(this);
  }
}

void MmiScreenFsm::up()
{
  if (0 != m_state)
  {
    m_state->up(this);
  }
}

void MmiScreenFsm::down()
{
  if (0 != m_state)
  {
    m_state->down(this);
  }
}

void MmiScreenFsm::changeState(MmiScreenState* state)
{
  m_state = state;
  if (0 != m_state)
  {
    m_state->entry(this);
  }
}

void MmiScreenFsm::updateDisplay()
{
  if (0 != m_state)
  {
    m_state->updateDisplay();
  }
}
