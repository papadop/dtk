/* dtkDistributedSocket.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: 2011/09/20 09:16:29
 * Version: $Id$
 * Last-Updated: mar. avril 17 18:41:55 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 687
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkCore/dtkGlobal.h>

#include <dtkLog/dtkLog.h>

#include "dtkDistributedSocket.h"

class dtkDistributedSocketPrivate
{
};

dtkDistributedSocket::dtkDistributedSocket( QObject* parent ) :  QTcpSocket(parent), d(new dtkDistributedSocketPrivate)
{
}

dtkDistributedSocket::~dtkDistributedSocket(void)
{
    delete d;
    d = NULL;
}

qint64 dtkDistributedSocket::sendRequest( dtkDistributedMessage *msg)
{

    QString buffer;

    buffer += msg->req();
    if (msg->size() == 0 ) {
        buffer += "content-size: 0\n\n";
        qint64 ret = this->write(buffer.toAscii());
        this->flush();
        return ret;
    } else if (msg->size() > 0) {
        buffer += "content-size: "+ QString::number(msg->size()) +"\n";
        if (!msg->type().isEmpty() && !msg->type().isNull())
            buffer += "content-type: " +msg->type() +"\n";

        foreach (const QString &key, (msg->headers()).keys())
            buffer += key +": " + msg->header(key) +"\n";
        buffer += "\n";
    }

    qint64 ret;
    if (msg->content().isNull() || msg->content().isEmpty()) {
        // no content provided, the caller is supposed to send the content itself
        ret = this->write(buffer.toAscii());
    } else {
        ret = this->write(buffer.toAscii());
        ret += this->write(msg->content());
    }

    return ret;
}

bool dtkDistributedSocket::waitForData(int max_wait) {
    this->blockSignals(true);
    bool res = this->waitForReadyRead(max_wait);
    this->blockSignals(false);
    return res;
}

/**
 * read and parse data from socket
 *
 * @return dtkDistributedMessage
 */
dtkDistributedMessage *dtkDistributedSocket::parseRequest(void)
{
    dtkDistributedMessage *msg = new dtkDistributedMessage;

    msg->setMethod(this->readLine());

    // read content-size
    msg->setSize(this->readLine());

    if (msg->size() > 0) {
        //read content-type
        msg->setType(this->readLine());

        // read optional headers
        QByteArray line = this->readLine();
        while (!QString(line).trimmed().isEmpty()) {// empty line after last header
            msg->setHeader(QString(line));
            line=this->readLine();
        }

        // read content
        QByteArray buffer;
        buffer.append(this->read(msg->size()));
        while (buffer.size() < msg->size() ) {
            if (this->waitForReadyRead()) {
                buffer.append(this->read(msg->size()-buffer.size()));
            } else {
                dtkWarn() << "not enough data received, only  " << buffer.size() << "out of " << msg->size() ;
                msg->setContent(buffer);
                msg->addHeader("missing_data",QString::number(msg->size()-buffer.size()));
                break;
            }
        }
        msg->setContent(buffer);
    } else
        // end of request == empty line
        this->readLine();

    return msg;
}
