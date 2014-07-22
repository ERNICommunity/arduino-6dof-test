/*
 * AMmiAdapter.cpp
 *
 *  Created on: 22.07.2014
 *      Author: niklausd
 */

#include "FreeSixIMU.h"
#include "AMmiAdapter.h"

AMmiAdapter::AMmiAdapter(FreeSixIMU* freeSixIMU)
: m_freeSixIMU(freeSixIMU)
{ }

AMmiAdapter::~AMmiAdapter()
{ }

float AMmiAdapter::getYawAngle()
{
  float angles[3] = { 0.0, 0.0, 0.0 };
  if (0 != m_freeSixIMU)
  {
    m_freeSixIMU->getAngles(angles);
  }
  return (angles[0]);
}

void AMmiAdapter::resetYaw()
{
  if (0 != m_freeSixIMU)
  {
    m_freeSixIMU->init();
  }
}
