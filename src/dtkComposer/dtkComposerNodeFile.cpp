/* dtkComposerNodeFile.cpp --- 
 * 
 * Author: Julien Wintz, INRIA
 * Created: Thu Mar  1 11:45:03 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeFile_p.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkNotification/dtkNotification.h>

#include <QtCore>
#include <QtNetwork>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFilePrivate
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeFilePrivate::download(const QUrl& url)
{
    QFileInfo file_template_info = QFileInfo(url.path());

    QTemporaryFile file;
    if(!file_template_info.completeSuffix().isEmpty())
        file.setFileTemplate(file.fileTemplate() + "." + file_template_info.completeSuffix());
    file.setAutoRemove(false);
    
    if (!file.open()) {
        qDebug() << DTK_PRETTY_FUNCTION << "Unable to file for saving";
        return;
    }
        
    this->dwnl_ok = 0;
    
    QHttp http;
    
    connect(&http, SIGNAL(requestFinished(int, bool)), this, SLOT(onRequestFinished(int, bool)));

    http.setHost(url.host(), url.scheme().toLower() == "https" ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp, url.port() == -1 ? 0 : url.port());
        
    if (!url.userName().isEmpty())
        http.setUser(url.userName(), url.password());
        
    QByteArray path = QUrl::toPercentEncoding(url.path(), "!$&'()*+,;=:@/");
    
    if (path.isEmpty()) {
        qDebug() << DTK_PRETTY_FUNCTION << "Invalid path" << url.path();
        return;
    }
    
    this->dwnl_id = http.get(path, &file);
    
    while(!this->dwnl_ok)
        qApp->processEvents();

    file.close();

    QFileInfo info(file);
    
    this->tempName = info.absoluteFilePath();
}

void dtkComposerNodeFilePrivate::onRequestFinished(int id, bool error)
{
    DTK_UNUSED(error);

    if(id == this->dwnl_id)
        this->dwnl_ok = 1;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFile implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeFile::dtkComposerNodeFile(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeFilePrivate)
{
    this->appendReceiver(&(d->receiver));

    d->fileName = QString();
    d->emitter.setData(&d->fileName);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeFile::~dtkComposerNodeFile(void)
{
    delete d;
    
    d = NULL;
}

void dtkComposerNodeFile::run(void)
{
    QString path;

    if (!d->receiver.isEmpty())
        path = *d->receiver.data();
    else
        path = d->fileName;

    if (path.startsWith("http")) {

        d->download(QUrl(path));

        if (!d->tempName.isEmpty())
            d->fileName = d->tempName;
        else
            d->fileName = path;

    } else {

        d->fileName = path;

    }
    if (!QFile(d->fileName).exists()) {
        QString msg = QString("File %1 does not exist! ").arg(d->fileName);
        dtkNotify(msg,30000);
    }
}

QString dtkComposerNodeFile::type(void)
{
    return "file";
}

QString dtkComposerNodeFile::titleHint(void)
{
    return "File";
}

QString dtkComposerNodeFile::inputLabelHint(int port)
{
    if(port == 0)
        return "name";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeFile::outputLabelHint(int port)
{
    if(port == 0)
        return "file";

    return dtkComposerNode::outputLabelHint(port);
}

QString dtkComposerNodeFile::value(void)
{
    return d->fileName;
}

void dtkComposerNodeFile::setValue(QString value)
{
    d->fileName = value;
}



// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFileExists implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeFileExists::dtkComposerNodeFileExists(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeFileExistsPrivate)
{
    this->appendReceiver(&(d->receiver));

    d->exists = false;
    d->emitter.setData(&d->exists);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeFileExists::~dtkComposerNodeFileExists(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeFileExists::run(void)
{
    if (!d->receiver.isEmpty()) {
        if (d->receiver.data()) {
            QString filename = *(d->receiver.data());
            d->exists = QFile(filename).exists();
        }
    }
}

QString dtkComposerNodeFileExists::type(void)
{
    return "fileExists";
}

QString dtkComposerNodeFileExists::titleHint(void)
{
    return "FileExists";
}

QString dtkComposerNodeFileExists::inputLabelHint(int port)
{
    if(port == 0)
        return "file";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeFileExists::outputLabelHint(int port)
{
    if(port == 0)
        return "exists";

    return dtkComposerNode::outputLabelHint(port);
}




// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFileList implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeFileList::dtkComposerNodeFileList(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeFileListPrivate)
{
    this->appendReceiver(&(d->receiver_dir));
    QList<int> variant_list;
    variant_list << QMetaType::QString << QMetaType::QStringList;
    d->receiver_filters.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_filters));

    d->emitter_files.setData(&(d->files));
    this->appendEmitter(&(d->emitter_files));
}

dtkComposerNodeFileList::~dtkComposerNodeFileList(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeFileList::run(void)
{
    if (!d->receiver_dir.isEmpty()) {
        d->files.clear();
        if (d->receiver_dir.data()) {
            QString dirname = *(d->receiver_dir.data());
            QDir dir(dirname);
            if (!d->receiver_filters.isEmpty()) {

                switch(d->receiver_filters.dataType()) {
                case QMetaType::QString: {
                    dir.setNameFilters(QStringList(*(d->receiver_filters.data<QString>())));
                    break;
                }
                case QMetaType::QStringList: {
                    dir.setNameFilters(*(d->receiver_filters.data<QStringList>()));
                    break;
                }
                default:
                    dtkWarn() << "Type" << d->receiver_filters.dataType() << "is not handled by the node. Only QString and QString List are supported";
                    break;
                }
            }
            foreach (QString file, dir.entryList()) {
                d->files << file;
            }
        }
    }
}

QString dtkComposerNodeFileList::type(void)
{
    return "fileList";
}

QString dtkComposerNodeFileList::titleHint(void)
{
    return "FileList";
}

QString dtkComposerNodeFileList::inputLabelHint(int port)
{
    if(port == 0)
        return "directory";
    if(port == 1)
        return "pattern";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeFileList::outputLabelHint(int port)
{
    if(port == 0)
        return "files";

    return dtkComposerNode::outputLabelHint(port);
}
