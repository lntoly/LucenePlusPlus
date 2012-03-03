/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/any.hpp>
#include "LuceneThread.h"

namespace Lucene
{
    typedef boost::shared_ptr<boost::asio::io_service::work> workPtr;

    /// A Future represents the result of an asynchronous computation. Methods are provided to check if the computation
    /// is complete, to wait for its completion, and to retrieve the result of the computation. The result can only be
    /// retrieved using method get when the computation has completed, blocking if necessary until it is ready.
    class Future : public LuceneObject
    {
    public:
        virtual ~Future();

    protected:
        boost::any value;

    public:
        void set(const boost::any& value)
        {
            SyncLock syncLock(this);
            this->value = value;
        }

        template <typename T>
        T get()
        {
            SyncLock syncLock(this);
            while (value.empty())
                wait(10);
            return value.empty() ? T() : boost::any_cast<T>(value);
        }
    };

    class ThreadFunction : public LuceneThread
    {
    public:
        ThreadFunction(const boost::asio::io_service& io_service);
        virtual ~ThreadFunction();

        LUCENE_CLASS(ThreadFunction);

    protected:
        const boost::asio::io_service& service;

    public:
        virtual void run();
    };

    /// Utility class to handle a pool of threads.
    class ThreadPool : public LuceneObject
    {
    public:
        ThreadPool();
        virtual ~ThreadPool();

        LUCENE_CLASS(ThreadPool);

    protected:
        boost::asio::io_service io_service;
        workPtr work;
        Collection<LuceneThreadPtr> threads;

        static const int32_t THREADPOOL_SIZE;

    protected:
        virtual void mark_members(gc* gc) const
        {
            gc->mark(threads);
            LuceneObject::mark_members(gc);
        }

    public:
        /// Get singleton thread pool instance.
        static ThreadPoolPtr getInstance();

        template <typename FUNC>
        FuturePtr scheduleTask(FUNC func)
        {
            FuturePtr future(newLucene<Future>());
            io_service.post(boost::bind(&ThreadPool::execute<FUNC>, this, func, future));
            return future;
        }

    protected:
        // this will be executed when one of the threads is available
        template <typename FUNC>
        void execute(FUNC func, FuturePtr future)
        {
            future->set(func());
            future->notifyAll();
        }
    };
}

#endif
