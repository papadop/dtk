/* dtkComposerNodeNumber.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Feb 25 16:21:13 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar  1 19:00:54 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 156
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeNumber.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberLabel
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberLabel : public QGraphicsItem
{
public:
     dtkComposerNodeNumberLabel(dtkComposerNodeNumber *parent);
    ~dtkComposerNodeNumberLabel(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    dtkComposerNodeNumber *parent_node;
    QPainterPath path;
    QString text;
    bool expanded;
};

dtkComposerNodeNumberLabel::dtkComposerNodeNumberLabel(dtkComposerNodeNumber *parent) : QGraphicsItem(parent)
{
    int margin = 10;
    int length = 77;
    int height = 15;
    int radius =  5;
    int origin_x = parent->boundingRect().width() / 2 - length - margin;
    int origin_y = -parent->boundingRect().height() / 2;

    QPainterPath b; b.addRoundedRect(origin_x,              origin_y, margin,          height,     radius, radius);
    QPainterPath c; c.addRoundedRect(origin_x + margin,     origin_y, length - margin, height,     radius, radius);
    QPainterPath d; d.addRoundedRect(origin_x + length,     origin_y, margin,          height,     radius, radius);
    QPainterPath e; e.addRoundedRect(origin_x + margin / 2, origin_y, length,          height / 2,      0,      0);

    path = c.united(e.subtracted(b.united(c.united(d))));

    parent_node = parent;

    text = "INT";

    expanded = false;
}

dtkComposerNodeNumberLabel::~dtkComposerNodeNumberLabel(void)
{

}

QRectF dtkComposerNodeNumberLabel::boundingRect(void) const
{
    return path.boundingRect();
}

void dtkComposerNodeNumberLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QLinearGradient gradient(option->rect.left(), option->rect.top(), option->rect.left(), option->rect.bottom());
    gradient.setColorAt(0.0, QColor("#bbbbbb"));
    gradient.setColorAt(0.3, QColor("#333333"));
    gradient.setColorAt(1.0, QColor("#222222"));

    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(gradient);
    painter->drawPath(path);
    
#if defined(Q_WS_MAC)
    QFont font("Lucida Grande", 11);
#else
    QFont font("Lucida Grande", 9);
#endif
    font.setBold(true);

    QFontMetrics metrics(font);
    
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(this->boundingRect(), Qt::AlignCenter, text);
}

void dtkComposerNodeNumberLabel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);    

    if (text == "INT") {

        text = "UINT";
        parent_node->setGenre(dtkComposerNodeNumber::UInt);
        parent_node->setValue(parent_node->number().toUInt());

    } else if (text == "UINT") {

        text = "LONG";
        parent_node->setGenre(dtkComposerNodeNumber::Long);
        parent_node->setValue(parent_node->number().value<long>());

    } else if (text == "LONG") {

        text = "ULONG";
        parent_node->setGenre(dtkComposerNodeNumber::ULong);
        parent_node->setValue(parent_node->number().value<ulong>());

    } else if (text == "ULONG") {

        text = "LLONG";
        parent_node->setGenre(dtkComposerNodeNumber::LongLong);
        parent_node->setValue(parent_node->number().toLongLong());

    } else if (text == "LLONG") {

        text = "ULLONG";
        parent_node->setGenre(dtkComposerNodeNumber::ULongLong);
        parent_node->setValue(parent_node->number().toULongLong());

    } else if (text == "ULLONG") {

        text = "FLOAT";
        parent_node->setGenre(dtkComposerNodeNumber::Float);
        parent_node->setValue(parent_node->number().value<float>());

    } else if (text == "FLOAT") {

        text = "DOUBLE";
        parent_node->setGenre(dtkComposerNodeNumber::Double);
        parent_node->setValue(parent_node->number().toDouble());

    } else if (text == "DOUBLE") {

        text = "INT";
        parent_node->setGenre(dtkComposerNodeNumber::Int);
        parent_node->setValue(parent_node->number().toInt());

    }

    this->update();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberButton
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberButton : public QGraphicsItem
{
public:
     dtkComposerNodeNumberButton(dtkComposerNodeNumber *parent);
    ~dtkComposerNodeNumberButton(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    dtkComposerNodeNumber *parent_node;
    QPainterPath path;
    QString text;
    bool expanded;
};

dtkComposerNodeNumberButton::dtkComposerNodeNumberButton(dtkComposerNodeNumber *parent) : QGraphicsItem(parent)
{
    int margin = 10;
    int length = 30;
    int height = 10;
    int radius =  5;
    int origin_x = -(length + margin) / 2;
    int origin_y = parent->boundingRect().height() / 2;

    QPainterPath b; b.addRoundedRect(origin_x,              origin_y, margin,          -height,     radius, radius);
    QPainterPath c; c.addRoundedRect(origin_x + margin,     origin_y, length - margin, -height,     radius, radius);
    QPainterPath d; d.addRoundedRect(origin_x + length,     origin_y, margin,          -height,     radius, radius);
    QPainterPath e; e.addRoundedRect(origin_x + margin / 2, origin_y, length,          -height / 2,      0,      0);

    path = c.united(e.subtracted(b.united(c.united(d))));

    parent_node = parent;
    
    text = "+";

    expanded = false;
}

dtkComposerNodeNumberButton::~dtkComposerNodeNumberButton(void)
{

}

QRectF dtkComposerNodeNumberButton::boundingRect(void) const
{
    return path.boundingRect();
}

void dtkComposerNodeNumberButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QLinearGradient gradient(option->rect.left(), option->rect.top(), option->rect.left(), option->rect.bottom());
    gradient.setColorAt(0.0, QColor("#bbbbbb"));
    gradient.setColorAt(0.3, QColor("#333333"));
    gradient.setColorAt(1.0, QColor("#222222"));

    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(gradient);
    painter->drawPath(path);
    
#if defined(Q_WS_MAC)
    QFont font("Lucida Grande", 8);
#else
    QFont font("Lucida Grande", 6);
#endif
    font.setBold(true);

    QFontMetrics metrics(font);
    
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(this->boundingRect(), Qt::AlignCenter, text);
}

void dtkComposerNodeNumberButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    if(!this->expanded) {
        parent_node->expand();
        text = "-";
    } else {
        parent_node->collapse();
        text = "+";
    }

    this->expanded = !this->expanded;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberEditor
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberEditor : public QGraphicsTextItem
{
public:
    dtkComposerNodeNumberEditor(dtkComposerNodeNumber *parent);

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    dtkComposerNodeNumber *parent_node;
};

dtkComposerNodeNumberEditor::dtkComposerNodeNumberEditor(dtkComposerNodeNumber *parent) : QGraphicsTextItem(parent)
{
#if defined(Q_WS_MAC)
    QFont font("Lucida Grande", 10);
#else
    QFont font("Lucida Grande", 8);
#endif

    this->setDefaultTextColor(Qt::lightGray);
    this->setFont(font);
    this->setTextInteractionFlags(Qt::TextEditorInteraction);
    this->setFlag(QGraphicsItem::ItemStacksBehindParent, true);

    this->parent_node = parent;
}

void dtkComposerNodeNumberEditor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath s_rect; s_rect.addRect(QRectF(option->rect.topLeft(), QSizeF(option->rect.width(), option->rect.height() / 2)));
    QPainterPath r_rect; r_rect.addRoundedRect(option->rect, 5, 5);
    QPainterPath path = s_rect.united(r_rect);

    painter->save();
    painter->setPen(Qt::darkGray);
    painter->setBrush(Qt::black);
    painter->drawPath(path);
    painter->restore();

    QStyleOptionGraphicsItem *o = const_cast<QStyleOptionGraphicsItem*>(option);
    o->state &= ~QStyle::State_Selected;
    o->state &= ~QStyle::State_HasFocus;

    QGraphicsTextItem::paint(painter, option, widget);
}

void dtkComposerNodeNumberEditor::keyPressEvent(QKeyEvent *event)
{
    QGraphicsTextItem::keyPressEvent(event);    

    switch (this->parent_node->genre()) {

    case (dtkComposerNodeNumber::Int):
        this->parent_node->setGenre(dtkComposerNodeNumber::Int);
        this->parent_node->setValue(this->toPlainText().toInt());
        break;
        
    case (dtkComposerNodeNumber::UInt):
        this->parent_node->setGenre(dtkComposerNodeNumber::UInt);
        this->parent_node->setValue(this->toPlainText().toUInt());
        break;

    case (dtkComposerNodeNumber::Long):
        this->parent_node->setGenre(dtkComposerNodeNumber::Long);
        this->parent_node->setValue(this->toPlainText().toLong());
        break;

    case (dtkComposerNodeNumber::ULong):
        this->parent_node->setGenre(dtkComposerNodeNumber::ULong);
        this->parent_node->setValue(this->toPlainText().toULong());
        break;

    case (dtkComposerNodeNumber::LongLong):
        this->parent_node->setGenre(dtkComposerNodeNumber::LongLong);
        this->parent_node->setValue(this->toPlainText().toLongLong());
        break;

    case (dtkComposerNodeNumber::ULongLong):
        this->parent_node->setGenre(dtkComposerNodeNumber::ULongLong);
        this->parent_node->setValue(this->toPlainText().toULongLong());
        break;

    case (dtkComposerNodeNumber::Float):
        this->parent_node->setGenre(dtkComposerNodeNumber::Float);
        this->parent_node->setValue(this->toPlainText().toFloat());
        break;

    case (dtkComposerNodeNumber::Double):
        this->parent_node->setGenre(dtkComposerNodeNumber::Double);
        this->parent_node->setValue(this->toPlainText().toDouble());
        break;

    default:
        this->parent_node->setGenre(dtkComposerNodeNumber::Int);
        this->parent_node->setValue(this->toPlainText().toInt());
        break;
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberPrivate
{
public:
    dtkComposerNodeProperty *property_input_value;
    dtkComposerNodeProperty *property_output_value;

public:
    dtkComposerNodeNumberLabel *label;
    dtkComposerNodeNumberButton *button;
    dtkComposerNodeNumberEditor *editor;

public:
    QPropertyAnimation *animation;

public:
    dtkComposerNodeNumber::Genre genre;

    QVariant value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumber
// /////////////////////////////////////////////////////////////////

dtkComposerNodeNumber::dtkComposerNodeNumber(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeNumberPrivate)
{
    d->property_input_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);
    d->property_output_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, this);

    d->label = new dtkComposerNodeNumberLabel(this);
    d->label->setPos(0, 0);

    d->button = new dtkComposerNodeNumberButton(this);
    d->button->setPos(0, 0);
    
    d->genre = dtkComposerNodeNumber::Int;
    d->value = QVariant((int)0);

    this->setTitle("Number");
    this->setKind(dtkComposerNode::Atomic);
    this->setType("dtkComposerNumber");

    this->addInputProperty(d->property_input_value);
    this->addOutputProperty(d->property_output_value);

    // --
    
    d->editor = new dtkComposerNodeNumberEditor(this);
    d->editor->setPos(-d->editor->boundingRect().width() / 2, 0);
    d->editor->setTextWidth(0.8 * this->boundingRect().width());
    d->editor->hide();

    // --

    d->animation = new QPropertyAnimation(d->editor, "pos");
    d->animation->setDuration(500);
    d->animation->setStartValue(QPointF(-d->editor->boundingRect().width()/2, 0));
    d->animation->setEndValue(QPointF(-d->editor->boundingRect().width()/2, 0.85 * d->editor->boundingRect().height()));
    d->animation->setEasingCurve(QEasingCurve::OutBounce);
}

dtkComposerNodeNumber::~dtkComposerNodeNumber(void)
{
    delete d;

    d = NULL;
}

QVariant dtkComposerNodeNumber::value(dtkComposerNodeProperty *property)
{
    if(property == d->property_output_value)
        return d->value;
}

dtkComposerNodeNumber::Genre dtkComposerNodeNumber::genre(void)
{
    return d->genre;
}

QVariant dtkComposerNodeNumber::number(void)
{
    return d->value;
}

void dtkComposerNodeNumber::setGenre(dtkComposerNodeNumber::Genre genre)
{
    d->genre = genre;
}

bool dtkComposerNodeNumber::setNumber(QVariant number)
{
    switch (number.userType()) {

    case (dtkComposerNodeNumber::Int):
        d->label->text = "INT";
        this->setGenre(dtkComposerNodeNumber::Int);
        this->setValue(number.toInt());
        d->editor->setPlainText(QString("%1").arg(number.toInt()));
        break;

    case (dtkComposerNodeNumber::UInt):
        d->label->text = "UINT";
        this->setGenre(dtkComposerNodeNumber::UInt);
        this->setValue(number.toUInt());
        d->editor->setPlainText(QString("%1").arg(number.toUInt()));
        break;

    case (dtkComposerNodeNumber::Long):
        d->label->text = "LONG";
        this->setGenre(dtkComposerNodeNumber::Long);
        this->setValue(number.value<long>());
        d->editor->setPlainText(QString("%1").arg(number.value<long>()));
        break;

    case (dtkComposerNodeNumber::ULong):
        d->label->text = "ULONG";
        this->setGenre(dtkComposerNodeNumber::ULong);
        this->setValue(number.value<ulong>());
        d->editor->setPlainText(QString("%1").arg(number.value<ulong>()));
        break;

    case (dtkComposerNodeNumber::LongLong):
        d->label->text = "LLONG";
        this->setGenre(dtkComposerNodeNumber::LongLong);
        this->setValue(number.toLongLong());
        d->editor->setPlainText(QString("%1").arg(number.toLongLong()));
        break;

    case (dtkComposerNodeNumber::ULongLong):
        d->label->text = "ULLONG";
        this->setGenre(dtkComposerNodeNumber::ULongLong);
        this->setValue(number.toULongLong());
        d->editor->setPlainText(QString("%1").arg(number.toULongLong()));
        break;

    case (dtkComposerNodeNumber::Float):
        d->label->text = "FLOAT";
        this->setGenre(dtkComposerNodeNumber::Float);
        this->setValue(number.value<float>());
        d->editor->setPlainText(QString("%1").arg(number.value<float>()));
        break;

    case (dtkComposerNodeNumber::Double):
        d->label->text = "DOUBLE";
        this->setGenre(dtkComposerNodeNumber::Double);
        this->setValue(number.toDouble());
        d->editor->setPlainText(QString("%1").arg(number.toDouble()));
        break;
          
    default:
        this->setGenre(dtkComposerNodeNumber::Invalid);
        d->value.clear();
        qDebug() << DTK_PRETTY_FUNCTION << "Invalid Variant type" << number.type();
        return false;
        break;
    }

    d->editor->update();

    return true;
}

void dtkComposerNodeNumber::setValue(int value)
{
    if(d->genre != dtkComposerNodeNumber::Int) {
        qDebug() << "The input value genre does not match with the expected INT genre.";
        return;
    }
    d->value = QVariant(value);
}

void dtkComposerNodeNumber::setValue(uint value)
{
    if(d->genre != dtkComposerNodeNumber::UInt) {
        qDebug() << "The input value genre does not match with the expected UNSIGNED INT genre.";
        return;
    }
    d->value = QVariant(value);
}

void dtkComposerNodeNumber::setValue(long value)
{
    if(d->genre != dtkComposerNodeNumber::Long) {
        qDebug() << "The input value genre does not match with the expected LONG genre.";
        return;
    }
    d->value = qVariantFromValue(value);
}

void dtkComposerNodeNumber::setValue(ulong value)
{
    if(d->genre != dtkComposerNodeNumber::ULong) {
        qDebug() << "The input value genre does not match with the expected UNSIGNED LONG genre.";
        return;
    }
    d->value = qVariantFromValue(value);
}

void dtkComposerNodeNumber::setValue(qlonglong value)
{
    if(d->genre != dtkComposerNodeNumber::LongLong) {
        qDebug() << "The input value genre does not match with the expected LONG LONG genre.";
        return;
    }
    d->value = QVariant(value);
}

void dtkComposerNodeNumber::setValue(qulonglong value)
{
    if(d->genre != dtkComposerNodeNumber::ULongLong) {
        qDebug() << "The input value genre does not match with the expected UNSIGNED LONG LONG genre.";
        return;
    }
    d->value = QVariant(value);
}

void dtkComposerNodeNumber::setValue(float value)
{
    if(d->genre != dtkComposerNodeNumber::Float) {
        qDebug() << "The input value genre does not match with the expected FLOAT genre.";
        return;
    }
    d->value = qVariantFromValue(value);
}

void dtkComposerNodeNumber::setValue(double value)
{
    if(d->genre != dtkComposerNodeNumber::Double) {
        qDebug() << "The input value genre does not match with the expected DOUBLE genre.";
        return;
    }
    d->value = QVariant(value);
}

void dtkComposerNodeNumber::expand(void)
{
    d->editor->show();
    d->animation->setDirection(QAbstractAnimation::Forward);
    d->animation->start();
}

void dtkComposerNodeNumber::collapse(void)
{
    d->animation->setDirection(QAbstractAnimation::Backward);
    d->animation->start();

    connect(d->animation, SIGNAL(finished()), this, SLOT(onCollapseFinised()));
}

void dtkComposerNodeNumber::onCollapseFinised(void)
{
    d->editor->hide();

    disconnect(d->animation, SIGNAL(finished()), this, SLOT(onCollapseFinised()));    
}

void dtkComposerNodeNumber::onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    if (property == d->property_input_value) {

        QVariant number = edge->source()->node()->value(edge->source());

        if (!this->setNumber(number)) {
            qDebug() << DTK_PRETTY_FUNCTION << "Input number has an invalid genre.";
            return;
        }
    }
    return;
}

void dtkComposerNodeNumber::onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);
}

void dtkComposerNodeNumber::run(void)
{

}

dtkComposerNodeNumber::Genre dtkComposerNodeNumber::genre(QVariant& a, QVariant& b)
{
    if (a.userType() == dtkComposerNodeNumber::Invalid || b.userType() == dtkComposerNodeNumber::Invalid) {

        return dtkComposerNodeNumber::Invalid;

    } else if (a.userType() == dtkComposerNodeNumber::Double || b.userType() == dtkComposerNodeNumber::Double) {

        return dtkComposerNodeNumber::Double;

    } else if (a.userType() == dtkComposerNodeNumber::Float || b.userType() == dtkComposerNodeNumber::Float) {

        return dtkComposerNodeNumber::Float;

    } else if (a.userType() == dtkComposerNodeNumber::ULongLong) {

        if (b.userType() == dtkComposerNodeNumber::ULongLong || b.userType() == dtkComposerNodeNumber::ULong || b.userType() == dtkComposerNodeNumber::UInt)
            return dtkComposerNodeNumber::ULongLong;
        else
            return dtkComposerNodeNumber::Invalid;

    } else if (b.userType() == dtkComposerNodeNumber::ULongLong) {

        if (a.userType() == dtkComposerNodeNumber::ULong || a.userType() == dtkComposerNodeNumber::UInt)
            return dtkComposerNodeNumber::ULongLong;
        else
            return dtkComposerNodeNumber::Invalid;

    } else if (a.userType() == dtkComposerNodeNumber::ULong) {

        if (b.userType() == dtkComposerNodeNumber::ULong || b.userType() == dtkComposerNodeNumber::UInt)
            return dtkComposerNodeNumber::ULong;
        else
            return dtkComposerNodeNumber::Invalid;

    } else if (b.userType() == dtkComposerNodeNumber::ULong) {

        if (a.userType() == dtkComposerNodeNumber::UInt)
            return dtkComposerNodeNumber::ULong;
        else
            return dtkComposerNodeNumber::Invalid;

    } else if (a.userType() == dtkComposerNodeNumber::UInt) {

        if (b.userType() == dtkComposerNodeNumber::UInt)
            return dtkComposerNodeNumber::UInt;
        else
            return dtkComposerNodeNumber::Invalid;

    } else if (a.userType() == dtkComposerNodeNumber::LongLong || b.userType() == dtkComposerNodeNumber::LongLong) {

        return dtkComposerNodeNumber::LongLong;

    } else if (a.userType() == dtkComposerNodeNumber::Long || b.userType() == dtkComposerNodeNumber::Long) {

        return dtkComposerNodeNumber::Long;

    } else if (a.userType() == dtkComposerNodeNumber::Int || b.userType() == dtkComposerNodeNumber::Int) {

        return dtkComposerNodeNumber::Int;

    }

    return dtkComposerNodeNumber::Invalid;
}
