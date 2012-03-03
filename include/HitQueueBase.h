/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef HITQUEUEBASE_H
#define HITQUEUEBASE_H

#include "PriorityQueue.h"

namespace Lucene
{
    class LPPAPI HitQueueBase : public LuceneObject
    {
    public:
        HitQueueBase(int32_t size);
        virtual ~HitQueueBase();

        LUCENE_CLASS(HitQueueBase);

    public:
        virtual ScoreDocPtr add(ScoreDocPtr scoreDoc);
        virtual ScoreDocPtr addOverflow(ScoreDocPtr scoreDoc);
        virtual ScoreDocPtr top();
        virtual ScoreDocPtr pop();
        virtual ScoreDocPtr updateTop();
        virtual int32_t size();
        virtual bool empty();
        virtual void clear();

    protected:
        PriorityQueueScoreDocsPtr queue;
        int32_t queueSize;

    protected:
        virtual void mark_members(gc* gc) const
        {
            gc->mark(queue);
            LuceneObject::mark_members(gc);
        }

    public:
        virtual void initialize();

    protected:
        virtual bool lessThan(const ScoreDocPtr& first, const ScoreDocPtr& second) = 0;
        virtual ScoreDocPtr getSentinelObject();

        friend class PriorityQueueScoreDocs;
    };

    class LPPAPI PriorityQueueScoreDocs : public PriorityQueue<ScoreDocPtr>
    {
    public:
        PriorityQueueScoreDocs(HitQueueBasePtr hitQueue, int32_t size);
        virtual ~PriorityQueueScoreDocs();

        LUCENE_CLASS(PriorityQueueScoreDocs);

    protected:
        HitQueueBasePtr hitQueue;

    protected:
        virtual void mark_members(gc* gc) const
        {
            gc->mark(hitQueue);
            PriorityQueue<ScoreDocPtr>::mark_members(gc);
        }

    protected:
        virtual bool lessThan(const ScoreDocPtr& first, const ScoreDocPtr& second);
        virtual ScoreDocPtr getSentinelObject();
    };
}

#endif
