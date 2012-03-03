/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef SPANQUERYFILTER_H
#define SPANQUERYFILTER_H

#include "SpanFilter.h"

namespace Lucene
{
    /// Constrains search results to only match those which also match a provided query.  Also provides position
    /// information about where each document matches at the cost of extra space compared with the
    /// QueryWrapperFilter.  There is an added cost to this above what is stored in a {@link QueryWrapperFilter}.
    /// Namely, the position information for each matching document is stored.
    ///
    /// This filter does not cache.  See the {@link CachingSpanFilter} for a wrapper that caches.
    class LPPAPI SpanQueryFilter : public SpanFilter
    {
    public:
        /// Constructs a filter which only matches documents matching query.
        /// @param query The {@link SpanQuery} to use as the basis for the Filter.
        SpanQueryFilter(SpanQueryPtr query = SpanQueryPtr());

        virtual ~SpanQueryFilter();

        LUCENE_CLASS(SpanQueryFilter);

    protected:
        SpanQueryPtr query;

    protected:
        virtual void mark_members(gc* gc) const
        {
            gc->mark(query);
            SpanFilter::mark_members(gc);
        }

    public:
        virtual DocIdSetPtr getDocIdSet(IndexReaderPtr reader);
        virtual SpanFilterResultPtr bitSpans(IndexReaderPtr reader);

        SpanQueryPtr getQuery();

        virtual String toString();
        virtual bool equals(LuceneObjectPtr other);
        virtual int32_t hashCode();
    };
}

#endif
