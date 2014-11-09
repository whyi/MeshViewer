#include <iostream>
#include <Windows.h>
#include <gl/glu.h>
#include "Camera.h"

CCamera::CCamera(void)
:rotatedX(0.0),rotatedY(0.0),rotatedZ(0.0),
 viewDir(0.0,0.0,-1.0),
 rightVector(1.0,0.0,0.0),
 upVector(0.0,1.0,0.0){}

void CCamera::move(const CVec& direction)
{
  position += direction;
}

void CCamera::rotateX(const double angle)
{
  rotatedX += angle;

  //rotate viewDir around the right vector:
  CVec tmpV = viewDir*cos(angle*PI_DIV_BY_180) + upVector*sin(angle*PI_DIV_BY_180);
  tmpV.normalize();
  viewDir = tmpV;

  //now compute the new upVector (by CVec::cross product)
  upVector = CVec::cross(viewDir, rightVector);
  upVector *= -1;
}

void CCamera::rotateY(const double angle)
{
  rotatedY += angle;
  //rotate viewDir around the up vector:
  CVec tmpV = viewDir*cos(angle*PI_DIV_BY_180) - rightVector*sin(angle*PI_DIV_BY_180);
  tmpV.normalize();
  viewDir = tmpV;

  //now compute the new rightVector (by CVec::cross product)
  rightVector = CVec::cross(viewDir, upVector);
}

void CCamera::render( void ) const
{
  //The point at which the camera looks:
  const CVec viewPoint = position+viewDir;

  //as we know the up vector, we can easily use gluLookAt:
  if( upVector.y() == MeshViewer::TOLERANCE || upVector.y() == -MeshViewer::TOLERANCE )
    upVector.setY(-1.0);

  gluLookAt( position.x(),position.y(),position.z(),
             viewPoint.x(),viewPoint.y(),viewPoint.z(),
             upVector.x(),upVector.y(),upVector.z());

}

void CCamera::moveForward(const double distance)
{
  position += viewDir*(-distance);
}

void CCamera::moveBackward(const double distance)
{
  position += viewDir*distance;
}

void CCamera::rotateAroundOrigin( const double angX, const double angY )
{
  const CVec tmp(CVec::dot( position, rightVector ),
                 CVec::dot( position, upVector ),
                 CVec::dot( position, viewDir ));

  position.set(0,0,0); // go to the origin

  rotateX(angX); // rotateX
  rotateY(angY);

  // go back by the recorded vector
  position = rightVector*tmp.x() + upVector*tmp.y() + viewDir*tmp.z();

}
