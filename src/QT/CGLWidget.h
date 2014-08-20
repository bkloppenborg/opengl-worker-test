/*
 * CGLWidget.h
 *
 *  Created on: Aug 20, 2014
 *      Author: bkloppenborg
 */

#ifndef CGLWIDGET_H_
#define CGLWIDGET_H_

#include <QGLWidget>
#include <QGLFramebufferObject>

class CGLWidget : public QGLWidget{
    Q_OBJECT

protected:
    float color;
    QGLFramebufferObject * mFBO_render;


public:
	CGLWidget ( QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0 );
	virtual ~CGLWidget();

protected:
	void paintGL();
	void resizeGL();
	void initializeGL();
};

#endif /* CGLWIDGET_H_ */
