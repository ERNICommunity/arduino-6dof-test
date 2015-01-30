/*
 * MmiScreenFsm.h
 *
 *  Created on: 30.01.2015
 *      Author: scan
 */

#ifndef MMI_MMISCREENFSM_H_
#define MMI_MMISCREENFSM_H_

class Mmi;
class MmiScreenState;

class MmiScreenFsm
{
public:
  MmiScreenFsm(Mmi* mmi);
  virtual ~MmiScreenFsm();

  void select();
  void left();
  void right();
  void up();
  void down();

  void changeState(MmiScreenState* state);

  void updateDisplay();

private:
  MmiScreenState* m_state;

private: // forbidden default functions
  MmiScreenFsm& operator = (const MmiScreenFsm& src);  // assignment operator
  MmiScreenFsm(const MmiScreenFsm& src);               // copy constructor
};

#endif /* MMI_MMISCREENFSM_H_ */
