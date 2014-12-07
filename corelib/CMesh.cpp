#include <sstream>
#include <fstream>
#include <iostream>
#include <climits>
#include "CMesh.h"
#include "Log.h"

CMesh::CMesh(void)
  : vertices(), triangles(),
    xmin(LONG_MAX), ymin(LONG_MAX), zmin(LONG_MAX),
    xmax(-LONG_MAX), ymax(-LONG_MAX), zmax(-LONG_MAX),
    geoCenter()
{
}

void CMesh::computeBoundingBox(void)
{
  geoCenter.set(0,0,0);

  for( size_t i = 0; i < vertices.size(); ++i )
  {
    if( vertices[i].x() > xmax ) xmax = vertices[i].x();
    if( vertices[i].y() > ymax ) ymax = vertices[i].y();
    if( vertices[i].z() > zmax ) zmax = vertices[i].z();
    if( vertices[i].x() < xmin ) xmin = vertices[i].x();
    if( vertices[i].y() < ymin ) ymin = vertices[i].y();
    if( vertices[i].z() < zmin ) zmin = vertices[i].z();
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

  for( size_t i = 0; i < triangles.size()/3; ++i )
  {
    glBegin( GL_TRIANGLES );
    glVertex3dv( vertices[triangles[3*i]] );
    glVertex3dv( vertices[triangles[3*i+1]] );
    glVertex3dv( vertices[triangles[3*i+2]] );
    glEnd();
  }

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  glPopMatrix();
}

void CMesh::readOFF(const std::string &filename)
{
  std::ifstream in(filename.c_str(), std::ios::in );
  std::string buffer;
  // read off "OFF" and header, the first 2 lines
  getline(in, buffer);
  getline(in, buffer);

  std::istringstream line(buffer);
  size_t counter(0);

  size_t number_of_vertices, number_of_triangles;
  line >> number_of_vertices >> number_of_triangles;

  vertices.reserve(number_of_vertices);
  while(counter < number_of_vertices)
  {
    getline(in, buffer);
    std::istringstream point(buffer);
    double x, y, z;
    point >> x >> y >> z;
    vertices.push_back(CVec(x,y,z));
    ++counter;
  }
  counter = 0;

  triangles.reserve(number_of_triangles);
  while(counter < number_of_triangles)
  {
    getline(in, buffer);
    std::istringstream face(buffer);
    size_t tmp, point_a, point_b, point_c;
    face >> tmp >> point_a >> point_b >> point_c;
    triangles.push_back(point_a);
    triangles.push_back(point_b);
    triangles.push_back(point_c);
    ++counter;
  }
  in.close();
}


const bool CMesh::containsPoint( const CVec &p ) const
{
  size_t nHit(0);

  for(size_t i = 0; i < triangles.size()/3; ++i)
  {
    if( CVec::rayHitTri(p, geoCenter,
                  vertices[triangles[3*i]],
                  vertices[triangles[3*i+2]],
                  vertices[triangles[3*i+1]]) )
      ++nHit;
  }

  if( nHit == 0 ) return false;

  if( nHit > 0 && nHit % 2 != 0 )
    return true;

  return false;
}
