/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef CLOSEABLETHREADLOCAL_H
#define CLOSEABLETHREADLOCAL_H

#include "LuceneThread.h"

namespace Lucene
{
    /// General purpose thread-local map.

    // todo: could this be replaced by boost::tss?

    template <typename T>
    class CloseableThreadLocal : public LuceneObject
    {
    public:
        typedef gc_ptr<T> localDataPtr;
        typedef SortedMap<int64_t, localDataPtr> MapLocalData;

        CloseableThreadLocal()
        {
            localData = MapLocalData::newInstance();
        }

    protected:
        MapLocalData localData;

    protected:
        virtual void mark_members(gc* gc) const
        {
            gc->mark(localData);
            LuceneObject::mark_members(gc);
        }

    public:
        localDataPtr get()
        {
            SyncLock syncLock(this);
            typename MapLocalData::iterator local = localData.find(LuceneThread::currentId());
            if (local != localData.end())
                return local->second;
            localDataPtr initial(initialValue());
            if (initial)
                localData.put(LuceneThread::currentId(), initial);
            return initial;
        }

        void set(localDataPtr data)
        {
            SyncLock syncLock(this);
            localData.put(LuceneThread::currentId(), data);
        }

        void close()
        {
            SyncLock syncLock(this);
            localData.remove(LuceneThread::currentId());
        }

    protected:
        virtual localDataPtr initialValue()
        {
            return localDataPtr(); // override
        }
    };
}

#endif
