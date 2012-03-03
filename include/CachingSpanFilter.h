/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef CACHINGSPANFILTER_H
#define CACHINGSPANFILTER_H

#include "SpanFilter.h"
#include "CachingWrapperFilter.h"

namespace Lucene
{
    /// Wraps another SpanFilter's result and caches it.  The purpose is to allow filters to simply filter,
    /// and then wrap with this class to add caching.
    class LPPAPI CachingSpanFilter : public SpanFilter
    {
    public:
        /// New deletions always result in a cache miss, by default ({@link CachingWrapperFilter#RECACHE}.
        CachingSpanFilter(SpanFilterPtr filter, CachingWrapperFilter::DeletesMode deletesMode = CachingWrapperFilter::DELETES_RECACHE);
        virtual ~CachingSpanFilter();

        LUCENE_CLASS(CachingSpanFilter);

    protected:
        SpanFilterPtr filter;
        FilterCachePtr cache;

    public:
        // for testing
        int32_t hitCount;
        int32_t missCount;

    protected:
        virtual void mark_members(gc* gc) const
        {
            gc->mark(filter);
            gc->mark(cache);
            SpanFilter::mark_members(gc);
        }

    public:
        virtual DocIdSetPtr getDocIdSet(IndexReaderPtr reader);
        virtual SpanFilterResultPtr bitSpans(IndexReaderPtr reader);

        virtual String toString();
        virtual bool equals(LuceneObjectPtr other);
        virtual int32_t hashCode();

    protected:
        SpanFilterResultPtr getCachedResult(IndexReaderPtr reader);
    };
}

#endif
