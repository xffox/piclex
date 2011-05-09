#ifndef MAPPER_THREAD_H
#define MAPPER_THREAD_H

#include <QThread>

#include "Mapper.h"

namespace gui
{
template<class In, class Out>
class MapperThread: public QThread
{
public:
    MapperThread(Mapper<In, Out> *parent,
            typename Mapper<In, Out>::MapFunc mapFunc);
    ~MapperThread();

protected:
    void run();

    void stopLoop();

private:
    Mapper<In, Out> *mParent;
    typename Mapper<In, Out>::MapFunc mMapFunc;

    bool mRun;

    const unsigned long mLoopSleepMicroseconds;
};

template<class In, class Out>
MapperThread<In, Out>::MapperThread(Mapper<In, Out> *parent,
        typename Mapper<In, Out>::MapFunc mapFunc)
    :mParent(parent), mMapFunc(mapFunc)
    ,mRun(false)
    ,mLoopSleepMicroseconds(1000)
{
}

template<class In, class Out>
MapperThread<In, Out>::~MapperThread()
{
    stopLoop();

    wait();
}

template<class In, class Out>
void MapperThread<In, Out>::run()
{
    mRun = true;
    In in;
    Out out;
    do
    {
        if(mParent->getNextInput(in))
        {
            mMapFunc(out, in);
            mParent->setResult(in, out);
        }
        else
        {
            usleep(mLoopSleepMicroseconds);
        }
    }while(mRun);
}

template<class In, class Out>
void MapperThread<In, Out>::stopLoop()
{
    mRun = false;
}

}

#endif//MAPPER_THREAD_H
