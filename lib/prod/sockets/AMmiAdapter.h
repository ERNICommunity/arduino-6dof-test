/*
 * AMmiAdapter.h
 *
 *  Created on: 22.07.2014
 *      Author: niklausd
 */

#ifndef AMMIADAPTER_H_
#define AMMIADAPTER_H_

#include "Mmi.h"

class FreeSixIMU;

class AMmiAdapter: public MmiAdapter
{
public:
  AMmiAdapter(FreeSixIMU* freeSixIMU);
  virtual ~AMmiAdapter();

  float getYawAngle();
  void resetYaw();


private:
  FreeSixIMU* m_freeSixIMU;

private: // forbidden default functions
  AMmiAdapter& operator = (const AMmiAdapter& src);  // assignment operator
  AMmiAdapter(const AMmiAdapter& src);               // copy constructor
};

#endif /* AMMIADAPTER_H_ */
