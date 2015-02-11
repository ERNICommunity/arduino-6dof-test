/*
 * MmiScreenState.cpp
 *
 *  Created on: 29.01.2015
 *      Author: scan
 */

#include "Arduino.h"

#include <Mmi.h>
#include <MmiScreenState.h>
#include <MmiScreen.h>
#include <MmiScreenFsm.h>

MmiScreenState::MmiScreenState()
: m_screen(0)
{ }

MmiScreenState::~MmiScreenState()
{ }

void MmiScreenState::updateDisplay()
{
  screen()->updateDisplay();
}


//-----------------------------------------------------------------------------

MmiScreenState* MmiAngleScreenState::s_instance = 0;

MmiScreenState* MmiAngleScreenState::Instance()
{
  if (0 == s_instance)
  {
    s_instance = new MmiAngleScreenState();
  }
  return s_instance;
}

const char* MmiAngleScreenState::toString()
{
  return "AngleScreenState";
}

void MmiAngleScreenState::select(MmiScreenFsm* fsm)
{
  if ((0 != fsm) && (0 != screen()) && (0 != screen()->mmi()))
  {
      fsm->changeState(MmiAccelScreenState::Instance());
  }
}

void MmiAngleScreenState::left(MmiScreenFsm* fsm)
{
  if (0 != screen())
  {
    screen()->setCursorLeft();
  }
}

void MmiAngleScreenState::up(MmiScreenFsm* fsm)
{
  if (0 != screen())
  {
    screen()->setCursorUp();
  }
}

void MmiAngleScreenState::down(MmiScreenFsm* fsm)
{
  if (0 != screen())
  {
    screen()->setCursorDown();
  }
}

void MmiAngleScreenState::entry(MmiScreenFsm* fsm)
{
  Serial.println(toString());
  updateDisplay();
}

//-----------------------------------------------------------------------------

MmiScreenState* MmiAccelScreenState::s_instance = 0;

MmiScreenState* MmiAccelScreenState::Instance()
{
  if (0 == s_instance)
  {
    s_instance = new MmiAccelScreenState();
  }
  return s_instance;
}

const char* MmiAccelScreenState::toString()
{
  return "AccelScreenState";
}

void MmiAccelScreenState::select(MmiScreenFsm* fsm)
{
  if ((0 != screen()) && (0 != fsm))
  {
      fsm->changeState(MmiMagnScreenState::Instance());
  }
}

void MmiAccelScreenState::left(MmiScreenFsm* fsm)
{
  if (0 != screen())
  {
    screen()->setCursorLeft();
  }
}

void MmiAccelScreenState::up(MmiScreenFsm* fsm)
{
  if (0 != screen())
  {
    screen()->setCursorUp();
  }
}

void MmiAccelScreenState::down(MmiScreenFsm* fsm)
{
  if (0 != screen())
  {
    screen()->setCursorDown();
  }
}

void MmiAccelScreenState::entry(MmiScreenFsm* fsm)
{
  Serial.println(toString());
  updateDisplay();
}

//-----------------------------------------------------------------------------

MmiScreenState* MmiMagnScreenState::s_instance = 0;

MmiScreenState* MmiMagnScreenState::Instance()
{
  if (0 == s_instance)
  {
    s_instance = new MmiMagnScreenState();
  }
  return s_instance;
}

const char* MmiMagnScreenState::toString()
{
  return "MagnScreenState";
}

void MmiMagnScreenState::select(MmiScreenFsm* fsm)
{
  if ((0 != screen()) && (0 != fsm))
  {
      fsm->changeState(MmiAngleScreenState::Instance());
  }
}

void MmiMagnScreenState::left(MmiScreenFsm* fsm)
{
  if (0 != screen())
  {
    screen()->setCursorLeft();
  }
}

void MmiMagnScreenState::up(MmiScreenFsm* fsm)
{
  if (0 != screen())
  {
    screen()->setCursorUp();
  }
}

void MmiMagnScreenState::down(MmiScreenFsm* fsm)
{
  if (0 != screen())
  {
    screen()->setCursorDown();
  }
}

void MmiMagnScreenState::entry(MmiScreenFsm* fsm)
{
  Serial.println(toString());
  updateDisplay();
}

