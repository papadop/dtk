/* dtkComposerNodeFactory.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb  7 22:37:03 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Nov 26 09:37:08 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 132
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewFactory.h>

#include "dtkComposerNode.h"
#include "dtkComposerNodeCondition.h"
#include "dtkComposerNodeData.h"
#include "dtkComposerNodeFactory.h"
#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeInteger.h"
#include "dtkComposerNodeProcess.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerNodeView.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFactoryPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeFactoryPrivate
{
public:
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFactory
// /////////////////////////////////////////////////////////////////

dtkComposerNodeFactory::dtkComposerNodeFactory(void) : QObject(), d(new dtkComposerNodeFactoryPrivate)
{

}

dtkComposerNodeFactory::~dtkComposerNodeFactory(void)
{
    delete d;

    d = NULL;
}

dtkComposerNode *dtkComposerNodeFactory::create(QString type)
{
    if (type == "dtkComposerInteger")
        return new dtkComposerNodeInteger;

    if (type == "dtkComposerString")
        return new dtkComposerNodeString;

    if (type == "dtkComposerFile")
        return new dtkComposerNodeFile;

    if (type == "dtkComposerCondition")
        return new dtkComposerNodeCondition;

    if (dtkAbstractData *data = dtkAbstractDataFactory::instance()->create(type)) {
        
        dtkComposerNodeData *node = new dtkComposerNodeData;
        node->setObject(data);
        node->setType(type);
        return node;
    }

    if (dtkAbstractProcess *process = dtkAbstractProcessFactory::instance()->create(type)) {
        
        dtkComposerNodeProcess *node = new dtkComposerNodeProcess;
        node->setObject(process);
        node->setType(type);
        return node;
    }

    if (dtkAbstractView *view = dtkAbstractViewFactory::instance()->create(type)) {
        
        dtkComposerNodeView *node = new dtkComposerNodeView;
        node->setObject(view);
        node->setType(type);
        node->addAction("Show view", view, SLOT(show()));

        return node;
    }

    return NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFactory documentation
// /////////////////////////////////////////////////////////////////

/*! \class dtkComposerNodeFactory
 *
 *  \brief The dtkComposerNodeFactory class defines a factory for
 *  creating composition nodes based on the type of the object that is
 *  attached to it.
 *
 */
