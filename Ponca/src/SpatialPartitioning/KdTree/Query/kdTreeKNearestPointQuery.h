/*
 This Source Code Form is subject to the terms of the Mozilla Public
 License, v. 2.0. If a copy of the MPL was not distributed with this
 file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include "../Iterator/KdTreeKNearestPointIterator.h"

#include "../iterator.h"

#include "../kdTree.h"

#include "../../query.h"

namespace Ponca {

template <typename _VectorType>
struct KdTreeKNearestPointQuery : public KdTreeQuery, public KNearestPointQuery<_VectorType>
{
    using VectorType = typename KNearestPointQuery<_VectorType>::VectorType;

    KdTreeKNearestPointQuery();
    KdTreeKNearestPointQuery(const KdTree* kdtree, int k);
    KdTreeKNearestPointQuery(const KdTree* kdtree, int k, const VectorType& point);

public:
    KdTreeKNearestPointIterator begin();
    KdTreeKNearestPointIterator end();

protected:
    void search();
};

} // namespace Ponca

#include "./kdTreeKNearestPointQuery.hpp"
