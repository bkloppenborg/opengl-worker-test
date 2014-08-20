/*
 * CGLThread.h
 *
 *  Created on: Aug 20, 2014
 *      Author: bkloppenborg
 */

#ifndef CGLTHREAD_H_
#define CGLTHREAD_H_

#include <QThread>
#include <QGLFramebufferObject>

class CGLWidget;

class CGLThread : public QThread{
private:
    CGLWidget * glw;

    QGLFramebufferObject * mFBO_render;

	bool doRendering;

public:
	CGLThread(CGLWidget * glWidget);
	~CGLThread();

public:
    void resizeViewport(const QSize &size);
    void run();
    void stop();

    bool running() { return doRendering; }

protected:
    void initializeGL();
};

#endif /* CGLTHREAD_H_ */
