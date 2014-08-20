/*
 * CGLWidget.cpp
 *
 *  Created on: Aug 20, 2014
 *      Author: bkloppenborg
 */

#include "CGLWidget.h"
#include "OpenGL.h"
#include <cmath>

CGLWidget::CGLWidget ( QWidget * parent, const QGLWidget * shareWidget, Qt::WindowFlags f)
	: QGLWidget(parent, shareWidget, f)
{
	mFBO_render = NULL;

}

CGLWidget::~CGLWidget()
{
	if(mFBO_render) delete mFBO_render;
}

/// Rendering function
void CGLWidget::paintGL()
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
    QRect region(0, 0, this->size().width(), this->size().height());
    QGLFramebufferObject::blitFramebuffer (0, region, mFBO_render, region);
	CHECK_OPENGL_STATUS_ERROR(glGetError(), "blitFramebuffer failed");
    swapBuffers();

    // update the color
    color += 0.25;
    color = fmod(color, 1);
}

// The widget has fixed size. Prohibit resizing.
void CGLWidget::resizeGL()
{

}

// Any OpenGL creation routines
void CGLWidget::initializeGL()
{
	if(mFBO_render) delete mFBO_render;

    // Create an RGBA32F MAA buffer
    QGLFramebufferObjectFormat fbo_format = QGLFramebufferObjectFormat();
    fbo_format.setInternalTextureFormat(GL_RGBA32F);
    fbo_format.setTextureTarget(GL_TEXTURE_2D);

    mFBO_render = new QGLFramebufferObject(this->size(), fbo_format);

	CHECK_OPENGL_STATUS_ERROR(glGetError(), "Could not create mFBO_render");
}