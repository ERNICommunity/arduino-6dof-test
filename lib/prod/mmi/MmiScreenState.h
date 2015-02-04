/*
 * MmiScreenState.h
 *
 *  Created on: 29.01.2015
 *      Author: scan
 */

#ifndef MMI_MMISCREENSTATE_H_
#define MMI_MMISCREENSTATE_H_

class MmiScreenFsm;
class MmiScreen;

class MmiScreenState
{
protected:
  MmiScreenState();
public:
  virtual ~MmiScreenState();

public:
  virtual void attachScreen(MmiScreen* screen) { m_screen = screen; }

  virtual void select(MmiScreenFsm* fsm) { };
  virtual void left(MmiScreenFsm* fsm)   { };
  virtual void right(MmiScreenFsm* fsm)  { };
  virtual void up(MmiScreenFsm* fsm)     { };
  virtual void down(MmiScreenFsm* fsm)   { };
  virtual void entry(MmiScreenFsm* fsm)  { };

  void updateDisplay();

  virtual const char* toString() = 0;

  MmiScreen* screen() { return m_screen; }

private:
  MmiScreen* m_screen;

private: // forbidden default functions
  MmiScreenState& operator = (const MmiScreenState& src);  // assignment operator
  MmiScreenState(const MmiScreenState& src);               // copy constructor
};

//-----------------------------------------------------------------------------

class MmiAngleScreenState : public MmiScreenState
{
private:
  MmiAngleScreenState() { }

public:
  static MmiScreenState* Instance();

  virtual ~MmiAngleScreenState() { }

  virtual void select(MmiScreenFsm* fsm);
  virtual void up(MmiScreenFsm* fsm)    ;
  virtual void down(MmiScreenFsm* fsm)  ;
  virtual void entry(MmiScreenFsm* fsm) ;

  virtual const char* toString();

private:
  static MmiScreenState* s_instance;

private: // forbidden default functions
  MmiAngleScreenState& operator = (const MmiAngleScreenState& src); // assignment operator
  MmiAngleScreenState(const MmiAngleScreenState& src);              // copy constructor

};

//-----------------------------------------------------------------------------

class MmiAccelScreenState : public MmiScreenState
{
private:
  MmiAccelScreenState() { }

public:
  static MmiScreenState* Instance();

  virtual ~MmiAccelScreenState() { }

  virtual void select(MmiScreenFsm* fsm);
  virtual void up(MmiScreenFsm* fsm)    ;
  virtual void down(MmiScreenFsm* fsm)  ;
  virtual void entry(MmiScreenFsm* fsm) ;

  virtual const char* toString();

private:
  static MmiScreenState* s_instance;

private: // forbidden default functions
  MmiAccelScreenState& operator = (const MmiAccelScreenState& src); // assignment operator
  MmiAccelScreenState(const MmiAccelScreenState& src);              // copy constructor

};

//-----------------------------------------------------------------------------

class MmiMagnScreenState : public MmiScreenState
{
private:
  MmiMagnScreenState() { }

public:
  static MmiScreenState* Instance();

  virtual ~MmiMagnScreenState() { }

  virtual void select(MmiScreenFsm* fsm);
  virtual void up(MmiScreenFsm* fsm)    ;
  virtual void down(MmiScreenFsm* fsm)  ;
  virtual void entry(MmiScreenFsm* fsm) ;

  virtual const char* toString();

private:
  static MmiScreenState* s_instance;

private: // forbidden default functions
  MmiMagnScreenState& operator = (const MmiMagnScreenState& src); // assignment operator
  MmiMagnScreenState(const MmiMagnScreenState& src);              // copy constructor

};

#endif /* MMI_MMISCREENSTATE_H_ */
