/* dtkComposerControls.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Nov 20 16:21:59 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 28 16:10:54 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 166
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerControls.h"
#include "dtkComposerControlsDelegate.h"
#include "dtkComposerNode.h"
#include "dtkComposerScene.h"
#include "dtkComposerSceneNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

int type(dtkComposerSceneNodeLeaf *node);

// /////////////////////////////////////////////////////////////////
// dtkComposerControlsPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerControlsPrivate
{
public:
    dtkComposerScene *scene;

public:
    QComboBox *selector;
    QListWidget *list;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerControls
// /////////////////////////////////////////////////////////////////

dtkComposerControls::dtkComposerControls(QWidget *parent) : QFrame(parent), d(new dtkComposerControlsPrivate)
{
    d->scene = NULL;

// /////////////////////////////////////////////////////////////////

    d->selector = new QComboBox(this);
    d->selector->addItem(QIcon(":dtkComposer/pixmaps/dtk-composer-node-flag-blue.png"), "Blue flagged nodes");
    d->selector->addItem(QIcon(":dtkComposer/pixmaps/dtk-composer-node-flag-gray.png"), "Gray flagged nodes");
    d->selector->addItem(QIcon(":dtkComposer/pixmaps/dtk-composer-node-flag-green.png"), "Green flagged nodes");
    d->selector->addItem(QIcon(":dtkComposer/pixmaps/dtk-composer-node-flag-orange.png"), "Orange flagged nodes");
    d->selector->addItem(QIcon(":dtkComposer/pixmaps/dtk-composer-node-flag-pink.png"), "Pink flagged nodes");
    d->selector->addItem(QIcon(":dtkComposer/pixmaps/dtk-composer-node-flag-red.png"), "Red flagged nodes");
    d->selector->addItem(QIcon(":dtkComposer/pixmaps/dtk-composer-node-flag-yellow.png"), "Yellow flagged nodes");

// /////////////////////////////////////////////////////////////////

    d->list = new QListWidget(this);
    d->list->setAttribute(Qt::WA_MacShowFocusRect, false);
    d->list->setEditTriggers(QAbstractItemView::DoubleClicked);
    d->list->setItemDelegate(new dtkComposerControlsDelegate(this));

// /////////////////////////////////////////////////////////////////

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(d->selector);
    layout->addWidget(d->list);

// /////////////////////////////////////////////////////////////////

    this->setFixedWidth(300);

// /////////////////////////////////////////////////////////////////

    connect(d->selector, SIGNAL(currentIndexChanged(int)), this, SLOT(setup(int)));
}

dtkComposerControls::~dtkComposerControls(void)
{
    delete d;

    d = NULL;
}

void dtkComposerControls::setScene(dtkComposerScene *scene)
{
    if(d->scene)
        disconnect(d->scene, SIGNAL(flagged()), this, SLOT(setup()));

    d->scene = scene;

    if(d->scene)
        connect(d->scene, SIGNAL(flagged()), this, SLOT(setup()));

    this->setup();
}

void dtkComposerControls::setup(void)
{
    this->setup(d->selector->currentIndex());
}

void dtkComposerControls::setup(int index)
{
    if(!d->scene)
        return;

    QList<dtkComposerSceneNodeLeaf *> nodes;

    switch(index) {
    case 0:
        nodes = d->scene->flagged(Qt::blue);
        break;
    case 1:
        nodes = d->scene->flagged(Qt::gray);
        break;
    case 2:
        nodes = d->scene->flagged(Qt::green);
        break;
    case 3:
        nodes = d->scene->flagged(Qt::darkYellow);
        break;
    case 4:
        nodes = d->scene->flagged(Qt::magenta);
        break;
    case 5:
        nodes = d->scene->flagged(Qt::red);
        break;
    case 6:
        nodes = d->scene->flagged(Qt::yellow);
        break;
    default:
        break;
    };

    d->list->clear();

    foreach(dtkComposerSceneNodeLeaf *node, nodes) {
        QListWidgetItem *item = new QListWidgetItem(node->title(), d->list, type(node));
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        d->list->addItem(item);
    }
}

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

int type(dtkComposerSceneNodeLeaf *node)
{
    if(node->wrapee()->type() == "integer")
        return dtkComposerControls::Integer;

    return dtkComposerControls::None;
}
