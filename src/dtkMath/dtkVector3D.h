/* dtkVector3D.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2008 - Thibaud Kloczko, Inria.
 * Created: Tue Jun  8 14:41:18 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 30 16:58:48 2012 (+0200)
 *           By: tkloczko
 *     Update #: 60
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVECTOR3D_H
#define DTKVECTOR3D_H

#include "dtkVector.h"
#include "dtkMatrixSquared.h"

template <class T = double> class dtkVector3D: public dtkVector<T>
{
public:
     dtkVector3D(void): dtkVector<T>(3U) {};
     dtkVector3D(const dtkMatrix<T>& mat): dtkVector<T>(mat) {};
     dtkVector3D(const dtkVector<T>& vec): dtkVector<T>(vec) {};
     dtkVector3D(const dtkVector3D& vec3D): dtkVector<T>(vec3D) {};
     dtkVector3D(const T&, const T&, const T&);
     dtkVector3D(const dtkMatrix<T>&, unsigned, unsigned);
     dtkVector3D(const dtkVector<T>& vec, unsigned irowStart): dtkVector<T>(vec, irowStart, irowStart + 2) {};
    ~dtkVector3D(void) {};

    void allocate(void) { dtkVector<T>::allocate(3); };

    void mapInto(const dtkMatrix<T>& mat, unsigned irowStart, unsigned icolStart);
    void mapInto(const dtkVector<T>& vec, unsigned irowStart = 0);

    dtkVector3D operator +(const dtkVector3D&) const;
    dtkVector3D operator -(const dtkVector3D&) const;
    dtkVector3D operator -(void) const;
    dtkVector3D operator *(const T&) const;

    T operator *(const dtkVector3D&) const;
    dtkVector3D operator %(const dtkVector3D&) const;
    dtkVector3D operator /(const T& value) const;

    dtkVector3D& operator  =(const dtkVector3D&);
    dtkVector3D& operator +=(const dtkVector3D&);
    dtkVector3D& operator -=(const dtkVector3D&);
    dtkVector3D& operator *=(const T&);

    dtkVector3D& operator %=(const dtkVector3D&);
    dtkVector3D& operator /=(const T& value);

    void storeOuterProduct(const dtkVector3D&, const dtkVector3D&);

    dtkVector3D unit(void) const { return (*this)/(this->norm()); }
};

template <class T> class dtkZero< dtkVector3D<T> >: public dtkVector3D<T>
{
public:
    dtkZero(void) { dtkMatrix<T>::fill(dtkZero<T>()); }
};

template <class T = double> class dtkReferential : dtkVector3D<dtkVector3D<T> >
{
public:
    dtkReferential(void) {
        (*this)[0] = dtkVector3D<T>((T)(1), (T)(0), (T)(0));
        (*this)[1] = dtkVector3D<T>((T)(0), (T)(1), (T)(0));
        (*this)[2] = dtkVector3D<T>((T)(0), (T)(0), (T)(1));
    }

    dtkReferential(dtkVector3D<T> i, dtkVector3D<T> j, dtkVector3D<T> k) {
        (*this)[0] = i;
        (*this)[1] = j;
        (*this)[2] = k;
    }

    dtkVector3D<T> i(void) { return (*this)[0]; }
    dtkVector3D<T> j(void) { return (*this)[1]; }
    dtkVector3D<T> k(void) { return (*this)[2]; }
};

// /////////////////////////////////////////////////////////////////
// Implementation of the template class dtkVector3D's methods
// /////////////////////////////////////////////////////////////////

#include "dtkVector3D.tpp"

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

#include <QtCore>

typedef dtkVector3D<qreal>  dtkVector3DReal;

Q_DECLARE_METATYPE(dtkVector3DReal);
Q_DECLARE_METATYPE(dtkVector3DReal *);

#endif

// /////////////////////////////////////////////////////////////////
// Credits
// /////////////////////////////////////////////////////////////////

// $Id: svector.h 184 2008-05-10 19:43:17Z hkuiper $

// CwMtx matrix and vector math library
// Copyright (C) 1999-2001  Harry Kuiper
// Copyright (C) 2000  Will DeVore (template conversion)

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA
