/* @(#)dtkDistributedCommunicator.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/02/07 13:59:41
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedCommunicator.h"
#include "dtkDistributedWorker.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedCommunicatorPrivate
// /////////////////////////////////////////////////////////////////

class dtkDistributedCommunicatorPrivate
{
public:
    QMap<qlonglong, void *> buffer_map;

public:
    qlonglong id;

public:
    bool initialized;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributedCommunicator
// /////////////////////////////////////////////////////////////////

/*!
  \class dtkDistributedCommunicator
  \inmodule dtkDistributed
  \brief ...
 */

dtkDistributedCommunicator::dtkDistributedCommunicator(void) : QObject(), d(new dtkDistributedCommunicatorPrivate)
{
    d->id = 0;
    d->initialized = false;
}

dtkDistributedCommunicator::~dtkDistributedCommunicator(void)
{
    delete d;

    d = NULL;
}

dtkDistributedCommunicator::dtkDistributedCommunicator(const dtkDistributedCommunicator& other)
{

}

dtkDistributedCommunicator& dtkDistributedCommunicator::operator = (const dtkDistributedCommunicator& other)
{
    return *this;

}

void dtkDistributedCommunicator::initialize(void)
{
    d->initialized = true;
}

bool dtkDistributedCommunicator::initialized(void)
{
    return d->initialized;
}

void dtkDistributedCommunicator::uninitialize(void)
{
    d->initialized = false;
}

bool dtkDistributedCommunicator::active(void)
{
    return false;
}

void dtkDistributedCommunicator::setPolicy(QString type)
{
}

/*! \fn dtkDistributedCommunicator::spawn (QStringList hostnames, qlonglong np, dtkDistributedWorker& worker)

  Spawn a communicator on all hostnames, starting np threads on each
  process. Once the processes and threads are started, use the worker
  to do the work.

*/

void dtkDistributedCommunicator::spawn(QStringList hostnames, qlonglong np, dtkDistributedWorker& worker)
{
    qDebug() << Q_FUNC_INFO;
}

void dtkDistributedCommunicator::unspawn(void)
{
}

void dtkDistributedCommunicator::exec(dtkDistributedWork *work)
{
//   DTK_DEFAULT_IMPLEMENTATION;
}

void dtkDistributedCommunicator::barrier(void)
{
//   DTK_DEFAULT_IMPLEMENTATION;
}

qint32 dtkDistributedCommunicator::wid(void)
{
   return 0;
}

void dtkDistributedCommunicator::setWid(qint32 id)
{
}

qint32 dtkDistributedCommunicator::size(void)
{
   return 1;
}

void *dtkDistributedCommunicator::allocate(qlonglong count, qlonglong size, qlonglong wid, qlonglong& buffer_id)
{
    void *buffer = malloc(size*count);
    d->buffer_map.insert(d->id, buffer);
    buffer_id = (d->id)++;
    return buffer;
}

void dtkDistributedCommunicator::deallocate(qlonglong wid, const qlonglong& buffer_id)
{
    void *buffer = d->buffer_map.take(buffer_id);
    free (buffer);
}

void dtkDistributedCommunicator::send(char *data, qint64 size, qint32 target, qint32 tag)
{
    return this->send(data, size, Char, target, tag);
}

void dtkDistributedCommunicator::send(const QVariant &v, qint32 target, qint32 tag)
{
    QByteArray bytes;
    QDataStream stream(&bytes,QIODevice::WriteOnly);
    stream << v;
    this->send(bytes, target, tag);
}

void dtkDistributedCommunicator::receive(char *data, qint64 size, qint32 source, qint32 tag)
{
    return this->receive(data, size, Char, source, tag);
}

void dtkDistributedCommunicator::receive(QVariant &v, qint32 target, qint32 tag)
{
    QByteArray bytes;
    this->receive(bytes, target, tag);
    QDataStream stream(&bytes,QIODevice::ReadOnly);
    stream >> v;
}

void dtkDistributedCommunicator::reduce(void   *send, void   *recv, qint64 size, DataType dataType, OperationType operationType, qint16 target, bool all)
{
    qCritical() << "Default operator for reduce, not implemented";
}

void dtkDistributedCommunicator::reduce(bool *send, bool *recv, qint64 size, OperationType operationType, qint16 target, bool all)
{
    return this->reduce(send, recv, size, Bool, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(char *send, char *recv, qint64 size, OperationType operationType, qint16 target, bool all)
{
    return this->reduce(send, recv, size, Char, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(int *send, int *recv, qint64 size, OperationType operationType, qint16 target, bool all)
{
    return this->reduce(send, recv, size, Int, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(qlonglong *send, qlonglong *recv, qint64 size, OperationType operationType, qint16 target, bool all)
{
    return this->reduce(send, recv, size, Int64, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(float *send, float *recv, qint64 size, OperationType operationType, qint16 target, bool all)
{
    return this->reduce(send, recv, size, Float, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(double *send, double *recv, qint64 size, OperationType operationType, qint16 target, bool all)
{
    return this->reduce(send, recv, size, Double, operationType, target, all);
}
