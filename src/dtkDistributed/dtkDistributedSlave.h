/* dtkDistributedSlave.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:13:03 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mar. oct.  4 16:31:23 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 66
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDSLAVE_H
#define DTKDISTRIBUTEDSLAVE_H

#include "dtkDistributedExport.h"
#include "dtkDistributedCommunicatorTcp.h"

#include <QtCore>
#include <QtNetwork>

class dtkDistributedSlavePrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedSlave : public QObject
{
    Q_OBJECT

public:
     dtkDistributedSlave(void);
    ~dtkDistributedSlave(void);

public:
    virtual int run(void);

public:
    bool    isConnected(void);
    bool isDisconnected(void);

    bool flush(void);
    void close(void);

signals:
    void    connected(const QUrl& server);
    void disconnected(const QUrl& server);

    void started(void);
    void   ended(void);

public slots:
    void    connect(const QUrl& server);
    void disconnect(const QUrl& server);

protected:
    virtual int exec(void) = 0;

    dtkDistributedCommunicatorTcp *communicator();

protected slots:
    void onStarted(void);
    void   onEnded(void);

protected slots:
    void error(QAbstractSocket::SocketError error);

private:
    dtkDistributedSlavePrivate *d;
};

#endif
