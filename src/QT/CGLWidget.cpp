/*
 * CGLWidget.cpp
 *
 *  Created on: Aug 20, 2014
 *      Author: bkloppenborg
 */

#include "CGLWidget.h"

CGLWidget::CGLWidget ( QWidget * parent, const QGLWidget * shareWidget, Qt::WindowFlags f)
	: QGLWidget(parent, shareWidget, f)
{
	mGLThread = new CGLThread(this);
}

CGLWidget::~CGLWidget()
{
	if(mGLThread)
	{
		mGLThread->stop();
		delete mGLThread;
	}
}


void CGLWidget::paintGL()
{
	if(!mGLThread->running())
	{
		setAutoBufferSwap(false);
	    this->doneCurrent();
		mGLThread->start();
	}
}

// The widget has fixed size. Prohibit resizing.
void CGLWidget::resizeGL()
{

}


void CGLWidget::initializeGL()
{
	// Almost all OpenGL initalization is done in the rendering thread.
	setFixedSize(this->size());
}

