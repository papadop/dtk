// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

namespace dtkMetaContainerSequentialPrivate
{
// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialPrivate::itemOperator implementation
// /////////////////////////////////////////////////////////////////

template <typename I, typename T> inline void itemOperatorBase<I, T>::addValue(I&, const T *) 
{
    qWarning("Operator += NOT implemented for type: %s", QMetaType::typeName(qMetaTypeId<T>()));
}

template <typename I, typename T> inline void itemOperatorBase<I, T>::subValue(I&, const T *) 
{
    qWarning("Operator -= NOT implemented for type: %s", QMetaType::typeName(qMetaTypeId<T>()));
}

template <typename I, typename T> inline void itemOperatorBase<I, T>::mulValue(I&, const T *) 
{
    qWarning("Operator *= NOT implemented for type: %s", QMetaType::typeName(qMetaTypeId<T>()));
}

template <typename I, typename T> inline void itemOperatorBase<I, T>::divValue(I&, const T *) 
{
    qWarning("Operator /= NOT implemented for type: %s", QMetaType::typeName(qMetaTypeId<T>()));
}

template <typename I, typename T> inline bool itemOperatorBase<I, T>::isEqual(const I&, const T *) 
{
    qWarning("Comparison is NOT implemented for type: %s", QMetaType::typeName(qMetaTypeId<T>()));
    return false;
}

template <typename I> inline void itemOperator<I, QString, false>::addValue(I& it, const QString *value) 
{
    *it += *value;
}

template <typename I> inline bool itemOperator<I, QString, false>::isEqual(const I& it, const QString *value) 
{
    return (*it == *value);
}

template <typename I, typename T> inline void itemOperator<I, T, true>::addValue(I& it, const T *value) 
{
    *it += *value;
}

template <typename I, typename T> inline void itemOperator<I, T, true>::subValue(I& it, const T *value) 
{
    *it -= *value;
}

template <typename I, typename T> inline void itemOperator<I, T, true>::mulValue(I& it, const T *value) 
{
    *it *= *value;
}

template <typename I, typename T> inline void itemOperator<I, T, true>::divValue(I& it, const T *value) 
{
    *it /= *value;
}

template <typename I, typename T> inline bool itemOperator<I, T, true>::isEqual(const I& it, const T *value) 
{
    return (*it == *value);
}


// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialPrivate::iterator implementation
// /////////////////////////////////////////////////////////////////

template<typename I, typename V> inline void iteratorOwner<I, V>::assign(void *& ptr, const I& it)
{
    ptr = new I(it);
}

template<typename I, typename V> inline void iteratorOwner<I, V>::assign(void *& ptr, void *const& src)
{
    ptr = new I(*static_cast<I *>(src));
}
    
template<typename I, typename V> inline void iteratorOwner<I, V>::advance(void *& it, int step)
{
    I& ite = *static_cast<I *>(it);
    std::advance(ite, step);
}

template<typename I, typename V> inline const void *iteratorOwner<I, V>::data(void *const & it)
{
    return &**static_cast<I *>(it);
}

template<typename I, typename V> inline const void *iteratorOwner<I, V>::data(I& it)
{
    return &*it;
}

template<typename I, typename V> inline void iteratorOwner<I, V>::destroy(void *& it)
{
    delete static_cast<I *>(it);
}

template<typename I, typename V> inline int iteratorOwner<I, V>::distance(I& from, void *const& to)
{
    return std::distance(from, *(static_cast<I *>(to)));
}

template<typename I, typename V> inline bool iteratorOwner<I, V>::equal(void *it, void *other)
{
    return *static_cast<I *>(it) == *static_cast<I *>(other);
}

template<typename I, typename V> inline void iteratorOwner<I, V>::setData(void *it, const void *value)
{
    **static_cast<I *>(it) = *static_cast<const V *>(value);
}

template<typename I, typename V> inline void iteratorOwner<I, V>::setData(I& it, const void *value)
{
    *it = *static_cast<const V *>(value);
}

template<typename I, typename V> inline void iteratorOwner<I, V>::add(void *it, const void *value)
{
    itemOperator<I, V>::addValue(*static_cast<I *>(it), static_cast<const V *>(value));
}

template<typename I, typename V> inline void iteratorOwner<I, V>::sub(void *it, const void *value)
{
    itemOperator<I, V>::subValue(*static_cast<I *>(it), static_cast<const V *>(value));
}

template<typename I, typename V> inline void iteratorOwner<I, V>::mul(void *it, const void *value)
{
    itemOperator<I, V>::mulValue(*static_cast<I *>(it), static_cast<const V *>(value));
}

template<typename I, typename V> inline void iteratorOwner<I, V>::div(void *it, const void *value)
{
    itemOperator<I, V>::divValue(*static_cast<I *>(it), static_cast<const V *>(value));
}

template<typename I, typename V> inline bool iteratorOwner<I, V>::isEqual(void *it, const void *value)
{
    return itemOperator<I, V>::isEqual(*static_cast<I *>(it), static_cast<const V *>(value));
}

// /////////////////////////////////////////////////////////////////

template<typename V> inline void iteratorOwner<V *, V>::assign(void *& ptr, V *const it)
{
    ptr = const_cast<V *>(it);
}

template<typename V> inline void iteratorOwner<V *, V>::assign(void *& ptr, void *const& src)
{
    ptr = static_cast<V *>(src);
}
    
template<typename V> inline void iteratorOwner<V *, V>::advance(void *& it, int step)
{
    V * ite = static_cast<V *>(it);
    std::advance(ite, step);
    it = ite;
}

template<typename V> inline const void *iteratorOwner<V *, V>::data(void *const& it)
{
    return it;
}

template<typename V> inline const void *iteratorOwner<V *, V>::data(V *it)
{
    return it;
}

template<typename V> inline void iteratorOwner<V *, V>::destroy(void *&)
{
    
}

template<typename V> inline int iteratorOwner<V *, V>::distance(V *from, void *const& to)
{
    return std::distance(from, (static_cast<V *>(to)));
}

template<typename V> inline bool iteratorOwner<V *, V>::equal(void *it, void *other)
{
    return static_cast<V *>(it) == static_cast<V *>(other);
}

template<typename V> inline void iteratorOwner<V *, V>::setData(void *it, const void *value)
{
    *static_cast<V *>(it) = *static_cast<const V *>(value);
}

template<typename V> inline void iteratorOwner<V *, V>::setData(V *it, const void *value)
{
    *it = *static_cast<const V *>(value);
}

template<typename V> inline void iteratorOwner<V *, V>::add(void *it, const void *value)
{
    V *item = static_cast<V *>(it);
    itemOperator<V*, V>::addValue(item, static_cast<const V *>(value));
}

template<typename V> inline void iteratorOwner<V *, V>::sub(void *it, const void *value)
{
    V *item = static_cast<V *>(it);
    itemOperator<V*, V>::subValue(item, static_cast<const V *>(value));
}

template<typename V> inline void iteratorOwner<V *, V>::mul(void *it, const void *value)
{
    V *item = static_cast<V *>(it);
    itemOperator<V*, V>::mulValue(item, static_cast<const V *>(value));
}

template<typename V> inline void iteratorOwner<V *, V>::div(void *it, const void *value)
{
    V *item = static_cast<V *>(it);
    itemOperator<V*, V>::divValue(item, static_cast<const V *>(value));
}

template<typename V> inline bool iteratorOwner<V *, V>::isEqual(void *it, const void *value)
{
    V *item = static_cast<V *>(it);
    return itemOperator<V*, V>::isEqual(item, static_cast<const V *>(value));
}

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialPrivate::containerAPI implementation
// /////////////////////////////////////////////////////////////////

template<typename T> inline void containerAPIBase<T>::clear(T *c)
{
    c->clear();
}
    
template<typename T> inline void containerAPIBase<T>::reserve(T *c, int size)
{
    c->reserve(size);
}
    
template<typename T> inline void containerAPIBase<T>::resize(T *c, int size)
{
    c->resize(size);
}

template<typename T> inline bool containerAPIBase<T>::empty(const T *c)
{
    return c->empty();
}

template<typename T> inline int containerAPIBase<T>::size(const T *c)
{
    return c->size();
}

template<typename T> inline void containerAPIBase<T>::insertData(T *c, int idx, const void *value)
{
    typename T::iterator it(c->begin());
    std::advance(it, idx);    
    c->insert(it, *static_cast<const typename T::value_type *>(value));
}

template<typename T> inline void containerAPIBase<T>::removeData(T *c, int idx)
{
    typename T::iterator it(c->begin());
    std::advance(it, idx);    
    c->erase(it);
}
    
template<typename T> inline void containerAPI<std::list<T> >::reserve(std::list<T> *, int)
{
    qWarning("Current meta container is based on std::list which does not provide reserve method. Nothing is done.");
}
    
template<typename T> inline void containerAPI<QList<T> >::resize(QList<T> *, int)
{
    qWarning("Current meta container is based on QList which does not provide resize method. Nothing is done.");
}

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialPrivate::handler template method implementation
// /////////////////////////////////////////////////////////////////

template<typename T> inline void handler::clearPrivate(void *c)
{
    containerAPI<T>::clear(static_cast<T *>(c));
}

template<typename T> inline void handler::reservePrivate(void *c, int size)
{
    containerAPI<T>::reserve(static_cast<T *>(c), size);
}

template<typename T> inline void handler::resizePrivate(void *c, int size)
{
    containerAPI<T>::resize(static_cast<T *>(c), size);
}

template<typename T> inline bool handler::emptyPrivate(void *c)
{
    return containerAPI<T>::empty(static_cast<T *>(c));
}

template<typename T> inline int handler::sizePrivate(void *c)
{
    return containerAPI<T>::size(static_cast<T *>(c));
}

template<typename T> inline void handler::setAtPrivate(void *c, int idx, const void *val)
{
    typename T::iterator it = static_cast<T *>(c)->begin();
    std::advance(it, idx);
    iteratorOwner<typename T::iterator, typename T::value_type>::setData(it, val);
}

template<typename T> inline void handler::insertPrivate(void *c, int idx, const void *val)
{
    containerAPI<T>::insertData(static_cast<T *>(c), idx, val);
}

template<typename T> inline void handler::removePrivate(void *c, int idx)
{
    containerAPI<T>::removeData(static_cast<T *>(c), idx);
}

template<typename T> inline const void *handler::atPrivate(const void *c, int idx)
{
    typename T::const_iterator it = static_cast<const T *>(c)->begin();
    std::advance(it, idx);
    return iteratorOwner<typename T::const_iterator, typename T::value_type>::data(it);
}
    
template<typename T> inline void handler::moveToBeginPrivate(void *c, void *& it)
{
    iteratorOwner<typename T::iterator, typename T::value_type>::assign(it, static_cast<T *>(c)->begin());
}
    
template<typename T> inline void handler::moveToCBeginPrivate(void *c, void *& it)
{
    const void *cc = c;
    iteratorOwner<typename T::const_iterator, typename T::value_type>::assign(it, static_cast<const T *>(cc)->begin());
}

template<typename T> inline void handler::moveToEndPrivate(void *c, void *& it)
{
    iteratorOwner<typename T::iterator, typename T::value_type>::assign(it, static_cast<T *>(c)->end());
}

template<typename T> inline void handler::moveToCEndPrivate(void *c, void *& it)
{
    const void *cc = c;
    iteratorOwner<typename T::const_iterator, typename T::value_type>::assign(it, static_cast<const T *>(cc)->end());
}

template<typename T> inline void handler::destroyIteratorPrivate(void *& it)
{
    iteratorOwner<typename T::iterator, typename T::value_type>::destroy(it);
}

template<typename T> inline void handler::destroyConstIteratorPrivate(void *& it)
{
    iteratorOwner<typename T::const_iterator, typename T::value_type>::destroy(it);
}

template<typename T> inline bool handler::equalIteratorPrivate(void *it, void *o)
{
    return iteratorOwner<typename T::iterator, typename T::value_type>::equal(it, o);
}

template<typename T> inline bool handler::equalConstIteratorPrivate(void *it, void *o)
{
    return iteratorOwner<typename T::const_iterator, typename T::value_type>::equal(it, o);
}

template<typename T> inline void handler::copyIteratorPrivate(void *& it, void *const& o)
{
    iteratorOwner<typename T::iterator, typename T::value_type>::assign(it, o);
}

template<typename T> inline void handler::copyConstIteratorPrivate(void *& it, void *const& o)
{
    iteratorOwner<typename T::const_iterator, typename T::value_type>::assign(it, o);
}

template<typename T> inline void handler::advancePrivate(void *& it, int step)
{
    iteratorOwner<typename T::iterator, typename T::value_type>::advance(it, step);
}

template<typename T> inline void handler::advanceConstPrivate(void *& it, int step)
{
    iteratorOwner<typename T::const_iterator, typename T::value_type>::advance(it, step);
}

template<typename T> inline Data handler::getDataPrivate(void *const& it, int metaTypeId, uint flags)
{
    return Data(metaTypeId, iteratorOwner<typename T::iterator, typename T::value_type>::data(it), flags);
}

template<typename T> inline Data handler::getConstDataPrivate(void *const& it, int metaTypeId, uint flags)
{
    return Data(metaTypeId, iteratorOwner<typename T::const_iterator, typename T::value_type>::data(it), flags);
}

template<typename T> inline const void *handler::iteratorValuePrivate(void *const& it)
{
    return iteratorOwner<typename T::iterator, typename T::value_type>::data(it);
}

template<typename T> inline void handler::setValueToIteratorPrivate(void *it, const void *val)
{
    iteratorOwner<typename T::iterator, typename T::value_type>::setData(it, val);
}

template<typename T> inline void handler::addValueToItemPrivate(void *it, const void *val)
{
    iteratorOwner<typename T::iterator, typename T::value_type>::add(it, val);
}

template<typename T> inline void handler::subValueToItemPrivate(void *it, const void *val)
{
    iteratorOwner<typename T::iterator, typename T::value_type>::sub(it, val);
}

template<typename T> inline void handler::mulValueToItemPrivate(void *it, const void *val)
{
    iteratorOwner<typename T::iterator, typename T::value_type>::mul(it, val);
}

template<typename T> inline void handler::divValueToItemPrivate(void *it, const void *val)
{
    iteratorOwner<typename T::iterator, typename T::value_type>::div(it, val);
}

template<typename T> inline bool handler::isItemEqualToPrivate(void *it, const void *val)
{
    return iteratorOwner<typename T::iterator, typename T::value_type>::isEqual(it, val);
}

template<typename T> inline int handler::indexOfIteratorPrivate(void *c, void *const& it)
{
    typename T::iterator from = static_cast<T *>(c)->begin();
    return iteratorOwner<typename T::iterator, typename T::value_type>::distance(from, it);
}

template<typename T> inline int handler::indexOfConstIteratorPrivate(void *c, void *const& it)
{
    const void *cc = c;
    typename T::const_iterator from = static_cast<const T *>(cc)->begin();
    return iteratorOwner<typename T::const_iterator, typename T::value_type>::distance(from, it);
}

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialPrivate::handler implementation
// /////////////////////////////////////////////////////////////////

template<typename T> inline handler::handler(T *c) : m_container(c),
                                                     m_iterator(0),
                                                     m_metaType_id(qMetaTypeId<typename T::value_type>()),
                                                     m_metaType_flags(QTypeInfo<typename T::value_type>::isPointer),
                                                     m_iterator_capabilities(containerAPI<T>::IteratorCapabilities),
                                                     m_clear(clearPrivate<T>),
                                                     m_reserve(reservePrivate<T>),
                                                     m_resize(resizePrivate<T>),
                                                     m_empty(emptyPrivate<T>),
                                                     m_size(sizePrivate<T>),
                                                     m_setAt(setAtPrivate<T>),
                                                     m_insert(insertPrivate<T>),
                                                     m_remove(removePrivate<T>),
                                                     m_at(atPrivate<T>),
                                                     m_advance(advancePrivate<T>),
                                                     m_advanceConst(advanceConstPrivate<T>),
                                                     m_getData(getDataPrivate<T>),
                                                     m_getConstData(getConstDataPrivate<T>),
                                                     m_moveToBegin(moveToBeginPrivate<T>),
                                                     m_moveToCBegin(moveToCBeginPrivate<T>),
                                                     m_moveToEnd(moveToEndPrivate<T>),
                                                     m_moveToCEnd(moveToCEndPrivate<T>),
                                                     m_destroyIterator(destroyIteratorPrivate<T>),
                                                     m_destroyConstIterator(destroyConstIteratorPrivate<T>),
                                                     m_equalIterator(equalIteratorPrivate<T>),
                                                     m_equalConstIterator(equalConstIteratorPrivate<T>),
                                                     m_copyIterator(copyIteratorPrivate<T>),
                                                     m_copyConstIterator(copyConstIteratorPrivate<T>),
                                                     m_iteratorValue(iteratorValuePrivate<T>),
                                                     m_setValueToIterator(setValueToIteratorPrivate<T>),
                                                     m_addValueTotItem(addValueToItemPrivate<T>),
                                                     m_subValueTotItem(subValueToItemPrivate<T>),
                                                     m_mulValueTotItem(mulValueToItemPrivate<T>),
                                                     m_divValueTotItem(divValueToItemPrivate<T>),
                                                     m_isItemEqualTo(isItemEqualToPrivate<T>),
                                                     m_indexOfIterator(indexOfIteratorPrivate<T>),
                                                     m_indexOfConstIterator(indexOfConstIteratorPrivate<T>)
{
}

inline handler::handler(void) : m_container(0),
                                m_iterator(0),
                                m_metaType_id(QMetaType::UnknownType),
                                m_metaType_flags(0),
                                m_iterator_capabilities(0),
                                m_clear(0),
                                m_reserve(0),
                                m_resize(0),
                                m_empty(0),
                                m_size(0),
                                m_setAt(0),
                                m_insert(0),
                                m_remove(0),
                                m_at(0),
                                m_advance(0),
                                m_advanceConst(0),
                                m_getData(0),
                                m_getConstData(0),
                                m_moveToBegin(0),
                                m_moveToCBegin(0),
                                m_moveToEnd(0),
                                m_moveToCEnd(0),
                                m_destroyIterator(0),
                                m_destroyConstIterator(0),
                                m_equalIterator(0),
                                m_equalConstIterator(0),
                                m_copyIterator(0),
                                m_copyConstIterator(0),
                                m_iteratorValue(0),
                                m_setValueToIterator(0),
                                m_addValueTotItem(0),
                                m_subValueTotItem(0),
                                m_mulValueTotItem(0),
                                m_divValueTotItem(0),
                                m_isItemEqualTo(0),
                                m_indexOfIterator(0),
                                m_indexOfConstIterator(0)
{
}

inline void handler::clear(void)
{
    Q_ASSERT(m_container);
    this->m_clear(m_container);
}

inline void handler::reserve(int size)
{
    Q_ASSERT(m_container);
    this->m_reserve(m_container, size);
}

inline void handler::resize(int size)
{
    Q_ASSERT(m_container);
    this->m_resize(m_container, size);
}

inline bool handler::empty(void)
{
    Q_ASSERT(m_container);
    return this->m_empty(m_container);
}

inline int handler::size(void)
{
    Q_ASSERT(m_container);
    return this->m_size(m_container);
}

inline void handler::setAt(int idx, const void *val)
{ 
    this->m_setAt(m_container, idx, val); 
}

inline void handler::insert(int idx, const void *val)
{ 
    this->m_insert(m_container, idx, val);
}

inline void handler::remove(int idx)
{ 
    this->m_remove(m_container, idx);
}

inline Data handler::at(int idx) const
{ 
    return Data(m_metaType_id, this->m_at(m_container, idx), m_metaType_flags);
}

inline Data handler::currentData(void) const
{
    return this->m_getData(m_iterator, m_metaType_id, m_metaType_flags);
}

inline Data handler::currentConstData(void) const
{
    return this->m_getConstData(m_iterator, m_metaType_id, m_metaType_flags);
}

inline handler& handler::advance(int step)
{
    Q_ASSERT(step > 0 || m_iterator_capabilities & BiDirectionalCapability);
    this->m_advance(m_iterator, step);
    return *this;
}

inline handler& handler::advanceConst(int step)
{
    this->m_advanceConst(m_iterator, step);
    return *this;
}

inline void handler::moveToBegin(void)
{ 
    this->m_moveToBegin(m_container, m_iterator);
}

inline void handler::moveToCBegin(void)
{ 
    this->m_moveToCBegin(m_container, m_iterator);
}

inline void handler::moveToEnd(void)
{ 
    this->m_moveToEnd(m_container, m_iterator);
}

inline void handler::moveToCEnd(void)
{ 
    this->m_moveToCEnd(m_container, m_iterator);
}

inline void handler::destroyIterator(void)
{ 
    this->m_destroyIterator(m_iterator);
}

inline void handler::destroyConstIterator(void)
{ 
    this->m_destroyConstIterator(m_iterator);
}

inline bool handler::equal(const handler& o) const
{ 
    return this->m_equalIterator(m_iterator, o.m_iterator);
}

inline bool handler::equalConst(const handler& o) const
{ 
    return this->m_equalConstIterator(m_iterator, o.m_iterator);
}

inline void handler::copy(const handler& o)
{ 
    *this = o;
    this->m_copyIterator(m_iterator, o.m_iterator);
}

inline void handler::copyConst(const handler& o)
{ 
    *this = o;
    this->m_copyConstIterator(m_iterator, o.m_iterator);
}

inline void handler::setValueToIterator(const void *value)
{
    this->m_setValueToIterator(m_iterator, value);
}

inline int handler::indexOfIterator(void) const
{
    return this->m_indexOfIterator(m_container, m_iterator);
}

inline void handler::addValueToItem(const void *value)
{
    this->m_addValueTotItem(m_iterator, value);
}

inline void handler::subValueToItem(const void *value)
{
    this->m_subValueTotItem(m_iterator, value);
}

inline void handler::mulValueToItem(const void *value)
{
    this->m_mulValueTotItem(m_iterator, value);
}

inline void handler::divValueToItem(const void *value)
{
    this->m_divValueTotItem(m_iterator, value);
}

inline bool handler::isItemEqualTo(const void *value) const
{
    return this->m_isItemEqualTo(m_iterator, value);
}

inline const void *handler::iteratorValue(void) const
{
    return this->m_iteratorValue(m_iterator);
}

inline int handler::indexOfConstIterator(void) const
{
    return this->m_indexOfConstIterator(m_container, m_iterator);
}

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialPrivate::convertFunctor for QMetatype system
// /////////////////////////////////////////////////////////////////

template<typename From> handler convertFunctor<From *>::operator () (From *f) const
{
    return handler(f);
}

// /////////////////////////////////////////////////////////////////

} // end of dtkMetaContainerSequentialPrivate namespace

// /////////////////////////////////////////////////////////////////
// Redifinition of Qt helper classes to handle our meta containers
// /////////////////////////////////////////////////////////////////

namespace QtPrivate {  
template<typename T> inline bool SequentialContainerConverterHelper<T *, false>::registerConverter(int) 
{ 
    return false; 
}
    
template<typename T> inline bool ValueTypeIsMetaType<T *, false>::registerConverter(int) 
{ 
    return false; 
}
    
template<typename T> inline bool ValueTypeIsMetaType<T *, true>::registerConverter(int id)
{
    const int toId = qMetaTypeId<dtkMetaContainerSequentialPrivate::handler>();
    if (!QMetaType::hasRegisteredConverterFunction(id, toId)) {
        dtkMetaContainerSequentialPrivate::convertFunctor<T *> o;
        static const QtPrivate::ConverterFunctor<T *,
                                                 dtkMetaContainerSequentialPrivate::handler,
                                                 dtkMetaContainerSequentialPrivate::convertFunctor<T *> > f(o);
        return QMetaType::registerConverterFunction(&f, id, toId);
    }
    return true;
}
}

//
// dtkMetaContainerSequential.tpp ends here

