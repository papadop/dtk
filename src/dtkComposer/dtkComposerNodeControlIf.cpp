/* dtkComposerNodeControlIf.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sat Feb 25 00:02:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr  4 15:39:53 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 71
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeControlIf.h"

#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeProxy.h"

#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterReceiver.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlIfPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlIfPrivate
{
public:    
    dtkComposerNodeProxy header;
    dtkComposerNodeProxy footer;

    dtkComposerNodeComposite then_block;
    dtkComposerNodeComposite else_block;

public:
    dtkComposerTransmitterReceiver<bool> cond;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlIf implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlIf::dtkComposerNodeControlIf(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlIfPrivate)
{
    d->header.removeEmitter(0);
    d->header.setInputLabelHint("cond", 0); 
    d->header.setAsHeader(true);

    d->cond.appendPrevious(d->header.receivers().first());
    d->header.receivers().first()->appendNext(&(d->cond));

    d->footer.removeReceiver(0);
    d->footer.setOutputLabelHint("cond", 0);
    d->footer.setAsFooter(true);

    d->cond.appendNext(d->footer.emitters().first());
    d->footer.emitters().first()->appendPrevious(&(d->cond));

    d->then_block.setTitleHint("Then");

    d->else_block.setTitleHint("Else");
}

dtkComposerNodeControlIf::~dtkComposerNodeControlIf(void)
{
    delete d;

    d = NULL;
}

int dtkComposerNodeControlIf::blockCount(void)
{
    return 2;
}

dtkComposerNodeLeaf *dtkComposerNodeControlIf::header(void)
{
    return &(d->header);
}

dtkComposerNodeLeaf *dtkComposerNodeControlIf::footer(void)
{
    return &(d->footer);
}

dtkComposerNodeComposite *dtkComposerNodeControlIf::block(int id)
{
    if(id == 0)
        return &(d->then_block);

    if(id == 1)
        return &(d->else_block);

    return NULL;
}

void dtkComposerNodeControlIf::setInputs(void)
{

}

void dtkComposerNodeControlIf::setConditions(void)
{
    
}

void dtkComposerNodeControlIf::setOutputs(void)
{
}

void dtkComposerNodeControlIf::setVariables(void)
{
    
}

int dtkComposerNodeControlIf::selectBranch(void)
{
    if (!d->cond.isEmpty())
	return static_cast<int>(!(d->cond.data()));
        
    return static_cast<int>(false);
}

void dtkComposerNodeControlIf::begin(void)
{
    
}

void dtkComposerNodeControlIf::end(void)
{
    bool value = d->cond.data();
    
    foreach(dtkComposerTransmitter *t, d->then_block.emitters())
        t->setActive(value);

    foreach(dtkComposerTransmitter *t, d->else_block.emitters())
        t->setActive(!value);
}

QString dtkComposerNodeControlIf::type(void)
{
    return "if";
}

QString dtkComposerNodeControlIf::titleHint(void)
{
    return "If";
}
