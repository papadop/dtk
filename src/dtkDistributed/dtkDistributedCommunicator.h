/* dtkDistributedCommunicator.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/02/07 11:38:59
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkDistributedPolicy.h"

#include <dtkCore/dtkCorePlugin.h>

class dtkDistributedWork;
class dtkDistributedWorker;
class dtkDistributedCommunicatorPrivate;
class dtkDistributedCommunicatorStatus;

class dtkDistributedCommunicator : public QObject
{
    Q_OBJECT

public:
             dtkDistributedCommunicator(void);
    virtual ~dtkDistributedCommunicator(void);

public:
    static const qint32 ANY_TAG    = -1;
    static const qint32 BCAST_TAG  = -7;
    static const qint32 ANY_SOURCE = -1;

    enum DataType {
        dtkDistributedCommunicatorBool,
        dtkDistributedCommunicatorChar,
        dtkDistributedCommunicatorInt,
        dtkDistributedCommunicatorLong,
        dtkDistributedCommunicatorInt64,
        dtkDistributedCommunicatorFloat,
        dtkDistributedCommunicatorDouble
    };

public:
    dtkDistributedCommunicator(const dtkDistributedCommunicator& other);
    dtkDistributedCommunicator& operator = (const dtkDistributedCommunicator& other);

public:
    virtual void  initialize(void);
    virtual bool  initialized(void);
    virtual void uninitialize(void);
    virtual bool       active(void);

public:
    virtual void setPolicy(dtkDistributedPolicy::Type type);

public:
    virtual void *allocate(qlonglong count, qlonglong size, qlonglong wid, qlonglong& buffer_id);

    virtual void deallocate(qlonglong wid, const qlonglong& buffer_id);

public:
    virtual void get(qint32 from, qlonglong position, void *array, qlonglong buffer_id) = 0;
    virtual void put(qint32 dest, qlonglong position, void  *data, qlonglong buffer_id) = 0;

public:
    virtual void send(void *data, qint64 size, DataType dataType, qint32 target, qint32 tag) = 0;
    virtual void send(char *data, qint64 size, qint32 target, qint32 tag);
    virtual void send(QByteArray& array, qint32 target, qint32 tag) = 0;
    virtual void send(const QVariant& v, qint32 target, qint32 tag);

public:
    virtual void broadcast(QByteArray& array, qint32 source) = 0;

public:
    virtual void receive(void *data, qint64 size, DataType dataType, qint32 source, qint32 tag) = 0;
    virtual void receive(char *data, qint64 size, qint32 source, qint32 tag);
    virtual void receive(QByteArray &v,  qint32 source, qint32 tag) = 0 ;
    virtual void receive(QByteArray &v,  qint32 source, qint32 tag, dtkDistributedCommunicatorStatus& status) = 0;
    virtual void receive(QVariant &v,  qint32 source, qint32 tag) ;
    /* virtual void receive(QVariant &v,  qint32 source, qint32 tag, dtkDistributedCommunicatorStatus& status) = 0; */

public:
    virtual void spawn(QStringList hostnames, qlonglong np, dtkDistributedWorker& worker);
    virtual void  exec(dtkDistributedWork *work);

public:
    virtual void unspawn(void);
    virtual void barrier(void);

public:
    virtual qint32  wid(void);
    virtual qint32 size(void);

public:
    virtual void setWid(qint32 id);

public:
    dtkDistributedCommunicatorPrivate *d;
};

DTK_DECLARE_OBJECT(dtkDistributedCommunicator*)
DTK_DECLARE_PLUGIN(dtkDistributedCommunicator)
DTK_DECLARE_PLUGIN_FACTORY(dtkDistributedCommunicator)
DTK_DECLARE_PLUGIN_MANAGER(dtkDistributedCommunicator)
