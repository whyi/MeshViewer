#ifndef CCAMERA_H
#define CCAMERA_H

//***************************************************************************
//
// Advanced CodeColony Camera
// Philipp Crocoll, 2003
//
//***************************************************************************
//***************************************************************************
// Modified for CVec by Jeonggyu Lee, 2009
//***************************************************************************

#include <windows.h>
#include <GL/gl.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "CVec.h"
#define PI_DIV_BY_180 M_PI/180.0

class CCamera
{
  CVec viewDir;
  CVec rightVector;
  mutable CVec upVector; // may be trunkated in render. that's why it's mutable
  CVec position;
  double rotatedX, rotatedY, rotatedZ;
public:
  CCamera(void);    // inits the values (Position: (0|0|0) Target: (0|0|-1) )
  void render(void) const;// executes some glRotates and a glTranslate command
                          // Note: You should call glLoadIdentity before using Render

  void move( const CVec& );
  void rotateX( const double );
  void rotateY( const double );
  void moveForward( const double );
  void moveBackward( const double );
  void rotateAroundOrigin(const double, const double);
};


#endif
