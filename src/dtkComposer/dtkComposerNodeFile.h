/* dtkComposerNodeFile.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEFILE_H
#define DTKCOMPOSERNODEFILE_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeFilePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeFile : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeFile(void);
    ~dtkComposerNodeFile(void);

public:
    void run(void);

public:
    QString type(void);
    QString titleHint(void);

public:
    QString inputLabelHint(int);
    QString outputLabelHint(int);

public:
    QString value(void);

public:
    void setValue(QString value);

private:
    dtkComposerNodeFilePrivate *d;
};


class dtkComposerNodeFileExistsPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeFileExists : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeFileExists(void);
    ~dtkComposerNodeFileExists(void);

public:
    void run(void);

public:
    QString type(void);
    QString titleHint(void);

public:
    QString inputLabelHint(int);
    QString outputLabelHint(int);

private:
    dtkComposerNodeFileExistsPrivate *d;
};



// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFileListDir definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeFileListPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeFileList : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeFileList(void);
    ~dtkComposerNodeFileList(void);

public:
    void run(void);

public:
    QString type(void);
    QString titleHint(void);

public:
    QString inputLabelHint(int);
    QString outputLabelHint(int);

private:
    dtkComposerNodeFileListPrivate *d;
};

#endif
