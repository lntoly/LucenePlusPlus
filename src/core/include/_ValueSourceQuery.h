/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef _VALUESOURCEQUERY_H
#define _VALUESOURCEQUERY_H

#include "Weight.h"
#include "Scorer.h"

namespace Lucene
{
    class ValueSourceWeight : public Weight
    {
    public:
        ValueSourceWeight(ValueSourceQueryPtr query, SearcherPtr searcher);
        virtual ~ValueSourceWeight();

        LUCENE_CLASS(ValueSourceWeight);

    public:
        ValueSourceQueryPtr query;
        SimilarityPtr similarity;
        double queryNorm;
        double queryWeight;

    protected:
        virtual void mark_members(gc* gc) const
        {
            gc->mark(query);
            gc->mark(similarity);
            Weight::mark_members(gc);
        }

    public:
        virtual QueryPtr getQuery();
        virtual double getValue();
        virtual double sumOfSquaredWeights();
        virtual void normalize(double norm);
        virtual ScorerPtr scorer(IndexReaderPtr reader, bool scoreDocsInOrder, bool topScorer);
        virtual ExplanationPtr explain(IndexReaderPtr reader, int32_t doc);
    };

    /// A scorer that (simply) matches all documents, and scores each document with the value of the value
    /// source in effect. As an example, if the value source is a (cached) field source, then value of that
    /// field in that document will be used. (assuming field is indexed for this doc, with a single token.)
    class ValueSourceScorer : public Scorer
    {
    public:
        ValueSourceScorer(SimilarityPtr similarity, IndexReaderPtr reader, ValueSourceWeightPtr weight);
        virtual ~ValueSourceScorer();

        LUCENE_CLASS(ValueSourceScorer);

    public:
        ValueSourceWeightPtr weight;
        double qWeight;
        DocValuesPtr vals;
        TermDocsPtr termDocs;
        int32_t doc;

    protected:
        virtual void mark_members(gc* gc) const
        {
            gc->mark(weight);
            gc->mark(vals);
            gc->mark(termDocs);
            Scorer::mark_members(gc);
        }

    public:
        virtual int32_t nextDoc();
        virtual int32_t docID();
        virtual int32_t advance(int32_t target);
        virtual double score();
    };
}

#endif
