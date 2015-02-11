/*
 * MmiScreen.h
 *
 *  Created on: 29.01.2015
 *      Author: scan
 */

#ifndef MMI_MMISCREEN_H_
#define MMI_MMISCREEN_H_

class Mmi;

class MmiScreen
{
protected:
  MmiScreen(Mmi* mmi);
public:
  virtual ~MmiScreen();

  virtual void updateDisplay()  = 0;
  virtual void setCursorUp()    { }
  virtual void setCursorDown()  { }
  virtual void setCursorRight() { }
  virtual void setCursorLeft()  { }

  Mmi* mmi() { return m_mmi; }

private:
  Mmi* m_mmi;

private: // forbidden default functions
  MmiScreen& operator = (const MmiScreen& src);  // assignment operator
  MmiScreen(const MmiScreen& src);               // copy constructor
};

//-----------------------------------------------------------------------------

class MmiAngleScreen : public MmiScreen
{
public:
  MmiAngleScreen(Mmi* mmi);
  virtual ~MmiAngleScreen();
  virtual void updateDisplay();
  virtual void setCursorUp();
  virtual void setCursorDown();
  virtual void setCursorLeft();

private: // forbidden default functions
  MmiAngleScreen& operator = (const MmiAngleScreen& src);  // assignment operator
  MmiAngleScreen(const MmiAngleScreen& src);               // copy constructor
};

//-----------------------------------------------------------------------------

class MmiAccelScreen : public MmiScreen
{
public:
  MmiAccelScreen(Mmi* mmi);
  virtual ~MmiAccelScreen();
  virtual void updateDisplay();
  virtual void setCursorUp();
  virtual void setCursorDown();
  virtual void setCursorLeft();

private: // forbidden default functions
  MmiAccelScreen& operator = (const MmiAccelScreen& src);  // assignment operator
  MmiAccelScreen(const MmiAccelScreen& src);               // copy constructor
};

//-----------------------------------------------------------------------------

class MmiMagnScreen : public MmiScreen
{
public:
  MmiMagnScreen(Mmi* mmi);
  virtual ~MmiMagnScreen();
  virtual void updateDisplay();
  virtual void setCursorUp();
  virtual void setCursorDown();
  virtual void setCursorLeft();

private: // forbidden default functions
  MmiMagnScreen& operator = (const MmiMagnScreen& src);  // assignment operator
  MmiMagnScreen(const MmiMagnScreen& src);               // copy constructor
};

#endif /* MMI_MMISCREEN_H_ */
