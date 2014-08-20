/*
 * CGLThread.cpp
 *
 *  Created on: Aug 20, 2014
 *      Author: bkloppenborg
 */

#include "CGLThread.h"
#include "CGLWidget.h"

#include "OpenGL.h"
#include <cmath>
#include <QGLFramebufferObjectFormat>

CGLThread::CGLThread(CGLWidget * glWidget) {
	glw = glWidget;

	mFBO_render = NULL;
}

CGLThread::~CGLThread() {
	if(mFBO_render) delete mFBO_render;
}


void CGLThread::resizeViewport(const QSize &size)
{
	// resize operation is prohibited
}

void CGLThread::run()
{
	doRendering = true;

	// Take control of the OpenGL context
	glw->makeCurrent();

	// Create buffers
	initializeGL();

	float color = 0;

	while(doRendering)
	{
		// change the background clear color
		mFBO_render->bind();
		CHECK_OPENGL_STATUS_ERROR(glGetError(), "Could not bind to mFBO_render");
		glClearColor(color, 0.0, 0.0, 0.0);
		CHECK_OPENGL_STATUS_ERROR(glGetError(), "glClearColor failed");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		CHECK_OPENGL_STATUS_ERROR(glGetError(), "glClear failed");
		mFBO_render->release();

		// blit the off-screen buffer to the default buffer
		QRect region(0, 0, glw->size().width(), glw->size().height());
		QGLFramebufferObject::blitFramebuffer (0, region, mFBO_render, region);
		CHECK_OPENGL_STATUS_ERROR(glGetError(), "blitFramebuffer failed");
		glw->swapBuffers();

		// update the color
		color += 0.10;
		color = fmod(color, 1);
	}
}

// Any OpenGL creation routines
void CGLThread::initializeGL()
{
	if(mFBO_render) delete mFBO_render;

    // Create an RGBA32F MAA buffer
    QGLFramebufferObjectFormat fbo_format = QGLFramebufferObjectFormat();
    fbo_format.setInternalTextureFormat(GL_RGBA32F);
    fbo_format.setTextureTarget(GL_TEXTURE_2D);

    mFBO_render = new QGLFramebufferObject(glw->size(), fbo_format);

	CHECK_OPENGL_STATUS_ERROR(glGetError(), "Could not create mFBO_render");
}

void CGLThread::stop()
{
	this->doRendering = false;
}
