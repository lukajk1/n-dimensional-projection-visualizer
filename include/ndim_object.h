#pragma once
#ifndef NDIM_OBJECT_H
#define NDIM_OBJECT_H

#include <cstddef>

struct RotationPlane {
    int axis1;        // First axis (0=X, 1=Y, 2=Z, 3=W, 4=V, etc.)
    int axis2;        // Second axis
    float speed;      // Rotation speed (radians per second)
};

struct NDimObjectData {
    // Vertex data
    const float* vertices;
    size_t vertexDataSize;        // sizeof(vertices) in bytes
    int vertexCount;              // Total number of vertices
    int dimensions;                // N (2, 3, 4, 5, 6, 7, etc.)

    // Rotation configuration
    const RotationPlane* defaultRotationPlanes;
    int numRotationPlanes;

    // Metadata
    const char* name;             // "Hypercube", "Simplex", "Cross-Polytope"
    const char* shaderVertPath;
    const char* shaderFragPath;

    // Helper functions
    int numVec4Groups() const { return (dimensions + 3) / 4; }
    int stride() const { return dimensions * sizeof(float); }
    int attributeOffset(int groupIndex) const {
        return groupIndex * 4 * sizeof(float);
    }
};

#endif
