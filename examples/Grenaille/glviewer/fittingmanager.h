#ifndef FITTINGMANAGER_H
#define FITTINGMANAGER_H

#include "Patate/grenaille.h"
#include "Patate/common/gl_utils/glmesh.h"

#include <QObject>

class FittingManager : public QObject
{
    Q_OBJECT
public:
    explicit FittingManager(QObject *parent = 0);

    //! Type of supported fit types, used to generate Baskets.
    //! \warning Must be aligned with UI
    enum FIT_TYPE {
        PLANE_COV,
        SPHERE_ORIENTED,
        UNSUPPORTED
    };

    typedef PatateCommon::GLTri3DMesh Mesh;
    typedef typename Mesh::Scalar Scalar;

    inline void setMesh(Mesh* mesh) { _mesh = mesh; }

signals:
    //! \brief Signal emitted when the basket has been applied to the input data.
    void fitPerformed();

public slots:
    void setBasketType(FIT_TYPE type);
    void setEvaluationPoint(const PatateCommon::GLTri3DMesh::Vector &pos);
    void setScale(float scale);
    void setScale(double scale);
    void fitPrimitive();

private:
    FIT_TYPE _fitType;
    PatateCommon::GLTri3DMesh *_mesh;
    Scalar _scale;
    typename Mesh::Vector _evalPos;
};

namespace fittingmanagerspace {
typedef PatateCommon::GLTri3DMesh::GrenaillePoint MyPoint;

template <FittingManager::FIT_TYPE type>
struct BasketMaker { };

template <>
struct BasketMaker<FittingManager::PLANE_COV>{
    typedef Grenaille::DistWeightFunc<MyPoint,Grenaille::SmoothWeightKernel<MyPoint::Scalar> > WeightFunc;
    typedef Grenaille::Basket<MyPoint,WeightFunc, Grenaille::CompactPlane,
                                                  Grenaille::CovariancePlaneFit> Basket;
};

template <>
struct BasketMaker<FittingManager::SPHERE_ORIENTED>{
    typedef Grenaille::DistWeightFunc<MyPoint,Grenaille::SmoothWeightKernel<MyPoint::Scalar> > WeightFunc;
    typedef Grenaille::Basket<MyPoint,WeightFunc, Grenaille::AlgebraicSphere,
                                                  Grenaille::OrientedSphereFit,
                                                  Grenaille::GLSParam> Basket;
};

} // namespace fittingmanagerspace

#endif // FITTINGMANAGER_H