/* dtkAbstractDataFace.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Dec 11 11:04:22 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb  1 22:17:17 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATAFACE_H
#define DTKABSTRACTDATAFACE_H

#include "dtkAbstractData.h"

class dtkAbstractDataVertex;
class dtkAbstractDataEdge;

class dtkAbstractDataFace : public dtkAbstractData
{
    Q_OBJECT

public:
             dtkAbstractDataFace(dtkAbstractData *parent = 0);
    virtual ~dtkAbstractDataFace(void);

    enum Type {
        dtkAbstractDataFaceTriangle,
        dtkAbstractDataFaceQuad,
        dtkAbstractDataFacePolygon
    };

    virtual int countVertices(void) = 0;
    virtual int countEdges(void) = 0;

    virtual QList<dtkAbstractDataVertex *> vertices(void) = 0;
    virtual QList<dtkAbstractDataEdge *> edges(void) = 0;

    virtual Type type(void) = 0;
};

#endif
