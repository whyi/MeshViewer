#ifndef CVEC_H
#define CVEC_H

#include <cmath>
#include <iostream>
#include <Windows.h>
#include <gl/GL.h>
namespace MeshViewer
{
  const double TOLERANCE(0.00000001f);
}

// Simple minded 3D point/vector class.
class CVec
{
  typedef double value_type;
  value_type arr[3];

public:
  // castring operator to cope with OpenGL APIs
  operator const GLdouble*(void) const;

  CVec(const value_type xx = 0.0, const value_type yy = 0.0, const value_type zz = 0.0);
  CVec(const CVec& rhs);
  CVec& operator=(const CVec &rhs);

  void normalize(void);

  // Get/Set member functions
  const value_type x(void) const;
  const value_type y(void) const;
  const value_type z(void) const;
  void setX(const value_type val);
  void setY(const value_type val);
  void setZ(const value_type val);
  void set(const value_type xx, const value_type yy, const value_type zz);

  // Basic Operators
  CVec& operator+=(const CVec& rhs);
  const CVec operator+(const CVec& rhs) const;
  CVec& operator-=(const CVec& rhs);
  const CVec operator-(const CVec& rhs) const;
  CVec& operator*=(const double s);
  const CVec operator*(const double s) const;

  // cross product
  static const CVec cross(const CVec &A, const CVec &B)
  {
    return CVec( A.y()*B.z()-A.z()*B.y(),
                 A.z()*B.x()-A.x()*B.z(),
                 A.x()*B.y()-A.y()*B.x());
  }

  // dot product
  static const double dot(const CVec& U, const CVec& V)
  {
    return (U.x()*V.x()) + (U.y()*V.y()) + (U.z()*V.z());
  }

  // mixed product. Essentially this is the volume of a hex composed of three basis vectors
  static double mixed(const CVec &U, const CVec &V, const CVec &W)
  {
    return CVec::dot(CVec::cross(U,V),W);
  }

  // compute volume of a tetrahedron constructed by EABC
  static double tetVolume(const CVec &E, const CVec &A, const CVec &B, const CVec &C)
  {
    const CVec EA=A-E;
    const CVec EB=B-E;
    const CVec EC=C-E;
    const double v = mixed(EA,EB,EC);
    if( abs(v) < MeshViewer::TOLERANCE )
      return 0;

    return v/6;
  }

  // intersection test
  static bool rayHitTri(const CVec &E, const CVec &M, const CVec &A, const CVec &B, const CVec &C)
  {
    const bool s = (tetVolume(E,A,B,C)>0);
    const bool sA = (tetVolume(E,M,B,C)>0);
    const bool sB = (tetVolume(E,A,M,C)>0);
    const bool sC = (tetVolume(E,A,B,M)>0);

    return( (s==sA) && (s==sB) && (s==sC) );
  }
};

#endif // CVEC_H
