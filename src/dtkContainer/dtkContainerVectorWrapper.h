/* dtkContainerVectorWrapper.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri May 25 09:29:47 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri May 25 09:59:27 2012 (+0200)
 *           By: tkloczko
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCONTAINERVECTORWRAPPER_H
#define DTKCONTAINERVECTORWRAPPER_H

#include "dtkAbstractContainerWrapper.h"
#include "dtkContainerExport.h"

#include <dtkCore/dtkGlobal>

#include <dtkContainer/dtkContainerVector.h>

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkContainerVectorWrapper interface
// /////////////////////////////////////////////////////////////////

template <typename T> class DTKCORE_EXPORT dtkContainerVectorWrapper : public dtkAbstractContainerWrapper
{
public:
     dtkContainerVectorWrapper(dtkAbstractData *parent = 0);
     dtkContainerVectorWrapper(const dtkContainerVector<T>& vector, dtkAbstractData *parent = 0);
     dtkContainerVectorWrapper(const dtkContainerVectorWrapper<T>& other);
    ~dtkContainerVectorWrapper(void);

public:
    dtkContainerVectorWrapper<T>& operator = (const dtkContainerVectorWrapper<T>& other);

public:
    dtkContainerVectorWrapper<T> *clone(void) const;

public:
    void setVector(const dtkContainerVector<T>& vector);

public:
          dtkContainerVector<T>& vector(void);
    const dtkContainerVector<T>& vector(void) const;

public:
    Type type(void) const;

public:
    void clear(void);

    void  append(const QVariant& data);
    void prepend(const QVariant& data);
    void  remove(const QVariant& data);

    void  insert(const QVariant& data, dtkxarch_int index);
    void replace(const QVariant& data, dtkxarch_int index);

    void resize(dtkxarch_int size);

public:
    bool  isEmpty(void) const;
    bool contains(const QVariant& data) const;

    dtkxarch_int   count(void) const;
    dtkxarch_int indexOf(const QVariant& data, dtkxarch_int from = 0) const;
     
    QVariant    at(dtkxarch_int index) const; 

public:
    bool operator != (const dtkContainerVectorWrapper<T>& other) const;
    bool operator == (const dtkContainerVectorWrapper<T>& other) const;

public:
    bool isEqual(const dtkAbstractContainerWrapper& other) const;    

private:
    dtkContainerVector<T> m_vector;
};

// /////////////////////////////////////////////////////////////////
// dtkContainerVectorWrapper implementation
// /////////////////////////////////////////////////////////////////

#include "dtkContainerVectorWrapper.tpp"

#endif
