/* dtkDistributedCommunicatorMpi.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 16:50:54 2010 (+0100)
 * Version: $Id$
 * Last-Updated: ven. déc. 13 10:02:24 2013 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 188
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCOMMUNICATORMPI_H
#define DTKDISTRIBUTEDCOMMUNICATORMPI_H

#include "dtkDistributedExport.h"
#include "dtkDistributedCommunicator.h"

class dtkDistributedCommunicatorMpiPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedCommunicatorMpi : public dtkDistributedCommunicator
{
    Q_OBJECT

public:
     dtkDistributedCommunicatorMpi(void);
    ~dtkDistributedCommunicatorMpi(void);

public:
    dtkDistributedCommunicatorMpi(const dtkDistributedCommunicatorMpi& other);
    dtkDistributedCommunicatorMpi& operator=(const dtkDistributedCommunicatorMpi& other);

public:
    void  initialize(void);
    bool  initialized(void);
    void uninitialize(void);

    dtkDistributedCommunicator *spawn(QString cmd, qlonglong np);

    double time(void);
    double tick(void);

    int rank(void);
    int size(void);

    QString name(void) const;

public:
    void   barrier(void);
    void      send(void *data,             qint64 size, DataType dataType, qint16 target, int tag);
    void   receive(void *data,             qint64 size, DataType dataType, qint16 source, int tag);
    void   receive(void *data,             qint64 size, DataType dataType, qint16 source, int tag, dtkDistributedCommunicatorStatus& status);
    void broadcast(void *data,             qint64 size, DataType dataType, qint16 source);
    void    gather(void *send, void *recv, qint64 size, DataType dataType, qint16 target, bool all = false);
    void   scatter(void *send, void *recv, qint64 size, DataType dataType, qint16 source);
    void    reduce(void *send, void *recv, qint64 size, DataType dataType, OperationType operationType, qint16 target, bool all = false);

    void      send(dtkAbstractData *data, qint16 target, int tag);
    void      send(const QString& s, qint16 target, int tag) ;
    void      send(QByteArray& array, qint16 target, int tag) ;

    void isend(void *data, qint64 size, DataType dataType, qint16 target, int tag, dtkDistributedCommunicatorRequest *req);
    void isend(dtkAbstractData *data, qint16 target, int tag, dtkDistributedCommunicatorRequest *req);
    void isend(const QString& s, qint16 target, int tag, dtkDistributedCommunicatorRequest *req) ;
    void isend(QByteArray& array, qint16 target, int tag, dtkDistributedCommunicatorRequest *req) ;

    void broadcast(     QByteArray& array, qint16 source);
    void broadcast(            QString& s, qint16 source);
    void broadcast(dtkAbstractData *&data, qint16 source);

    void   receive(dtkAbstractData *&data, qint16 source, int tag);
    void   receive(QString &s, qint16 source, int tag) ;
    void   receive(QByteArray &a, qint16 source, int tag) ;
    void   receive(QByteArray &a, qint16 source, int tag, dtkDistributedCommunicatorStatus& status) ;

    void ireceive(void *data, qint64 size, DataType dataType, qint16 source, int tag, dtkDistributedCommunicatorRequest *req);
    /* void ireceive(dtkAbstractData *&data, qint16 source, int tag); */
    /* void ireceive(QString &s, qint16 source, int tag) ; */
    /* void ireceive(QByteArray &a, qint16 source, int tag) ; */

private:
    dtkDistributedCommunicatorMpiPrivate *d;
};




class dtkDistributedCommunicatorRequestMpiPrivate;
class DTKDISTRIBUTED_EXPORT dtkDistributedCommunicatorRequestMpi : public dtkDistributedCommunicatorRequest
{
public:
             dtkDistributedCommunicatorRequestMpi(void);
    virtual ~dtkDistributedCommunicatorRequestMpi(void);

public:
    void wait(void);

public:
    dtkDistributedCommunicatorRequestMpiPrivate *d_func(void) { return d; }

private:
    dtkDistributedCommunicatorRequestMpiPrivate *d;
};



Q_DECLARE_METATYPE(dtkDistributedCommunicatorMpi);
Q_DECLARE_METATYPE(dtkDistributedCommunicatorMpi*);


#endif
