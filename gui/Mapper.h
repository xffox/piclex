#ifndef MAPPER_H
#define MAPPER_H

#include <tr1/functional>

#include <cassert>

#include <QMap>
#include <QList>
#include <QMutex>
#include <QMutexLocker>

#include "Logger.h"
#include "MapperCallback.h"

namespace gui
{
template<class In, class Out>
class MapperThread;

//! Asynchronous mapper
/*!
 * Asynchronously map input to output with the mapping function. Store
 * results in the cache-like storage.
 */
//TODO: or use another class Map for the map functor?
template<class In, class Out>
class Mapper
{
    friend class MapperThread<In, Out>;

public:
    typedef std::tr1::function<void (Out&, const In&)> MapFunc;
    typedef MapperCallback<In, Out> *Callback;

private:
    typedef QMap<In, QList<Callback> > CallbacksMap;

public:
    Mapper(MapFunc mapFunc);
    ~Mapper();

    //! Get a previously stored result if exists.
    /*!
     * Search for a stored result.
     * \return true if the result has been found, false otherwise.
     */
    bool mapStored(Out &out, const In &in) const;

    //! Initiate async mapping.
    /*!
     * The callback will be called immediately if the result exists.
     */
    void map(const In &in, Callback callback);

    //! Initiate async mapping.
    /*!
     * Just to store the result, no callback.
     */
    void map(const In &in);

    //! Cancel async mapping.
    void cancel(const In &in, Callback callback);

    //! Cancel async mapping.
    void cancel(Callback callback);

private:
    bool getNextInput(In &in);
    void setResult(const In &in, const Out &out);

private:
    void storeResult(const In &in, const Out &out);
    void removeResult(const In &in);

    void callCallbacks(const In &in);

    void addCallback(const In &in, Callback callback);
    void remCallback(const In &in, Callback callback);
    void remCallbacks(Callback callback);

    // returns next iter
    typename CallbacksMap::iterator remCallbacksByIter(
            typename CallbacksMap::iterator callbacksMapIter, Callback callback);

    void addInput(const In &in);
    void remInput(const In &in);

private:
    MapFunc mMapFunc;

    // the order is important, can't use QSet
    QList<In> mInputs;
    QMap<In, Out> mResults;
    QList<In> mRemoveOrder;

    MapperThread<In, Out> *mMapperThread;

    CallbacksMap mCallbacksMap;

    size_t mMaxStored;

    mutable QMutex mInputsMutex;
    mutable QMutex mResultsMutex;
};
}

#include "MapperThread.h"

namespace gui
{
template<class In, class Out>
Mapper<In, Out>::Mapper(MapFunc mapFunc)
    :mMapFunc(mapFunc)
    ,mMaxStored(100)
{
    mMapperThread = new MapperThread<In, Out>(this, mapFunc);

    mMapperThread->start();
}

template<class In, class Out>
Mapper<In, Out>::~Mapper()
{
    //TODO: check join
    delete mMapperThread;
}

template<class In, class Out>
bool Mapper<In, Out>::mapStored(Out &out, const In &in) const
{
    QMutexLocker locker(&mResultsMutex);

    typename QMap<In, Out>::const_iterator iter = mResults.find(in);
    if(iter != mResults.end())
    {
        out = *iter;
        return true;
    }
    return false;
}

template<class In, class Out>
void Mapper<In, Out>::map(const In &in, Callback callback)
{
    QMutexLocker locker(&mResultsMutex);

    typename QMap<In, Out>::const_iterator iter = mResults.find(in);
    if(iter != mResults.end())
    {
        if(callback)
            callback->call(in, *iter);
        return;
    }

    addCallback(in, callback);
}

template<class In, class Out>
void Mapper<In, Out>::map(const In &in)
{
    QMutexLocker locker(&mResultsMutex);

    typename QMap<In, Out>::const_iterator iter = mResults.find(in);
    if(iter == mResults.end())
        addInput(in);
}

template<class In, class Out>
void Mapper<In, Out>::cancel(const In &in, Callback callback)
{
    QMutexLocker locker(&mResultsMutex);

    remCallback(in, callback);
}

template<class In, class Out>
void Mapper<In, Out>::cancel(Callback callback)
{
    QMutexLocker locker(&mResultsMutex);

    remCallbacks(callback);
}

template<class In, class Out>
bool Mapper<In, Out>::getNextInput(In &in)
{
    QMutexLocker locker(&mInputsMutex);

    if(mInputs.size() > 0)
    {
        in = mInputs.front();
        //TODO: need a pointer for multiple threads
#if 0
        mInputs.pop_front();
#endif
        return true;
    }
    return false;
}

template<class In, class Out>
void Mapper<In, Out>::setResult(const In &in, const Out &out)
{
    QMutexLocker locker(&mResultsMutex);

    storeResult(in, out);

    callCallbacks(in);

    //TODO: move it
    remInput(in);
}

template<class In, class Out>
void Mapper<In, Out>::storeResult(const In &in, const Out &out)
{
    assert(mResults.size() == mRemoveOrder.size());

    typename QMap<In, Out>::const_iterator resultsIter = mResults.find(in);
    if(resultsIter == mResults.end())
    {
        while(static_cast<size_t>(mResults.size()) >= mMaxStored)
            removeResult(mRemoveOrder.front());
        mRemoveOrder.push_back(in);
    }
    mResults[in] = out;

    base::Log().debug("Mapper stored '%s'", qPrintable(in));
    base::Log().debug("Mapper stored size= %d", mResults.size());
}

template<class In, class Out>
void Mapper<In, Out>::removeResult(const In &in)
{
    assert(mResults.size() == mRemoveOrder.size());

    mResults.remove(in);
    mRemoveOrder.removeOne(in);

    base::Log().debug("Mapper removed '%s'", qPrintable(in));
}

template<class In, class Out>
void Mapper<In, Out>::callCallbacks(const In &in)
{
    typename QMap<In, Out>::const_iterator resultsIter = mResults.find(in);
    //TODO: fix it
    assert(resultsIter != mResults.end());

    typename CallbacksMap::iterator callbacksMapIter = mCallbacksMap.find(in);
    if(callbacksMapIter != mCallbacksMap.end())
    {
        typename QList<Callback>::iterator iter = callbacksMapIter->begin();
        for(; iter != callbacksMapIter->end(); ++iter)
            (*iter)->call(in, *resultsIter);

        mCallbacksMap.erase(callbacksMapIter);
    }
}

template<class In, class Out>
void Mapper<In, Out>::addCallback(const In &in, Callback callback)
{
    typename CallbacksMap::iterator callbacksMapIter = mCallbacksMap.find(in);
    if(callbacksMapIter != mCallbacksMap.end())
    {
        if(callback)
            if(!callbacksMapIter->contains(callback))
                callbacksMapIter->append(callback);
    }
    else
    {
        if(callback)
        {
            QList<Callback> inCallbacks;
            inCallbacks.append(callback);
            mCallbacksMap[in] = inCallbacks;
        }

        addInput(in);
    }
}

template<class In, class Out>
void Mapper<In, Out>::remCallback(const In &in, Callback callback)
{
    if(!callback)
        return;

    remCallbacksByIter(mCallbacksMap.find(in), callback);
}

template<class In, class Out>
void Mapper<In, Out>::remCallbacks(Callback callback)
{
    if(!callback)
        return;

    typename CallbacksMap::iterator callbacksMapIter = mCallbacksMap.begin();
    while(callbacksMapIter != mCallbacksMap.end())
        callbacksMapIter = remCallbacksByIter(callbacksMapIter, callback);
}

template<class In, class Out>
typename Mapper<In, Out>::CallbacksMap::iterator
Mapper<In, Out>::remCallbacksByIter(
        typename CallbacksMap::iterator callbacksMapIter, Callback callback)
{
    if(callbacksMapIter != mCallbacksMap.end())
    {
        callbacksMapIter->removeOne(callback);
        if(callbacksMapIter->isEmpty())
        {
            remInput(callbacksMapIter.key());

            return mCallbacksMap.erase(callbacksMapIter);
        }

        return ++callbacksMapIter;
    }
    return callbacksMapIter;
}

template<class In, class Out>
void Mapper<In, Out>::addInput(const In &in)
{
    QMutexLocker locker(&mInputsMutex);

    if(!mInputs.contains(in))
        mInputs.push_back(in);
}

template<class In, class Out>
void Mapper<In, Out>::remInput(const In &in)
{
    QMutexLocker locker(&mInputsMutex);

    // removeAll() is older but slower
    mInputs.removeOne(in);
}

}

#endif//MAPPER_H
