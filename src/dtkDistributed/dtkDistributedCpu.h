/* dtkDistributedCpu.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 13:23:49 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 22 09:56:24 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 22
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCPU_H
#define DTKDISTRIBUTEDCPU_H

#include <QObject>

#include "dtkDistributedExport.h"

class dtkDistributedNode;
class dtkDistributedCore;
class dtkDistributedCpuPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedCpu : public QObject
{
    Q_OBJECT

public:
     dtkDistributedCpu(dtkDistributedNode *parent);
    ~dtkDistributedCpu(void);

    enum Architecture {
        x86,
        x86_64,
    };

    Architecture architecture(void);

    void setArchitecture(Architecture arch);

    enum Model {
        Xeon,
        Opteron
    };

    Model model(void);

    void setModel(Model model);

    QList<dtkDistributedCore *> cores(void);

    void operator << (dtkDistributedCore *core);

private:
    dtkDistributedCpuPrivate *d;
};

#endif
