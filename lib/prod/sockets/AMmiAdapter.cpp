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
{
  m_angles[0] = 0.0;
  m_angles[1] = 0.0;
  m_angles[2] = 0.0;
  m_accel[0] = 0.0;
  m_accel[1] = 0.0;
  m_accel[2] = 0.0;
  m_magn[0] = 0.0;
  m_magn[1] = 0.0;
  m_magn[2] = 0.0;
}

AMmiAdapter::~AMmiAdapter()
{ }

void AMmiAdapter::sampleAngles()
{
  if (0 != m_freeSixIMU)
  {
    m_freeSixIMU->getAngles(m_angles);
  }
}

float AMmiAdapter::getPitchAngle()
{
  return (m_angles[2]);
}

float AMmiAdapter::getRollAngle()
{
  return (m_angles[1]);
}

float AMmiAdapter::getYawAngle()
{
  return (m_angles[0]);
}

void AMmiAdapter::sampleAccel()
{
  if (0 != m_freeSixIMU)
  {
    m_freeSixIMU->getAccelXYZ(m_accel);
  }
}

float AMmiAdapter::getXAccel()
{
  return (m_accel[0]);
}

float AMmiAdapter::getYAccel()
{
  return (m_accel[1]);
}

float AMmiAdapter::getZAccel()
{
  return (m_accel[2]);
}

void AMmiAdapter::sampleMagn()
{
  if (0 != m_freeSixIMU)
  {
    m_freeSixIMU->getMagnXYZ(m_magn);
  }
}

float AMmiAdapter::getXMagn()
{
  return (m_magn[0]);
}

float AMmiAdapter::getYMagn()
{
  return (m_magn[1]);
}

float AMmiAdapter::getZMagn()
{
  return (m_magn[2]);
}

void AMmiAdapter::resetAngles()
{
  if (0 != m_freeSixIMU)
  {
    m_freeSixIMU->init();
  }
}
