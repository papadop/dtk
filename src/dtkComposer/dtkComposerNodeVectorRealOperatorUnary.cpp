/* dtkComposerNodeVectorRealOperatorUnary.cpp ---
 *
 * Author: slekout
 * Copyright (C) 2011 - Babette lekouta, Inria.
 * Created: Thu Apr 26 15:58:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated:
 *           By:
 *     Update #:
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerNodeVectorRealOperatorUnary.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorUnaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal*> receiver_vec;

public:
    dtkComposerTransmitterEmitter<dtkVectorReal*> emitter_vec;
};

dtkComposerNodeVectorRealOperatorUnary::dtkComposerNodeVectorRealOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealOperatorUnaryPrivate)
{
    this->appendReceiver(&d->receiver_vec);
    this->appendEmitter(&d->emitter_vec);
}

dtkComposerNodeVectorRealOperatorUnary::~dtkComposerNodeVectorRealOperatorUnary(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorUnaryScalar
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorUnaryScalarPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal*> receiver_vec;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_val;
};

dtkComposerNodeVectorRealOperatorUnaryScalar::dtkComposerNodeVectorRealOperatorUnaryScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealOperatorUnaryScalarPrivate)
{
    this->appendReceiver(&d->receiver_vec);  

    this->appendEmitter(&d->emitter_val);
}

dtkComposerNodeVectorRealOperatorUnaryScalar::~dtkComposerNodeVectorRealOperatorUnaryScalar(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorUnary - UNITARY
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorUnaryUnitary::run(void)
{
    if (!d->receiver_vec.isEmpty()){
        dtkVectorReal *vector = d->receiver_vec.data();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorRealOperatorUnaryUnitary::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
            d->emitter_vec.clearData();
            return;
        }

        vector->makeUnit();
        d->emitter_vec.setData(vector);

    } else {
        dtkWarn() << "dtkComposerNodeVectorRealOperatorUnaryUnitary::" << Q_FUNC_INFO << "Input not specified. Nothing is done";
        d->emitter_vec.clearData();
    }
}
// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorUnaryScalar - NORM
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorUnaryScalarNorm::run(void)
{
    if (!d->receiver_vec.isEmpty()){
        const dtkVectorReal *vector = d->receiver_vec.constData();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorRealOperatorUnaryScalarNorm::" << Q_FUNC_INFO << "Input vector not set. -1 is returned";
            d->emitter_val.setData(-1);
            return;
        }        

        d->emitter_val.setData(vector->norm());

    } else {
        dtkWarn() << "dtkComposerNodeVectorRealOperatorUnaryScalarNorm::" << Q_FUNC_INFO << "Input not specified. -1 is returned";
        d->emitter_val.setData(-1);
    }


}