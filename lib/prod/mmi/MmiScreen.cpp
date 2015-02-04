/*
 * MmiScreen.cpp
 *
 *  Created on: 29.01.2015
 *      Author: scan
 */

#include <Arduino.h>

#include <MmiScreen.h>
#include <Mmi.h>
#include <LcdKeypad.h>

MmiScreen::MmiScreen(Mmi* mmi)
: m_mmi(mmi)
{ }

MmiScreen::~MmiScreen()
{ }

//-----------------------------------------------------------------------------

MmiAngleScreen::MmiAngleScreen(Mmi* mmi)
: MmiScreen(mmi)
{ }

MmiAngleScreen::~MmiAngleScreen()
{ }

void MmiAngleScreen::setCursorUp()
{
  if (0 != mmi() && (0 != mmi()->lcdKeypad()))
  {
    mmi()->lcdKeypad()->setBackLightOn(true);
  }
}

void MmiAngleScreen::setCursorDown()
{
  if (0 != mmi() && (0 != mmi()->lcdKeypad()))
  {
    mmi()->lcdKeypad()->setBackLightOn(false);
  }
}

void MmiAngleScreen::updateDisplay()
{
  if ((0 != mmi()) && (0 != mmi()->lcdKeypad()) && (0 != mmi()->adapter()))
  {
    mmi()->adapter()->sampleAngles();

    //-------------------------------------------
    // LCD Display Line 1
    //-------------------------------------------
    mmi()->lcdKeypad()->setCursor(0, 0);

    mmi()->lcdKeypad()->print("Y:");
    mmi()->lcdKeypad()->print(mmi()->adapter()->getYawAngle(), 1);
    mmi()->lcdKeypad()->print("\337"); // print the degree character °
    mmi()->lcdKeypad()->print("                ");

    //-------------------------------------------
    // LCD Display Line 2
    //-------------------------------------------
    mmi()->lcdKeypad()->setCursor(0, 1);

    mmi()->lcdKeypad()->print("P:");
    mmi()->lcdKeypad()->print(mmi()->adapter()->getPitchAngle(), 0);
    mmi()->lcdKeypad()->print("\337"); // print the degree character °
    mmi()->lcdKeypad()->print(" - R:");
    mmi()->lcdKeypad()->print(mmi()->adapter()->getRollAngle(), 0);
    mmi()->lcdKeypad()->print("\337"); // print the degree character °
    mmi()->lcdKeypad()->print("           ");
  }
}

//-----------------------------------------------------------------------------

MmiAccelScreen::MmiAccelScreen(Mmi* mmi)
: MmiScreen(mmi)
{ }

MmiAccelScreen::~MmiAccelScreen()
{ }

void MmiAccelScreen::setCursorUp()
{
  if (0 != mmi())
  {
    mmi()->lcdKeypad()->setBackLightOn(true);
  }
}

void MmiAccelScreen::setCursorDown()
{
  if (0 != mmi())
  {
    mmi()->lcdKeypad()->setBackLightOn(false);
  }
}

void MmiAccelScreen::updateDisplay()
{
  if ((0 != mmi()) && (0 != mmi()->lcdKeypad()) && (0 != mmi()->adapter()))
  {
    mmi()->adapter()->sampleAccel();

    //-------------------------------------------
    // LCD Display Line 1
    //-------------------------------------------
    mmi()->lcdKeypad()->setCursor(0, 0);

    mmi()->lcdKeypad()->print("X:");
    mmi()->lcdKeypad()->print(mmi()->adapter()->getXAccel(), 1);
    mmi()->lcdKeypad()->print("g"); // print g Unit
    mmi()->lcdKeypad()->print("                ");

    //-------------------------------------------
    // LCD Display Line 2
    //-------------------------------------------
    mmi()->lcdKeypad()->setCursor(0, 1);

    mmi()->lcdKeypad()->print("Y:");
    mmi()->lcdKeypad()->print(mmi()->adapter()->getYAccel(), 1);
    mmi()->lcdKeypad()->print("g"); // print g Unit
    mmi()->lcdKeypad()->print(" Z:");
    mmi()->lcdKeypad()->print(mmi()->adapter()->getZAccel(), 1);
    mmi()->lcdKeypad()->print("g"); // print g Unit
    mmi()->lcdKeypad()->print("           ");
  }
}

//-----------------------------------------------------------------------------

MmiMagnScreen::MmiMagnScreen(Mmi* mmi)
: MmiScreen(mmi)
{ }

MmiMagnScreen::~MmiMagnScreen()
{ }

void MmiMagnScreen::setCursorUp()
{
  if (0 != mmi())
  {
    mmi()->lcdKeypad()->setBackLightOn(true);
  }
}

void MmiMagnScreen::setCursorDown()
{
  if (0 != mmi())
  {
    mmi()->lcdKeypad()->setBackLightOn(false);
  }
}

void MmiMagnScreen::updateDisplay()
{
  if ((0 != mmi()) && (0 != mmi()->lcdKeypad()) && (0 != mmi()->adapter()))
  {
    mmi()->adapter()->sampleMagn();

    //-------------------------------------------
    // LCD Display Line 1
    //-------------------------------------------
    mmi()->lcdKeypad()->setCursor(0, 0);

    mmi()->lcdKeypad()->print("X:");
    mmi()->lcdKeypad()->print(mmi()->adapter()->getXMagn(), 0);
    //mmi()->lcdKeypad()->print("g"); // print g Unit
    mmi()->lcdKeypad()->print("                ");

    //-------------------------------------------
    // LCD Display Line 2
    //-------------------------------------------
    mmi()->lcdKeypad()->setCursor(0, 1);

    mmi()->lcdKeypad()->print("Y:");
    mmi()->lcdKeypad()->print(mmi()->adapter()->getYMagn(), 0);
    //mmi()->lcdKeypad()->print("g"); // print g Unit
    mmi()->lcdKeypad()->print(" Z:");
    mmi()->lcdKeypad()->print(mmi()->adapter()->getZMagn(), 0);
    //mmi()->lcdKeypad()->print("g"); // print g Unit
    mmi()->lcdKeypad()->print("           ");
  }
}
