/* dtkComposerEvaluator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Oct 24 12:51:53 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Oct 27 14:15:23 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSEREVALUATOR_H
#define DTKCOMPOSEREVALUATOR_H

#include "dtkComposerExport.h"

#include <QtCore/QObject>

class dtkComposerEvaluatorPrivate;
class dtkComposerScene;

class DTKCOMPOSER_EXPORT dtkComposerEvaluator : public QObject
{
    Q_OBJECT

public:
     dtkComposerEvaluator(QObject *parent = 0);
     dtkComposerEvaluator(dtkComposerScene *scene, QObject *parent = 0);
    ~dtkComposerEvaluator(void);

    void setScene(dtkComposerScene *scene);

signals:
    void evaluationStarted(void);
    void evaluationStopped(void);

public slots:
    void start(void);
    void stop(void);

private:
    dtkComposerEvaluatorPrivate *d;
};

#endif
