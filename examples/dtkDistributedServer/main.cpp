/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 16:02:43 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 25 16:06:29 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>
#include <QtGui>
#include <QtDebug>

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    qDebug() << "Starting dtk distributed server";

    return application.exec();
}
