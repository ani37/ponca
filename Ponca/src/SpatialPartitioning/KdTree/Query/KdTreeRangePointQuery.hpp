/*
 This Source Code Form is subject to the terms of the Mozilla Public
 License, v. 2.0. If a copy of the MPL was not distributed with this
 file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "./KdTreeRangePointQuery.h"
#include "../kdTree.h"

class KdTree;

namespace Ponca {
template <typename VectorType>
KdTreeRangePointQuery<VectorType>::KdTreeRangePointQuery() :
    KdTreeQuery(),
    RangePointQuery<VectorType>()
{
    cout << "Test" << endl;
}

template <typename VectorType>
KdTreeRangePointQuery<VectorType>::KdTreeRangePointQuery(const KdTree* kdtree) :
    KdTreeQuery(kdtree),
    RangePointQuery<VectorType>()
{
}

template <typename VectorType>
KdTreeRangePointQuery<VectorType>::KdTreeRangePointQuery(const KdTree* kdtree, Scalar radius) :
    KdTreeQuery(kdtree),
    RangePointQuery<VectorType>(radius)
{
}

template <typename VectorType>
KdTreeRangePointQuery<VectorType>::KdTreeRangePointQuery(const KdTree* kdtree, Scalar radius, const VectorType& point) :
    KdTreeQuery(kdtree),
    RangePointQuery<VectorType>(radius, point)
{
}

template <typename VectorType>
KdTreeRangePointIterator<typename RangePointQuery<VectorType>::VectorType> KdTreeRangePointQuery<VectorType>::begin()
{
    KdTreeRangePointIterator<VectorType> it(this);
    this->initialize(it);
    this->advance(it);
    return it;
}

template <typename VectorType>
KdTreeRangePointIterator<typename RangePointQuery<VectorType>::VectorType> KdTreeRangePointQuery<VectorType>::end()
{
    return KdTreeRangePointIterator<VectorType>(this, static_cast<int>(m_kdtree->size()));
}

template <typename VectorType>
void KdTreeRangePointQuery<VectorType>::initialize(KdTreeRangePointIterator<VectorType>& it)
{
    m_stack.clear();
    m_stack.push();
    m_stack.top().index = 0;
    m_stack.top().squared_distance = 0;
    it.m_index = -1;
    it.m_start = 0;
    it.m_end   = 0;
}

template <typename VectorType>
void KdTreeRangePointQuery<VectorType>::advance(KdTreeRangePointIterator<VectorType>& it)
{
    const auto& nodes   = m_kdtree->node_data();
    const auto& points  = m_kdtree->point_data();
    const auto& indices = m_kdtree->index_data();

    for(int i=it.m_start; i<it.m_end; ++i)
    {
        int idx = indices[i];

        Scalar d = (m_point - points[idx]).squaredNorm();
        if(d < m_squared_radius)
        {
            it.m_index = idx;
            it.m_start = i+1;
            return;
        }
    }

    while(!m_stack.empty())
    {
        auto& qnode = m_stack.top();
        const auto& node = nodes[qnode.index];

        if(qnode.squared_distance < m_squared_radius)
        {
            if(node.leaf)
            {
                m_stack.pop();
                it.m_start = node.start;
                it.m_end   = node.start + node.size;
                for(int i=it.m_start; i<it.m_end; ++i)
                {
                    int idx = indices[i];

                    Scalar d = (m_point - points[idx]).squaredNorm();
                    if(d < m_squared_radius)
                    {
                        it.m_index = idx;
                        it.m_start = i+1;
                        return;
                    }
                }
            }
            else
            {
                // replace the stack top by the farthest and push the closest
                Scalar newOff = m_point[node.dim] - node.splitValue;
                m_stack.push();
                if(newOff < 0)
                {
                    m_stack.top().index = node.firstChildId;
                    qnode.index         = node.firstChildId+1;
                }
                else
                {
                    m_stack.top().index = node.firstChildId+1;
                    qnode.index         = node.firstChildId;
                }
                m_stack.top().squared_distance = qnode.squared_distance;
                qnode.squared_distance         = newOff*newOff;
            }
        }
        else
        {
            m_stack.pop();
        }
    }
    it.m_index = points.size();
}

} // namespace ponca