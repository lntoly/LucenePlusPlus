/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef _REVERSEORDFIELDSOURCE_H
#define _REVERSEORDFIELDSOURCE_H

#include "DocValues.h"

namespace Lucene
{
    class ReverseOrdDocValues : public DocValues
    {
    public:
        ReverseOrdDocValues(ReverseOrdFieldSourcePtr source, Collection<int32_t> arr, int32_t end);
        virtual ~ReverseOrdDocValues();

        LUCENE_CLASS(ReverseOrdDocValues);

    protected:
        ReverseOrdFieldSourcePtr source;
        Collection<int32_t> arr;
        int32_t end;

    protected:
        virtual void mark_members(gc* gc) const
        {
            gc->mark(source);
            gc->mark(arr);
            DocValues::mark_members(gc);
        }

    public:
        virtual double doubleVal(int32_t doc);
        virtual int32_t intVal(int32_t doc);
        virtual String strVal(int32_t doc);
        virtual String toString(int32_t doc);
        virtual CollectionValue getInnerArray();
    };
}

#endif
