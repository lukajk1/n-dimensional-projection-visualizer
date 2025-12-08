#include "ndim_object.h"
#include "vertex_data.h"

// 4D Hypercube Construction
RotationPlane hypercube4D_rotations[] = {
    {1, 3, 0.7f}  // YW plane rotation at 0.7 rad/s
};

static float identity4D[16];

NDimObjectData hypercube4D = {
    hypercubeVerts_4D,           // vertices
    hypercubeVerts_4D_size,      // vertexDataSize
    64,                          // vertexCount (4D hypercube has 16 vertices, 32 edges, 64 vertices for GL_LINES)
    4,                           // dimensions
    hypercube4D_rotations,       // defaultRotationPlanes
    1,                           // numRotationPlanes
    identity4D,                  // identityMatrix (will be initialized)
    1.0f,                        // scale
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "4D Hypercube",              // name
    "shaders/4d.v",            // shaderVertPath
    "shaders/fragment.f"         // shaderFragPath
};

// 5D Hypercube Construction
RotationPlane hypercube5D_rotations[] = {
    {1, 3, 0.5f},  // YW plane rotation at 0.5 rad/s
    {0, 4, 0.3f}   // XV plane rotation at 0.3 rad/s
};

static float identity5D[25];

NDimObjectData hypercube5D = {
    hypercubeVerts_5D,           // vertices
    hypercubeVerts_5D_size,      // vertexDataSize
    160,                         // vertexCount (5D hypercube has 32 vertices, 80 edges, 160 vertices for GL_LINES)
    5,                           // dimensions
    hypercube5D_rotations,       // defaultRotationPlanes
    2,                           // numRotationPlanes
    identity5D,                  // identityMatrix (will be initialized)
    1.3f,                        // scale
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "5D Hypercube",              // name
    "shaders/5d.v",              // shaderVertPath
    "shaders/fragment.f"         // shaderFragPath
};
