/* dtkAbstractDataTypedImage2D.h --- 
 * 
 * Author: Theo Papadopoulo
 * Copyright (C) 2011 - Theo Papadopoulo, Inria.
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATATYPEDIMAGE2D_H
#define DTKABSTRACTDATATYPEDIMAGE2D_H

#include <dtkCore/dtkAbstractDataImage.h>

template <unsigned DIM,typename T>
class DTKCORE_EXPORT dtkAbstractDataTypedImage: public dtkAbstractDataImage {
public:

    dtkAbstractDataTypedImage() { }
   ~dtkAbstractDataTypedImage() { }

    int                                Dimension() const { return DIM;       }
    const dtkAbstractDataImage::PixId& PixelType() const { return typeid(T); }
};

#endif
