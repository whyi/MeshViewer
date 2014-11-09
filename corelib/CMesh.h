#ifndef CMESH_H
#define CMESH_H

#include <vector>
#include <string>
#include "CVec.h"

class CMesh
{
public:
  std::vector<CVec> m_pts;
  std::vector<size_t> m_tris;
  double xmin, ymin, zmin, xmax, ymax, zmax;
  CVec geoCenter;
  CMesh(void);
  void render(void) const;
  const bool containsPoint( const CVec &p ) const;

  const double width(void) const  { return xmax-xmin; } // width of the bounding box
  const double height(void) const { return ymax-ymin; } // height of the bounding box
  const double diag(void) const   { return sqrt(width()*width()+height()*height());}

  bool readOFF(const std::string &filename);
  void computeBoundingBox(void);
};

#endif // CMESH_H
