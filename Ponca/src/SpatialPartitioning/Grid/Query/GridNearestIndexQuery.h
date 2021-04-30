#pragma once

#include <PCA/SpacePartitioning/Query/NearestIndexQuery.h>
#include <PCA/SpacePartitioning/Grid/Query/GridQuery.h>
#include <PCA/SpacePartitioning/Grid/Iterator/GridNearestIndexIterator.h>

namespace pca {

class GridNearestIndexQuery : public GridQuery,
                              public NearestIndexQuery
{
public:
    GridNearestIndexQuery();
    GridNearestIndexQuery(const Grid* grid);
    GridNearestIndexQuery(const Grid* grid, int index);

public:
    GridNearestIndexIterator begin();
    GridNearestIndexIterator end();

protected:
    void search();
};

} // namespace pca
