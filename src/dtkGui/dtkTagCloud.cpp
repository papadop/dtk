/* dtkTagCloud.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun May  3 10:42:27 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Feb 28 17:33:53 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 1179
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkFlowLayout.h"
#include "dtkTagCloud.h"

#include <QtDebug>

// /////////////////////////////////////////////////////////////////
// helper functions
// /////////////////////////////////////////////////////////////////

bool dtkTagAlphaLessThan(const dtkTag &t1, const dtkTag &t2) {
    return t1.text() < t2.text();
}

bool dtkTagNumLessThan(const dtkTag &t1, const dtkTag &t2) {
    return t1.count() < t2.count();
}

bool dtkTagAlphaMoreThan(const dtkTag &t1, const dtkTag &t2) {
    return t1.text() >= t2.text();
}

bool dtkTagNumMoreThan(const dtkTag &t1, const dtkTag &t2) {
    return t1.count() >= t2.count();
}

// /////////////////////////////////////////////////////////////////
// dtkTagCloudHasher
// /////////////////////////////////////////////////////////////////

class dtkTagCloudHasher
{
public:
    dtkTagCloudHasher(int buckets, int min, int max) {
        if (buckets < 1)
            qDebug() << "dtkTagCloudHasher: Must have at least one bucket.";

        this->buckets = buckets;
        this->min = min;
        this->max = max+1;

        this->width = ((double)(this->max-this->min))/((double)(this->buckets));
    }

    int bucket(dtkTag tag) {
        return ((float)(tag.count()-this->min))/((float)(this->width));
    }

private:
    int min, max, buckets;

private:
    double width;
};

// /////////////////////////////////////////////////////////////////
// dtkTagPrivate
// /////////////////////////////////////////////////////////////////

class dtkTagPrivate
{
public:
    int count;
    QString text;
    QString color;
    QStringList items;
};

// /////////////////////////////////////////////////////////////////
// dtkTag
// /////////////////////////////////////////////////////////////////

dtkTag::dtkTag(void) : d(new dtkTagPrivate)
{
    d = new dtkTagPrivate;
}

dtkTag::dtkTag(QString text, int count) : d(new dtkTagPrivate)
{
    d = new dtkTagPrivate;
    d->text = text;
    d->count = count;
}

dtkTag::dtkTag(QString text, int count, QStringList items) : d(new dtkTagPrivate)
{
    d = new dtkTagPrivate;
    d->text = text;
    d->count = count;
    d->items = items;
}

dtkTag::dtkTag(QString text, int count, QStringList items, QString color) : d(new dtkTagPrivate)
{
    d = new dtkTagPrivate;
    d->text = text;
    d->count = count;
    d->items = items;
    d->color = color;
}

dtkTag::dtkTag(const dtkTag& other)
{
    d = new dtkTagPrivate;
    d->text = other.d->text;
    d->count = other.d->count;
    d->items = other.d->items;
    d->color = other.d->color;
}

dtkTag::~dtkTag(void)
{
    delete d;

    d = NULL;
}

int dtkTag::count(void) const
{
    return d->count;
}

QString dtkTag::text(void) const
{
    return d->text;
}

QStringList dtkTag::items(void) const
{
    return d->items;
}

QString dtkTag::color(void) const
{
    return d->color;
}

void dtkTag::setCount(int count)
{
    if (count > 0)
        d->count = count;
    else
        d->count = count;
}

void dtkTag::setText(QString text)
{
    if (!text.isNull())
        d->text = text;
    else
        d->text = "";
}

void dtkTag::setItems(QStringList items)
{
    if (!items.isEmpty())
        d->items = items;
    else
        d->items = QStringList();
}

void dtkTag::setColor(QString color)
{
    if (!color.isNull())
        d->color = color;
    else
        d->color = "";
}

// /////////////////////////////////////////////////////////////////
// dtkTagCloudPrivate
// /////////////////////////////////////////////////////////////////

class dtkTagCloudPrivate
{
public:
    QList<dtkTag> tags;

    int averageFontSize;
    int fontSizeRange;
    int mincount;
    int maxcount;
    int tagCount;

    dtkTagCloud::SortingType  sortingType;
    dtkTagCloud::SortingOrder sortingOrder;
};

// /////////////////////////////////////////////////////////////////
// dtkTagCloud
// /////////////////////////////////////////////////////////////////

dtkTagCloud::dtkTagCloud(QWidget *parent) : QTextBrowser(parent)
{
    d = new dtkTagCloudPrivate;

    d->averageFontSize = 0;
    d->fontSizeRange   = 0;

    d->sortingType  = Alpha;
    d->sortingOrder = Asc;

    this->setFrameShape(QFrame::NoFrame);

    connect(this, SIGNAL(anchorClicked(const QUrl&)), this, SLOT(onLinkClicked(const QUrl&)));
}

dtkTagCloud::~dtkTagCloud(void)
{
    delete d;
}

void dtkTagCloud::addTag(QString text, int count)
{
    d->tags << dtkTag(text, count);
}

void dtkTagCloud::addTag(QString text, int count, QStringList items)
{
    d->tags << dtkTag(text, count, items);
}

void dtkTagCloud::addTag(QString text, int count, QStringList items, QString color)
{
    d->tags << dtkTag(text, count, items, color);
}

void dtkTagCloud::addTag(dtkTag tag)
{
    d->tags << tag;
}

void dtkTagCloud::setFontSize(int size)
{
    d->averageFontSize = (size > 0) ? size : 0;
}

void dtkTagCloud::setFontRange(int range)
{
    d->fontSizeRange = (range > 0) ? range: 0;
}

void dtkTagCloud::setSortingType(SortingType type)
{
    d->sortingType = type;
}

void dtkTagCloud::setSortingOrder(SortingOrder order)
{
    d->sortingOrder = order;
}

void dtkTagCloud::sort(void)
{
    if(d->sortingType == Alpha && d->sortingOrder == Asc)
        qSort(d->tags.begin(), d->tags.end(), dtkTagAlphaLessThan);

    if(d->sortingType == Alpha && d->sortingOrder == Desc)
        qSort(d->tags.begin(), d->tags.end(), dtkTagAlphaMoreThan);

    if(d->sortingType == Num && d->sortingOrder == Asc)
        qSort(d->tags.begin(), d->tags.end(), dtkTagNumLessThan);

    if(d->sortingType == Num && d->sortingOrder == Desc)
        qSort(d->tags.begin(), d->tags.end(), dtkTagNumMoreThan);
}

void dtkTagCloud::clear(void)
{
    d->tags.clear();

    this->render();
}

void dtkTagCloud::render(void)
{
    if (d->averageFontSize <= 0)
        qDebug() << "AverageFontSize must be non-zero and non-negative.";

    if (d->fontSizeRange <= 0)
        qDebug() << "FontSizeRange must be non-zero and non-negative.";

    if (d->tags.isEmpty())
        return;

    d->mincount = 100000000;
    d->maxcount = 0;
    d->tagCount = 0;

    foreach (dtkTag tag, d->tags) {

        if (tag.count() < d->mincount)
            d->mincount = tag.count();

        if (tag.count() > d->maxcount)
            d->maxcount = tag.count();

        d->tagCount++;
    }

    dtkTagCloudHasher hasher(d->fontSizeRange, d->mincount, d->maxcount);

    int baseFontSize = d->averageFontSize - ((double)(d->fontSizeRange-1)/2);

    QString cloud; cloud.append(QString("<div align=\"justify\">\n"));

    foreach (dtkTag tag, d->tags) {

        int fontSize = baseFontSize + hasher.bucket(tag);

        QString color = "";

        if (!tag.color().isEmpty()) {
            color  = "color: ";
            color += (!tag.color().startsWith("#")) ? "#" : "";
            color += tag.color();
            color += ";";
        }

        QString count = QString::number(tag.count()) + " item" + ((tag.count() != 1) ? "s" : "");

        cloud.append(QString("<a href=\"tag://%1\" title=\"%2\" style=\"font-size: %4px; text-decoration: none; %5\" item=\"%3\">%1</a> ")
                     .arg(tag.text())
                     .arg(count)
                     .arg(tag.items().first())
                     .arg(fontSize)
                     .arg(color));
    }
    cloud.append("</div>\n");

    this->setHtml(cloud);
}

void dtkTagCloud::onLinkClicked(const QUrl& url)
{
    emit tagClicked(url.host());
}

// /////////////////////////////////////////////////////////////////
// dtkTagScopeTag
// /////////////////////////////////////////////////////////////////

class dtkTagScopeTag : public QPushButton
{
public:
    dtkTagScopeTag(QString tag) : QPushButton(tag) {}
};

// /////////////////////////////////////////////////////////////////
// dtkTagScope
// /////////////////////////////////////////////////////////////////

class dtkTagScopePrivate
{
public:
    QStringList filters;
    QLineEdit *edit;
    QToolButton *clear;

public:
    QList<dtkTagScopeTag *> tags;

public:
    dtkFlowLayout *layout;
};

dtkTagScope::dtkTagScope(QWidget *parent) : QFrame(parent)
{
    d = new dtkTagScopePrivate;

    // d->browser = new QTextBrowser(this);
    // d->browser->setFixedHeight(24);
    // d->browser->setFrameShape(QFrame::NoFrame);

    d->edit = new QLineEdit;
    d->edit->setFixedHeight(24);
    d->edit->setAttribute(Qt::WA_MacShowFocusRect, false);

    d->clear = new QToolButton;
    d->clear->setFixedHeight(24);
    d->clear->setAttribute(Qt::WA_MacShowFocusRect, false);

    QHBoxLayout *t_layout = new QHBoxLayout;
    t_layout->setContentsMargins(0, 0, 0, 0);
    t_layout->setSpacing(0);
    t_layout->addWidget(d->edit);
    t_layout->addWidget(d->clear);

    d->layout = new dtkFlowLayout;
    d->layout->setContentsMargins(0, 0, 0, 0);
    d->layout->setSpacing(0);

    // layout->addWidget(d->browser);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addLayout(t_layout);
    layout->addLayout(d->layout);

    this->setFrameShape(QFrame::NoFrame);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    // connect(d->browser, SIGNAL(anchorClicked(const QUrl&)), this, SLOT(onLinkClicked(const QUrl&)));

    connect(d->edit, SIGNAL(returnPressed()), this, SLOT(onTagAdded()));
    connect(d->clear, SIGNAL(clicked()), this, SIGNAL(cleared()));
}

dtkTagScope::~dtkTagScope(void)
{
    delete d->clear;
    delete d->edit;
    delete d;
}

QSize dtkTagScope::sizeHint(void) const
{
    return QSize(100, 24);
}

void dtkTagScope::clear(void)
{
    d->filters.clear();
}

void dtkTagScope::render(void)
{
    foreach(dtkTagScopeTag *tag, d->tags) {
        d->layout->removeWidget(tag);
    }

    qDeleteAll(d->tags); d->tags.clear();

    foreach(QString filter, d->filters) {
        dtkTagScopeTag *tag = new dtkTagScopeTag(filter);
        d->tags << tag;
        d->layout->addWidget(tag);

        connect(tag, SIGNAL(clicked()), this, SLOT(onTagRemoved()));
    }

    this->update();

    // QString scope = "";
    // scope += "<strong>scope</strong> : ";
    // foreach(QString filter, d->filters) {
    // scope += "  " + filter + " > ";
    // }

    // d->browser->setHtml(scope);
}

void dtkTagScope::addTag(QString tag)
{
    d->filters << tag;
}

void dtkTagScope::onTagAdded(void)
{
    QString tag = d->edit->text();

    emit tagAdded(tag);

    d->edit->clear();
}

void dtkTagScope::onTagRemoved(void)
{
    dtkTagScopeTag *tag = dynamic_cast<dtkTagScopeTag *>(sender());

    if(!tag)
        return;

    QString value = tag->text();

    emit tagRemoved(value);
}

// /////////////////////////////////////////////////////////////////
// dtkItem
// /////////////////////////////////////////////////////////////////

class dtkItemPrivate
{
public:
    QString name;
    QString description;
    QStringList tags;
    QStringList types;
};

dtkItem::dtkItem(QString name) : QListWidgetItem(name)
{
    d = new dtkItemPrivate;
    d->name = name;
    d->description = QString();
    d->tags = QStringList();
    d->types = QStringList();
}

dtkItem::dtkItem(QString name, QString description) : QListWidgetItem(name)
{
    d = new dtkItemPrivate;
    d->name = name;
    d->description = description;
    d->tags = QStringList();
    d->types = QStringList();
}

dtkItem::dtkItem(QString name, QString description, QStringList tags) : QListWidgetItem(name)
{
    d = new dtkItemPrivate;
    d->name = name;
    d->description = description;
    d->tags = tags;
    d->types = QStringList();
}

dtkItem::dtkItem(QString name, QString description, QStringList tags, QStringList types) : QListWidgetItem(name)
{
    d = new dtkItemPrivate;
    d->name = name;
    d->description = description;
    d->tags = tags;
    d->types = types;
}

dtkItem::dtkItem(const dtkItem& item) : QListWidgetItem(item.name())
{
    d = new dtkItemPrivate;
    d->name = item.d->name;
    d->description = item.d->description;
    d->tags = item.d->tags;
    d->types = item.d->types;
}

dtkItem::~dtkItem(void)
{
    delete d;

    d = NULL;
}

QString dtkItem::name(void) const
{
    return d->name;
}

QString dtkItem::description(void) const
{
    return d->description;
}

QStringList dtkItem::tags(void) const
{
    return d->tags;
}

QStringList dtkItem::types(void) const
{
    return d->types;
}

// /////////////////////////////////////////////////////////////////
// dtkItemList
// /////////////////////////////////////////////////////////////////

class dtkItemListPrivate
{
public:
    QList<dtkItem *> items;
};

dtkItemList::dtkItemList(QWidget *parent) : QListWidget(parent)
{
    d = new dtkItemListPrivate;
    
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameShape(QFrame::NoFrame);
    this->setDragEnabled(true);
    this->setItemDelegate(new dtkItemListDelegate(this));

    connect(this, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(onItemClicked(QListWidgetItem *)));
}

dtkItemList::~dtkItemList(void)
{
    delete d;
}

void dtkItemList::addItem(QString name)
{
    d->items << new dtkItem(name, QString(), QStringList());

    QListWidget::addItem(d->items.last());
}

void dtkItemList::addItem(QString name, QString description)
{
    d->items << new dtkItem(name, description, QStringList());

    QListWidget::addItem(d->items.last());
}

void dtkItemList::addItem(QString name, QString description, QStringList tags)
{
    d->items << new dtkItem(name, description, tags);

    QListWidget::addItem(d->items.last());
}

void dtkItemList::addItem(QString name, QString description, QStringList tags, QStringList types)
{
    d->items << new dtkItem(name, description, tags, types);

    QListWidget::addItem(d->items.last());
}

void dtkItemList::addItem(dtkItem item)
{
    d->items << new dtkItem(item);

    QListWidget::addItem(d->items.last());
}

void dtkItemList::clear(void)
{
    d->items.clear();

    QListWidget::clear();
}

void dtkItemList::onItemClicked(QListWidgetItem *item)
{
    dtkItem *i = dynamic_cast<dtkItem *>(item);

    if(!i)
        return;

    emit itemClicked(i->description());
}

// /////////////////////////////////////////////////////////////////
// dtkItemListDelegate
// /////////////////////////////////////////////////////////////////

dtkItemListDelegate::dtkItemListDelegate(dtkItemList *list) : QStyledItemDelegate(list)
{
    this->list = list;
}

void dtkItemListDelegate::paint(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    dtkItem *item = dynamic_cast<dtkItem *>(list->itemFromIndex(index));

    if(!item)
        return;

    painter->fillRect(option.rect, Qt::white);

    QRect name_rect = option.rect;
    name_rect.setHeight(15);

    painter->setPen(Qt::black);
    painter->drawText(name_rect, Qt::AlignLeft, item->name());

    QRect desc_rect = option.rect;
    desc_rect.translate(0, 15);
    desc_rect.setHeight(40);

    painter->setPen(Qt::gray);
    painter->drawText(desc_rect, Qt::AlignLeft, item->description());

    QRect tags_rect = option.rect;
    tags_rect.translate(0, 55);
    tags_rect.setHeight(15);

    painter->setPen(Qt::blue);
    painter->drawText(tags_rect, Qt::AlignLeft, item->tags().join(" "));

    painter->setPen(Qt::darkGray);
    painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
}

QSize dtkItemListDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    return QSize(100, 70);
}

// /////////////////////////////////////////////////////////////////
// dtkItemDesc
// /////////////////////////////////////////////////////////////////

class dtkItemDescPrivate
{
public:
    QString description;

public:
    QPushButton *back;
};

dtkItemDesc::dtkItemDesc(QWidget *parent) : QFrame(parent), d(new dtkItemDescPrivate)
{
    d->back = new QPushButton("Back");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch(1);
    layout->addWidget(d->back);

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameShape(QFrame::NoFrame);

    connect(d->back, SIGNAL(clicked()), this, SIGNAL(back()));
}

dtkItemDesc::~dtkItemDesc(void)
{
    delete d;

    d = NULL;
}

void dtkItemDesc::clear(void)
{
    d->description.clear();
}

void dtkItemDesc::setDescription(const QString& description)
{
    d->description = description;
}

// /////////////////////////////////////////////////////////////////
// dtkItemView
// /////////////////////////////////////////////////////////////////

class dtkItemViewPrivate
{
public:
    QWidget *parent;

public:    
    QEasingCurve::Type type;

public:
    bool vertical;
    bool wrap;
    bool active;

public:
    int speed;
    int now;
    int next;

public:
    QPoint pnow;

public:
    dtkItemList *list;
    dtkItemDesc *desc;
};

dtkItemView::dtkItemView(QWidget *parent) : QStackedWidget(parent), d(new dtkItemViewPrivate)
{
    d->list = new dtkItemList(this);
    d->desc = new dtkItemDesc(this);

    if (parent != 0)
        d->parent = parent;
    else
        d->parent = this;

    d->vertical = false;
    d->speed = 500;
    d->type = QEasingCurve::OutBack;
    d->now = 0;
    d->next = 0;
    d->wrap = false;
    d->pnow = QPoint(0,0);
    d->active = false;

    this->addWidget(d->list);
    this->addWidget(d->desc);

    connect(d->list, SIGNAL(itemClicked(const QString&)), this, SLOT(onItemClicked(const QString&)));
    connect(d->desc, SIGNAL(back()), this, SLOT(slideInPrev()));
}

dtkItemView::~dtkItemView(void)
{
    delete d;

    d = NULL;
}

dtkItemList *dtkItemView::list(void)
{
    return d->list;
}

dtkItemDesc *dtkItemView::desc(void)
{
    return d->desc;
}

void dtkItemView::onItemClicked(const QString& description)
{
    d->desc->setDescription(description);

    this->slideInNext();
}

void dtkItemView::setVerticalMode(bool vertical)
{
    d->vertical = vertical;
}

void dtkItemView::setSpeed(int speed)
{
    d->speed = speed;
}

void dtkItemView::setAnimation(QEasingCurve::Type type)
{
    d->type = type;
}

void dtkItemView::setWrap(bool wrap)
{
    d->wrap = wrap;
}

void dtkItemView::slideInNext(void)
{
    int now = currentIndex();
    if (d->wrap||(now<count()-1))
        slideInIdx(now+1);
}

void dtkItemView::slideInPrev(void)
{
    int now = currentIndex();
    if (d->wrap||(now>0))
        slideInIdx(now-1);
}

void dtkItemView::slideInIdx(int idx, Direction direction)
{
    if (idx>count()-1) {
        direction = d->vertical ? Top2Bottom : Right2Left;
        idx = (idx)%count();
    } else if (idx<0) {
        direction =  d->vertical ? Bottom2Top: Left2Right;
        idx = (idx+count())%count();
    }
    slideInWgt(widget ( idx ),direction);
}

void dtkItemView::slideInWgt(QWidget *newwidget, Direction direction)
{
    if (d->active)
        return;
    else
        d->active = true;

    Direction directionhint;
    int now = currentIndex();
    int next = indexOf(newwidget);
    if (now==next) {
        d->active = false;
        return;
    }
    else if (now<next){
        directionhint = d->vertical ? Top2Bottom : Right2Left;
    }
    else {
        directionhint = d->vertical ? Bottom2Top : Left2Right;
    }
    if (direction == Automatic) {
        direction = directionhint;
    }
    
    int offsetx = frameRect().width();
    int offsety = frameRect().height();
    
    widget(next)->setGeometry ( 0,  0, offsetx, offsety );
    
    if (direction==Bottom2Top)  {
        offsetx = 0;
        offsety = -offsety;
    }
    else if (direction==Top2Bottom) {
        offsetx = 0;
    }
    else if (direction==Right2Left) {
        offsetx = -offsetx;
        offsety = 0;
    }
    else if (direction==Left2Right) {
        offsety = 0;
    }

    QPoint pnext = widget(next)->pos();
    QPoint pnow = widget(now)->pos();
    d->pnow = pnow;
    
    widget(next)->move(pnext.x()-offsetx,pnext.y()-offsety);
    widget(next)->show();
    widget(next)->raise();
    
    QPropertyAnimation *animnow = new QPropertyAnimation(widget(now), "pos");    
    animnow->setDuration(d->speed);
    animnow->setEasingCurve(d->type);
    animnow->setStartValue(QPoint(pnow.x(), pnow.y()));
    animnow->setEndValue(QPoint(offsetx+pnow.x(), offsety+pnow.y()));

    QPropertyAnimation *animnext = new QPropertyAnimation(widget(next), "pos");
    animnext->setDuration(d->speed);
    animnext->setEasingCurve(d->type);
    animnext->setStartValue(QPoint(-offsetx+pnext.x(), offsety+pnext.y()));
    animnext->setEndValue(QPoint(pnext.x(), pnext.y()));
    
    QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;
    animgroup->addAnimation(animnow);
    animgroup->addAnimation(animnext);
    
    QObject::connect(animgroup, SIGNAL(finished()),this,SLOT(animationDoneSlot()));

    d->next = next;
    d->now = now;
    d->active = true;

    animgroup->start();
}

void dtkItemView::animationDoneSlot(void)
{
    setCurrentIndex(d->next);

    widget(d->now)->hide();
    widget(d->now)->move(d->pnow);

    d->active = false;

    emit animationFinished();
}

// /////////////////////////////////////////////////////////////////
// dtkTagController
// /////////////////////////////////////////////////////////////////

class dtkTagControllerPrivate
{
public:
    dtkItemList *list;
    dtkTagCloud *cloud;
    dtkTagScope *scope;

    QList<dtkTag>  tags;
    QList<dtkItem> items;
    QStringList    filters;
};

dtkTagController::dtkTagController(void) : QObject()
{
    d = new dtkTagControllerPrivate;
    d->list = NULL;
    d->cloud = NULL;
    d->scope = NULL;
}

dtkTagController::~dtkTagController(void)
{
    delete d;

    d = NULL;
}

void dtkTagController::attach(dtkItemView *view)
{
    d->list = view->list();

    // connect(d->list, SIGNAL(tagClicked(QString)), this, SLOT(setFilter(QString)));
}

void dtkTagController::attach(dtkTagCloud *cloud)
{
    d->cloud = cloud;

    connect(d->cloud, SIGNAL(tagClicked(QString)), this, SLOT(addFilter(QString)));
}

void dtkTagController::attach(dtkTagScope *scope)
{
    d->scope = scope;

    connect(d->scope, SIGNAL(tagSet(QString)),   this, SLOT(setFilter(QString)));
    connect(d->scope, SIGNAL(tagAdded(QString)), this, SLOT(addFilter(QString)));
    connect(d->scope, SIGNAL(tagRemoved(QString)), this, SLOT(remFilter(QString)));
    connect(d->scope, SIGNAL(cleared(void)), this, SLOT(clear()));
}

void dtkTagController::addItem(QString name)
{
    d->items << dtkItem(name, "", QStringList());

    this->update();
    this->render();
}

void dtkTagController::addItem(QString name, QString description)
{
    d->items << dtkItem(name, description, QStringList());

    this->update();
    this->render();
}

void dtkTagController::addItem(QString name, QString description, QStringList tags)
{
    d->items << dtkItem(name, description, tags);

    this->update();
    this->render();
}

void dtkTagController::addItem(QString name, QString description, QStringList tags, QStringList types)
{
    d->items << dtkItem(name, description, tags, types);

    this->update();
    this->render();
}

void dtkTagController::update(void)
{
    d->tags.clear();

    QHash<QString, QStringList> tags;
    
    foreach(dtkItem item, d->items)
        foreach(QString tag, item.tags())
            tags[tag] << item.name();

    foreach(QString tag, tags.keys())
        d->tags << dtkTag(tag, tags[tag].count(), tags[tag]);
}

static bool filter(QStringList l1, QStringList l2) {
    bool pass = true;
    foreach(QString s, l1) if(!l2.contains(s)) pass = false;
    return pass;
}

void dtkTagController::clear(void)
{
    d->filters.clear();
    
    this->render();
}

void dtkTagController::render(void)
{
    if (d->list) {
        d->list->clear();
        foreach(dtkItem item, d->items)
            if(filter(d->filters, item.tags()))
                d->list->addItem(item);
    }

    if (d->cloud) {
        d->cloud->clear();
        foreach(dtkTag tag, d->tags)
            d->cloud->addTag(tag);
        d->cloud->render();
    }

    if (d->scope) {
        d->scope->clear();
        foreach(QString filter, d->filters)
            d->scope->addTag(filter);
        d->scope->render();
    }
}

void dtkTagController::addFilter(QString filter)
{
    d->filters << filter;

    this->render();
}

void dtkTagController::setFilter(QString filter)
{
    d->filters.clear();
    d->filters << filter;

    this->render();
}

void dtkTagController::remFilter(QString filter)
{
    d->filters.removeOne(filter);

    this->render();
}
