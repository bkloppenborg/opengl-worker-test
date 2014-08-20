/*
 * main.cpp
 *
 *  Created on: Aug 20, 2014
 *      Author: bkloppenborg
 */

/*
 * Copyright (c) 2014 Brian Kloppenborg
 *
 * If you use this software as part of a scientific publication, please cite as:
 *
 * Kloppenborg, B.; Baron, F. (2012), "SIMTOI: The SImulation and Modeling
 * Tool for Optical Interferometry" (Version X).
 * Available from  <https://github.com/bkloppenborg/simtoi>.
 *
 * This file is part of the SImulation and Modeling Tool for Optical
 * Interferometry (SIMTOI).
 *
 * SIMTOI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation version 3.
 *
 * SIMTOI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SIMTOI.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtGui>
#include <QApplication>
#include <QGLFormat>

// Include to enable threads on X11
#ifdef Q_WS_X11
#include <X11/Xlib.h>
#endif // Q_WS_X11

#include "main.h"
#include "gui_main.h"

int main(int argc, char* argv[])
{
	// X11 requires some special initialzation for threaded OpenGL rendering.
#if QT_VERSION_MAJOR >= 4 && QT_VERSION_MINOR >= 8
	// For QT >= 4.8, we have to set a global QT attribute
    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);
#elif defined Q_WS_X11
    // For all other versions of QT running on X11, the following (should) be sufficient.
    XInitThreads();
#endif

	// Pass off to the GUI:
    QApplication app(argc, argv);

	// Set the default OpenGL format
	QGLFormat fmt;
	fmt.setVersion(3, 2);
	fmt.setProfile(QGLFormat::CoreProfile);
	fmt.setDoubleBuffer(true);
	fmt.setSampleBuffers(true);
	fmt.setSamples(4);
	QGLFormat::setDefaultFormat(fmt);

    // Startup the GUI:
	gui_main main_window;
    main_window.show();

    return app.exec();
}
