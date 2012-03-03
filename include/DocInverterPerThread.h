/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef DOCINVERTERPERTHREAD_H
#define DOCINVERTERPERTHREAD_H

#include "DocFieldConsumerPerThread.h"
#include "AttributeSource.h"

namespace Lucene
{
    /// This is a DocFieldConsumer that inverts each field, separately, from a Document, and accepts a
    /// InvertedTermsConsumer to process those terms.
    class DocInverterPerThread : public DocFieldConsumerPerThread
    {
    public:
        DocInverterPerThread(DocFieldProcessorPerThreadPtr docFieldProcessorPerThread, DocInverterPtr docInverter);
        virtual ~DocInverterPerThread();

        LUCENE_CLASS(DocInverterPerThread);

    public:
        DocInverterPtr docInverter;
        InvertedDocConsumerPerThreadPtr consumer;
        InvertedDocEndConsumerPerThreadPtr endConsumer;
        SingleTokenAttributeSourcePtr singleToken;

        DocStatePtr docState;
        FieldInvertStatePtr fieldState;

        /// Used to read a string value for a field
        ReusableStringReaderPtr stringReader;

    protected:
        virtual void mark_members(gc* gc) const
        {
            gc->mark(docInverter);
            gc->mark(consumer);
            gc->mark(endConsumer);
            gc->mark(singleToken);
            gc->mark(docState);
            gc->mark(fieldState);
            gc->mark(stringReader);
            DocFieldConsumerPerThread::mark_members(gc);
        }

    public:
        virtual void initialize();
        virtual void startDocument();
        virtual DocWriterPtr finishDocument();
        virtual void abort();
        virtual DocFieldConsumerPerFieldPtr addField(FieldInfoPtr fi);
    };

    class SingleTokenAttributeSource : public AttributeSource
    {
    public:
        SingleTokenAttributeSource();
        virtual ~SingleTokenAttributeSource();

        LUCENE_CLASS(SingleTokenAttributeSource);

    public:
        TermAttributePtr termAttribute;
        OffsetAttributePtr offsetAttribute;

    protected:
        virtual void mark_members(gc* gc) const
        {
            gc->mark(termAttribute);
            gc->mark(offsetAttribute);
            AttributeSource::mark_members(gc);
        }

    public:
        void reinit(const String& stringValue, int32_t startOffset, int32_t endOffset);
    };
}

#endif
