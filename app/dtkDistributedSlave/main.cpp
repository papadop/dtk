/* @(#)main.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2014 - Nicolas Niclausse, Inria.
 * Created: 2014/04/25 16:28:19
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */



#include <dtkCore/dtkCore.h>

#include <dtkDistributed/dtkDistributed.h>
#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedSettings.h>
#include <dtkDistributed/dtkDistributedSlave.h>
#include <dtkDistributed/dtkDistributedPolicy.h>
#include <dtkDistributed/dtkDistributedMessage.h>
#include <dtkDistributed/dtkDistributedWork.h>
#include <dtkDistributed/dtkDistributedWorker.h>
#include <dtkDistributed/dtkDistributedWorkerManager.h>

#include <dtkLog>

#include <QtCore>

#include <iostream>

class simpleWork : public dtkDistributedWork
{
public:
    simpleWork *clone(void) { return new simpleWork(*this); };

public:
    QString server;

public:
    void run(void) {

        QTime time;
        qDebug() << wid();
        qDebug() << wct();
        dtkDistributedSlave slave;

        DTK_DISTRIBUTED_BEGIN_GLOBAL;

        QUrl url(server);

        qDebug() << "Running on master, connect to remote server" ;
        slave.connect(url);
        qDebug() << "slave connected to server " << slave.isConnected();

        if (slave.isConnected()) {
            dtkDistributedMessage msg(dtkDistributedMessage::SETRANK,slave.jobId(),dtkDistributedMessage::SLAVE_RANK);
            msg.send(slave.socket());
        }

        DTK_DISTRIBUTED_END_GLOBAL;

        qDebug() << "I'm the simple slave " << wid() ;

        QThread::sleep(60);

        DTK_DISTRIBUTED_BEGIN_GLOBAL;
        if (slave.isConnected()) {
           dtkDistributedMessage msg(dtkDistributedMessage::ENDJOB,slave.jobId(),dtkDistributedMessage::SLAVE_RANK);
           msg.send(slave.socket());
        }

        DTK_DISTRIBUTED_END_GLOBAL;

    }
};

int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);
    QCoreApplication::setApplicationName("dtkDistributedSlave");
    QCoreApplication::setApplicationVersion("1.0.0");

    QString policyType = "qthread";

    QCommandLineParser parser;
    parser.setApplicationDescription("DTK distributed slave example application: it connect to the DTK distributed server and waits for 1 minute before exiting.");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption policyOption("policy", QCoreApplication::translate("main", "dtkDistributed policy"), policyType);
    parser.addOption(policyOption);
    QCommandLineOption serverOption("server", QCoreApplication::translate("main", "server URL"));
    parser.addOption(serverOption);

    if (!parser.parse(QCoreApplication::arguments())) {
        qCritical() << "Command line error" ;
        return 1;
    }

    parser.process(application);

     if (!parser.isSet(serverOption)) {
         qCritical() << "Error: no server set ! Use --server <url> " ;
         return 1;
     }

    // the server waits for the jobid in stdout
    std::cout << QString("DTK_JOBID="+dtkDistributedSlave::jobId()).toStdString() << std::endl << std::flush;

    // plugins
    dtkDistributedSettings settings;
    settings.beginGroup("communicator");
    qDebug() << "initialize plugin manager "<< settings.value("plugins").toString();
    dtkDistributed::communicator::pluginManager().initialize(settings.value("plugins").toString());
    qDebug() << "initialization done ";
    settings.endGroup();

    qDebug() << dtkDistributed::communicator::pluginManager().plugins();
    qDebug() << dtkDistributed::communicator::pluginFactory().keys();


    // work

    simpleWork *work = new simpleWork;
    work->server = parser.value(serverOption);

    dtkDistributedPolicy policy;

     if (parser.isSet(policyOption)) {
         policyType = parser.value(policyOption);
     }
    policy.setType(policyType);

    dtkDistributedWorkerManager manager;

    manager.setPolicy(&policy);
    manager.spawn();
    manager.exec(work);

    return 0;
}
