/* dtkAbstractDataReader.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 24 22:03:03 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Sep 15 15:11:44 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 38
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractDataReader.h>

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkSmartPointer.h>

class dtkAbstractDataReaderPrivate
{
public:
    bool enabled;

    dtkSmartPointer<dtkAbstractData> data;
};

dtkAbstractDataReader::dtkAbstractDataReader(void) : dtkAbstractObject(), d(new dtkAbstractDataReaderPrivate)
{
    d->enabled = false;
}

dtkAbstractDataReader::~dtkAbstractDataReader(void)
{
    delete d;

    d = NULL;
}

bool dtkAbstractDataReader::enabled(void) const
{
    return d->enabled;
}

void dtkAbstractDataReader::enable(void)
{
    d->enabled = true;
}

void dtkAbstractDataReader::disable(void)
{
    d->enabled = false;
}

dtkAbstractData *dtkAbstractDataReader::data(void)
{
    return d->data;
}

/**
 * Set the data that has been read.
 * The reader will increase the reference count of the data.
 */
void dtkAbstractDataReader::setData(dtkAbstractData *data)
{
    d->data = data;
}

//  Verify that the reader can handle this/these file(s).

bool dtkAbstractDataReader::canRead(const QString& file)
{
    DTK_UNUSED(file);

    return false;
}

bool dtkAbstractDataReader::canRead(const QStringList& files)
{
    if (files.size()==1)
        return canRead(files[0]);

    return false;
}

bool dtkAbstractDataReader::read(const QString& file)
{
    DTK_UNUSED(file);

    return false;
}

bool dtkAbstractDataReader::read(const QStringList& files)
{
    DTK_UNUSED(files);

    return false;
}

void dtkAbstractDataReader::readInformation(const QString& path)
{
    DTK_UNUSED(path);
}

void dtkAbstractDataReader::readInformation(const QStringList& paths)
{
    if (paths.size()==1)
        return readInformation(paths[0]);
}

void dtkAbstractDataReader::setProgress(int value)
{
    emit progressed (value);
}
