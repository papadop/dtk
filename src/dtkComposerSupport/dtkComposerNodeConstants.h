/* dtkComposerNodeConstants.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:58:13 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONSTANTS_H
#define DTKCOMPOSERNODECONSTANTS_H

#include <dtkConfig.h>

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"


// /////////////////////////////////////////////////////////////////
// PI
// /////////////////////////////////////////////////////////////////

class dtkComposerNodePiPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodePi : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodePi(void);
    ~dtkComposerNodePi(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "pi";
    }

    inline QString titleHint(void) {
        return "Pi";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

private:
    dtkComposerNodePiPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// E
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeEPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeE : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeE(void);
    ~dtkComposerNodeE(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "e";
    }

    inline QString titleHint(void) {
        return "E";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

private:
    dtkComposerNodeEPrivate *d;
};

#if defined(DTK_BUILD_DISTRIBUTED)

// /////////////////////////////////////////////////////////////////
// CONTROLLER_RUN_RANK
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControllerRunRankPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeControllerRunRank : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeControllerRunRank(void);
    ~dtkComposerNodeControllerRunRank(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "ControllerRunRank";
    }

    inline QString titleHint(void) {
        return "CONTROLLER_RUN_RANK";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

private:
    dtkComposerNodeControllerRunRankPrivate *d;
};

#endif

#if defined(DTK_BUILD_DISTRIBUTED)

// /////////////////////////////////////////////////////////////////
// MPI_ANY_TAG
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeAnyTagPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeAnyTag : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeAnyTag(void);
    ~dtkComposerNodeAnyTag(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "AnyTag";
    }

    inline QString titleHint(void) {
        return "ANY_TAG";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

private:
    dtkComposerNodeAnyTagPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// MPI_ANY_SOURCE
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeAnySourcePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeAnySource : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeAnySource(void);
    ~dtkComposerNodeAnySource(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "AnySource";
    }

    inline QString titleHint(void) {
        return "ANY_SOURCE";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

private:
    dtkComposerNodeAnySourcePrivate *d;
};


#endif

#endif