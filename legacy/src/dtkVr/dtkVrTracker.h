/* dtkVrTracker.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 20:30:26 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 26 17:49:20 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRTRACKER_H
#define DTKVRTRACKER_H

#include "dtkVrExport.h"

#include <dtkMath/dtkQuaternion.h>
#include <dtkMath/dtkVector3D.h>

#include <QtCore>
#include <QtNetwork>

class dtkVrTrackerPrivate;

class DTKVR_EXPORT dtkVrTracker : public QObject
{
    Q_OBJECT

public:
     dtkVrTracker(void);
    ~dtkVrTracker(void);

public:
    virtual void   initialize(void);
    virtual void uninitialize(void);

public:
    virtual void setUrl(const QUrl& url);

public:
    virtual dtkVector3D<double> headPosition(void);
    virtual dtkVector3D<double> handPosition(void);

public:
    virtual dtkQuaternion<double> headOrientation(void);

private:
    dtkVrTrackerPrivate *d;
};

#endif
