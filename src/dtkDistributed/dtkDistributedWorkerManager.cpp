/* @(#)dtkDistributedWorkerManager.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/02/14 13:20:59
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedWorkerManager.h"

#include "dtkDistributedCommunicator.h"
#include "dtkDistributedPolicy.h"
#include "dtkDistributedWorker.h"

class dtkDistributedWorkerManagerPrivate
{

public:
    dtkDistributedCommunicator *comm;
    dtkDistributedPolicy *policy;
    dtkDistributedWorker worker;

};

dtkDistributedWorkerManager::dtkDistributedWorkerManager(void) : QObject(), d(new dtkDistributedWorkerManagerPrivate)
{
    d->comm   = NULL;
    d->policy = NULL;
}

dtkDistributedWorkerManager::~dtkDistributedWorkerManager(void)
{
    delete d;

    d = NULL;
}

dtkDistributedWorkerManager::dtkDistributedWorkerManager(const dtkDistributedWorkerManager& other)
{
}

dtkDistributedWorkerManager& dtkDistributedWorkerManager::operator = (const dtkDistributedWorkerManager& other)
{
    return (*this);
}

void dtkDistributedWorkerManager::setCommunicator(dtkDistributedCommunicator *comm)
{
    d->comm = comm;
}

void dtkDistributedWorkerManager::setPolicy(dtkDistributedPolicy *policy)
{
    d->policy = policy;
    d->comm = policy->communicator();
}

void dtkDistributedWorkerManager::setWork(dtkDistributedWork *work)
{
    d->worker.setWork(work);
}

void dtkDistributedWorkerManager::spawn(void)
{
    d->worker.setCommunicator(d->comm);

    QStringList hosts = d->policy->hosts();

    d->comm->spawn(hosts, hosts.count(), d->worker);
}

void dtkDistributedWorkerManager::exec(void)
{
    d->comm->exec();
}

void dtkDistributedWorkerManager::unspawn(void)
{
    d->comm->uninitialize();
}