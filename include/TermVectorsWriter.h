/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef TERMVECTORSWRITER_H
#define TERMVECTORSWRITER_H

#include "LuceneObject.h"

namespace Lucene
{
    class TermVectorsWriter : public LuceneObject
    {
    public:
        TermVectorsWriter(DirectoryPtr directory, const String& segment, FieldInfosPtr fieldInfos);
        virtual ~TermVectorsWriter();

        LUCENE_CLASS(TermVectorsWriter);

    protected:
        IndexOutputPtr tvx;
        IndexOutputPtr tvd;
        IndexOutputPtr tvf;
        FieldInfosPtr fieldInfos;
        Collection<UTF8ResultPtr> utf8Results;

    protected:
        virtual void mark_members(gc* gc) const
        {
            gc->mark(tvx);
            gc->mark(tvd);
            gc->mark(tvf);
            gc->mark(fieldInfos);
            gc->mark(utf8Results);
            LuceneObject::mark_members(gc);
        }

    public:
        /// Add a complete document specified by all its term vectors. If document has no term vectors,
        /// add value for tvx.
        void addAllDocVectors(Collection<TermFreqVectorPtr> vectors);

        /// Do a bulk copy of numDocs documents from reader to our streams.  This is used to expedite merging,
        /// if the field numbers are congruent.
        void addRawDocuments(TermVectorsReaderPtr reader, Collection<int32_t> tvdLengths, Collection<int32_t> tvfLengths, int32_t numDocs);

        /// Close all streams.
        void close();
    };
}

#endif
