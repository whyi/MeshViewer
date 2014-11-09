/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include <QtOpenGL>
#include <cmath>
#include "gl/GLU.h"
#include "glwidget.h"
#include "Log.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif
#define ROTATION_STEP 0.5f
using namespace std;

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
      mesh()
{
    if (mesh.readOFF("fandisk.off")) {
        mesh.computeBoundingBox();
    }
}

GLWidget::~GLWidget()
{
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(800, 800);
}


void GLWidget::initializeCamera(void)
{
  cout << "InitCamera(void) : initializing camera....";
  rot[0] = rot[1] = 180;

  glFrontFace( GL_CCW );
  camera.move( CVec(0.0,0.0,mesh.diag()) );
  camera.rotateAroundOrigin( rot[0], rot[1] );
  cout << "done!" << endl;
}


void GLWidget::initializeGL()
{
  initializeCamera();
}


void GLWidget::setViewport(void) const
{
  glViewport(0, 0, dim[0], dim[1]);
  const GLfloat fAspect = dim[0]/dim[1];
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0f, fAspect, 1.0f, 10000.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void GLWidget::GLRenderScene(void) const
{
  setViewport();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glDisable( GL_CULL_FACE );
  camera.render(); // Viewing Transform

  glPushMatrix();
    mesh.render();
  glPopMatrix();

}

void GLWidget::paintGL()
{
  GLRenderScene();
}

void GLWidget::resizeGL(int width, int height)
{
    dim[0] = width;
    dim[1] = height;
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#else
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
  lastPos = event->pos();
}


void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
  if(event->buttons() & Qt::LeftButton)
  {
    const double dx = event->x() - lastPos.x();
    const double dy = event->y() - lastPos.y();
    rot[0] = dy*ROTATION_STEP;
    rot[1] = dx*ROTATION_STEP;
    camera.rotateAroundOrigin(-rot[0], -rot[1] );
    lastPos = event->pos();
  }

  updateGL();
  event->accept();
  GLRenderScene();
}

void GLWidget::wheelEvent( QWheelEvent *event )
{
  const int d = event->delta();

  bool forward(true);
  if( d < 0 ) forward = false;

  float abd = abs(d);
  abd = abd*(0.1f);
  if( mesh.diag() < 120 ) { abd = 2.0f; };

  if( forward )  camera.moveForward( abd );
  if( !forward ) camera.moveBackward( abd );

  event->accept();
  updateGL();
}

void GLWidget::keyboardHandler( QKeyEvent *e )
{
  switch(e->key())
  {
    case Qt::Key_Escape : LogMsg( LOG_ERROR, "Got broken, exiting..."); exit(0);
    case Qt::Key_T	   	: break;
    default:
      break;
  }
  e->accept();
  updateGL();
}
