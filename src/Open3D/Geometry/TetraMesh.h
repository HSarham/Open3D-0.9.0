// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2019 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#pragma once

#include <Eigen/Core>
#include <Eigen/StdVector>
#include <memory>
#include <vector>

#include "Open3D/Geometry/MeshBase.h"
#include "Open3D/Utility/Eigen.h"
#include "Open3D/Utility/Helper.h"

namespace open3d {
namespace geometry {

class PointCloud;
class TriangleMesh;

class TetraMesh : public MeshBase {
public:
    TetraMesh() : MeshBase(Geometry::GeometryType::TetraMesh) {}
    TetraMesh(const std::vector<Eigen::Vector3d> &vertices,
              const std::vector<Eigen::Vector4i, utility::Vector4i_allocator>
                      &tetras)
        : MeshBase(Geometry::GeometryType::TetraMesh, vertices),
          tetras_(tetras) {}
    ~TetraMesh() override {}

public:
    TetraMesh &Clear() override;

public:
    TetraMesh &operator+=(const TetraMesh &mesh);
    TetraMesh operator+(const TetraMesh &mesh) const;

    /// Function that removes duplicated verties, i.e., vertices that have
    /// identical coordinates.
    TetraMesh &RemoveDuplicatedVertices();

    /// Function that removes duplicated tetrahedra, i.e., removes tetrahedra
    /// that reference the same four vertices, independent of their order.
    TetraMesh &RemoveDuplicatedTetras();

    /// This function removes vertices from the tetra mesh that are not
    /// referenced in any tetrahedron of the mesh.
    TetraMesh &RemoveUnreferencedVertices();

    /// Function that removes degenerate tetrahedra, i.e., tetrahedra that
    /// reference a single vertex multiple times in a single tetrahedron.
    /// They are usually the product of removing duplicated vertices.
    TetraMesh &RemoveDegenerateTetras();

    bool HasTetras() const {
        return vertices_.size() > 0 && tetras_.size() > 0;
    }

    /// Function to extract a triangle mesh of the specified iso-surface at
    /// \param level. \param values are values per-vertex.
    /// This method applies primal contouring and generates triangles for each
    /// tetrahedron.
    std::shared_ptr<TriangleMesh> ExtractTriangleMesh(
            const std::vector<double> &values, double level);

    /// Function that creates a tetrahedral mesh (TetraMeshFactory.cpp).
    /// from a point cloud. The method creates the Delaunay triangulation
    /// using the implementation from Qhull.
    static std::tuple<std::shared_ptr<TetraMesh>, std::vector<size_t>>
    CreateFromPointCloud(const PointCloud &point_cloud);

protected:
    // Forward child class type to avoid indirect nonvirtual base
    TetraMesh(Geometry::GeometryType type) : MeshBase(type) {}

public:
    std::vector<Eigen::Vector4i, utility::Vector4i_allocator> tetras_;
};

}  // namespace geometry
}  // namespace open3d
