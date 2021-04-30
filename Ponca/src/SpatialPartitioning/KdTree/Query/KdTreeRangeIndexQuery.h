/*
 This Source Code Form is subject to the terms of the Mozilla Public
 License, v. 2.0. If a copy of the MPL was not distributed with this
 file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include <PCA/SpacePartitioning/Query/RangeIndexQuery.h>
#include <PCA/SpacePartitioning/KdTree/Query/KdTreeQuery.h>
#include <PCA/SpacePartitioning/KdTree/Iterator/KdTreeRangeIndexIterator.h>

namespace Ponca {

class KdTreeRangeIndexQuery : public KdTreeQuery,
                              public RangeIndexQuery
{
protected:
    friend class KdTreeRangeIndexIterator;

public:
    KdTreeRangeIndexQuery();
    KdTreeRangeIndexQuery(const KdTree* kdtree);
    KdTreeRangeIndexQuery(const KdTree* kdtree, Scalar radius);
    KdTreeRangeIndexQuery(const KdTree* kdtree, Scalar radius, int index);

public:
    KdTreeRangeIndexIterator begin();
    KdTreeRangeIndexIterator end();

protected:
    void initialize(KdTreeRangeIndexIterator& iterator);
    void advance(KdTreeRangeIndexIterator& iterator);
};

}   
