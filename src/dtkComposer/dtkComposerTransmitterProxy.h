/* dtkComposerTransmitterProxy.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Feb 20 11:17:31 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar 28 16:42:19 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 37
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerTransmitter.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterProxy 
// /////////////////////////////////////////////////////////////////

class  dtkComposerTransmitterProxy : public dtkComposerTransmitter
{
public:
     dtkComposerTransmitterProxy(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterProxy(void);

public:
    Kind kind(void) const;

    QString kindName(void) const;

public:
    void setActive(bool active);

public:
    LinkMap  leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
    LinkMap rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
};

