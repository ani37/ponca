#pragma once

#include "./kdTreeNode.h"

#include <Eigen/Eigen>
#include <Eigen/Geometry> // aabb

#include <memory>
#include <vector>

#define PCA_KDTREE_MAX_DEPTH 32
using Scalar = float;

namespace Ponca {

class KdTree
{
public:
    using Vector3Array = std::vector< Eigen::Matrix<SPScalar, 3, 1>>;
    using Aabb = Eigen::AlignedBox<SPScalar, 3>;

    inline KdTree();
    template <typename Range>
    inline KdTree(const Range& points);
    inline KdTree(std::shared_ptr<Vector3Array>& points);
    inline KdTree(std::shared_ptr<Vector3Array>& points, const std::vector<int>& sampling);

    inline void clear();
    inline void build(std::shared_ptr<Vector3Array>& points);
    inline void build(std::shared_ptr<Vector3Array>& points, const std::vector<int>& sampling);
    inline void rebuild(const std::vector<int>& sampling);

    inline bool valid() const;
    inline std::string to_string() const;

    // Accessors ---------------------------------------------------------------
public:
    inline size_t size() const;

    inline const Vector3Array& point_data() const;
    inline       Vector3Array& point_data();

    inline const std::shared_ptr<Vector3Array>& point_ptr() const;
    inline       std::shared_ptr<Vector3Array>& point_ptr();

    inline const std::vector<KdTreeNode>& node_data() const;
    inline       std::vector<KdTreeNode>& node_data();

    inline const std::vector<int>& index_data() const;
    inline       std::vector<int>& index_data();

    // Parameters --------------------------------------------------------------
public:
    inline int min_cell_size() const;
    inline void set_min_cell_size(int min_cell_size);

    // Internal ----------------------------------------------------------------
public:
    inline void build_rec(int node_id, int start, int end, int level);
    inline int partition(int start, int end, int dim, Scalar value);

    // Data --------------------------------------------------------------------
protected:
    std::shared_ptr<Vector3Array>            m_points;
    std::shared_ptr<std::vector<KdTreeNode>> m_nodes;
    std::shared_ptr<std::vector<int>>        m_indices;

    int m_min_cell_size;
};

} // namespace Ponca

#include "./kdTree.hpp"
