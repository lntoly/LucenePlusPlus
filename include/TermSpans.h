/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef TERMSPANS_H
#define TERMSPANS_H

#include "Spans.h"

namespace Lucene
{
    /// Public for extension only
    class LPPAPI TermSpans : public Spans
    {
    public:
        TermSpans(TermPositionsPtr positions, TermPtr term);
        virtual ~TermSpans();

        LUCENE_CLASS(TermSpans);

    protected:
        TermPositionsPtr positions;
        TermPtr term;
        int32_t _doc;
        int32_t freq;
        int32_t count;
        int32_t position;

    protected:
        virtual void mark_members(gc* gc) const
        {
            gc->mark(positions);
            gc->mark(term);
            Spans::mark_members(gc);
        }

    public:
        virtual bool next();
        virtual bool skipTo(int32_t target);
        virtual int32_t doc();
        virtual int32_t start();
        virtual int32_t end();
        virtual Collection<ByteArray> getPayload();
        virtual bool isPayloadAvailable();
        virtual String toString();

        TermPositionsPtr getPositions();
    };
}

#endif
