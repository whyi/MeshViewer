#include <sstream>
#include <fstream>
#include <iostream>
#include <climits>
#include "CMesh.h"
#include "Log.h"

CMesh::CMesh(void)
  : m_pts(), m_tris(),
    xmin(LONG_MAX), ymin(LONG_MAX), zmin(LONG_MAX),
    xmax(-LONG_MAX), ymax(-LONG_MAX), zmax(-LONG_MAX),
    geoCenter()
{
}

void CMesh::computeBoundingBox(void)
{
  geoCenter.set(0,0,0);

  for( size_t i = 0; i < m_pts.size(); ++i )
  {
    if( m_pts[i].x() > xmax ) xmax = m_pts[i].x();
    if( m_pts[i].y() > ymax ) ymax = m_pts[i].y();
    if( m_pts[i].z() > zmax ) zmax = m_pts[i].z();
    if( m_pts[i].x() < xmin ) xmin = m_pts[i].x();
    if( m_pts[i].y() < ymin ) ymin = m_pts[i].y();
    if( m_pts[i].z() < zmin ) zmin = m_pts[i].z();
  }
  geoCenter.set((xmin+xmax)/2,
                (ymin+ymax)/2,
                (zmin+zmax)/2);
}

void CMesh::render(void) const
{
  glPushMatrix();

  glLineWidth( 0.5f );
  glColor3f( 1, 0, 0 );
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

  for( size_t i = 0; i < m_tris.size()/3; ++i )
  {
    glBegin( GL_TRIANGLES );
    glVertex3dv( m_pts[m_tris[3*i]] );
    glVertex3dv( m_pts[m_tris[3*i+1]] );
    glVertex3dv( m_pts[m_tris[3*i+2]] );
    glEnd();
  }

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  glPopMatrix();
}

bool CMesh::readOFF(const std::string &filename)
{
  std::ifstream in(filename.c_str(), std::ios::in );
  std::string buffer;
  // read off "OFF" and header, the first 2 lines
  getline(in, buffer);
  getline(in, buffer);

  std::istringstream line(buffer);
  size_t nVertices, nTris;
  line >> nVertices >> nTris;

  m_pts.reserve(nVertices);
  size_t cnt(0);
  while(cnt < nVertices)
  {
    getline(in, buffer);
    std::istringstream pointsLine(buffer);
    double x, y, z;
    pointsLine >> x >> y >> z;
    m_pts.push_back(CVec(x,y,z));
    ++cnt;
  }
  cnt = 0;
  m_tris.reserve(nTris);
  while(cnt < nTris)
  {
    getline(in, buffer);
    std::istringstream pointsLine(buffer);
    size_t tmp, i1, i2, i3;
    pointsLine >> tmp >> i1 >> i2 >> i3;
    m_tris.push_back(i1);
    m_tris.push_back(i2);
    m_tris.push_back(i3);
    ++cnt;
  }
  in.close();
  return true;
}


const bool CMesh::containsPoint( const CVec &p ) const
{
  size_t nHit(0);

  for(size_t i = 0; i < m_tris.size()/3; ++i)
  {
    if( CVec::rayHitTri(p, geoCenter,
                  m_pts[m_tris[3*i]],
                  m_pts[m_tris[3*i+2]],
                  m_pts[m_tris[3*i+1]]) )
      ++nHit;
  }

  if( nHit == 0 ) return false;

  if( nHit > 0 && nHit % 2 != 0 )
    return true;

  return false;
}
