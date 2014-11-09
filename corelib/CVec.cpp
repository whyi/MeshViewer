#include "CVec.h"

CVec::operator const GLdouble*(void) const { return &arr[0]; }
CVec::CVec(const value_type xx, const value_type yy, const value_type zz)
{
  arr[0] = xx;
  arr[1] = yy;
  arr[2] = zz;
}

CVec::CVec(const CVec& rhs)
{
  arr[0] = rhs.arr[0];
  arr[1] = rhs.arr[1];
  arr[2] = rhs.arr[2];
}

CVec& CVec::operator=(const CVec &rhs)
{
  if( this != &rhs )
  {
    arr[0] = rhs.arr[0];
    arr[1] = rhs.arr[1];
    arr[2] = rhs.arr[2];
  }
  return *this;
}

void CVec::normalize(void)
{
  const value_type n = sqrt(arr[0]*arr[0]+arr[1]*arr[1]+arr[2]*arr[2]);
  if( n > MeshViewer::TOLERANCE )
  {
    if(arr[0] != 0 && n != 0) arr[0] /= n;
    if(arr[1] != 0 && n != 0) arr[1] /= n;
    if(arr[2] != 0 && n != 0) arr[2] /= n;
  }
}

const CVec::value_type CVec::x(void) const { return arr[0]; }
const CVec::value_type CVec::y(void) const { return arr[1]; }
const CVec::value_type CVec::z(void) const { return arr[2]; }
void CVec::setX(const value_type val) { arr[0] = val; }
void CVec::setY(const value_type val) { arr[1] = val; }
void CVec::setZ(const value_type val) { arr[2] = val; }
void CVec::set(const value_type xx, const value_type yy, const value_type zz)
{
  arr[0] = xx;
  arr[1] = yy;
  arr[2] = zz;
}

CVec& CVec::operator+=(const CVec& rhs)
{
  arr[0] += rhs.arr[0];
  arr[1] += rhs.arr[1];
  arr[2] += rhs.arr[2];
  return *this;
}

const CVec CVec::operator+(const CVec& rhs) const
{
  return CVec(arr[0] + rhs.arr[0],
              arr[1] + rhs.arr[1],
              arr[2] + rhs.arr[2]);
}

CVec& CVec::operator-=(const CVec& rhs)
{
  arr[0] -= rhs.arr[0];
  arr[1] -= rhs.arr[1];
  arr[2] -= rhs.arr[2];
  return *this;
}

const CVec CVec::operator-(const CVec& rhs) const
{
  return CVec(arr[0]-rhs.arr[0],
              arr[1]-rhs.arr[1],
              arr[2]-rhs.arr[2]);
}

CVec& CVec::operator*=(const double s)
{
  arr[0]*=s;
  arr[1]*=s;
  arr[2]*=s;
  return *this;
}

const CVec CVec::operator*(const double s) const
{
  return CVec(arr[0]*s, arr[1]*s, arr[2]*s);
}

