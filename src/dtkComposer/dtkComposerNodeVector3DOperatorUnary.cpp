/* dtkComposerNodeVector3DOperatorUnary.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Apr 26 15:58:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2013 Tue Jan  8 09:33:41 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 58
 */

/* Commentary: 
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeVector3D.h"
#include "dtkComposerNodeVector3DOperatorUnary.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorUnary 
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVector3DOperatorUnaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVector3DReal*> receiver_vec;

public:
    dtkComposerTransmitterEmitter<dtkVector3DReal*> emitter_vec;
};

dtkComposerNodeVector3DOperatorUnary::dtkComposerNodeVector3DOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVector3DOperatorUnaryPrivate)
{
    this->appendReceiver(&d->receiver_vec);
    this->appendEmitter(&d->emitter_vec);
}

dtkComposerNodeVector3DOperatorUnary::~dtkComposerNodeVector3DOperatorUnary(void)
{
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorUnaryScalar
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVector3DOperatorUnaryScalarPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVector3DReal*> receiver_vec;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_val;
};

dtkComposerNodeVector3DOperatorUnaryScalar::dtkComposerNodeVector3DOperatorUnaryScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVector3DOperatorUnaryScalarPrivate)
{
    this->appendReceiver(&d->receiver_vec);

    this->appendEmitter(&d->emitter_val);
}

dtkComposerNodeVector3DOperatorUnaryScalar::~dtkComposerNodeVector3DOperatorUnaryScalar(void)
{
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorUnary - UNITARY
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorUnaryUnitary::run(void)
{
    if (!d->receiver_vec.isEmpty()) {

        dtkVector3DReal *vector = d->receiver_vec.data();

        if (!vector) {
            dtkError() << "dtkComposerNodeVector3DOperatorUnaryUnitary::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
            d->emitter_vec.clearData();
            return;
        }

        vector->makeUnit();
        d->emitter_vec.setData(vector);

    }  else {        
        dtkWarn() << "dtkComposerNodeVector3DOperatorUnaryUnitary::" << Q_FUNC_INFO << "Input not specified. Nothing is done";
        d->emitter_vec.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorUnaryScalar - NORM
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorUnaryScalarNorm::run(void)
{
    if (!d->receiver_vec.isEmpty()) {

        dtkVector3DReal *vector = d->receiver_vec.constData();

        if (!vector) {
            dtkError() << "dtkComposerNodeVector3DOperatorUnaryScalarNorm::" << Q_FUNC_INFO << "Input vector not set. -1 is returned";
            d->emitter_val.setData(-1);
            return;
        }

        d->emitter_val.setData(vector->norm());

    }  else {
        dtkWarn() << "dtkComposerNodeVector3DOperatorUnaryScalarNorm::" << Q_FUNC_INFO << "Input vector not set. -1 is returned";
        d->emitter_val.setData(-1);
    }
}
