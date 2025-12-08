#include "ndim_object.h"
#include "vertex_data.h"

// 2D Hypercube Construction
RotationPlane hypercube2D_rotations[] = {
    {0, 1, 0.5f}  // XY plane rotation at 0.5 rad/s
};

static float identity2D[4];

NDimObjectData hypercube2D = {
    hypercubeVerts_2D,           // vertices
    hypercubeVerts_2D_size,      // vertexDataSize
    8,                           // vertexCount (2D square has 4 vertices, 4 edges, 8 vertices for GL_LINES)
    2,                           // dimensions
    hypercube2D_rotations,       // defaultRotationPlanes
    1,                           // numRotationPlanes
    identity2D,                  // identityMatrix (will be initialized)
    1.0f,                        // scale
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "2D Hypercube",              // name
    "shaders/2d.v",              // shaderVertPath
    "shaders/fragment.f"         // shaderFragPath
};

// 3D Hypercube Construction
RotationPlane hypercube3D_rotations[] = {
    {0, 1, 0.4f}  // XY plane rotation at 0.4 rad/s
};

static float identity3D[9];

NDimObjectData hypercube3D = {
    hypercubeVerts_3D,           // vertices
    hypercubeVerts_3D_size,      // vertexDataSize
    24,                          // vertexCount (3D cube has 8 vertices, 12 edges, 24 vertices for GL_LINES)
    3,                           // dimensions
    hypercube3D_rotations,       // defaultRotationPlanes
    1,                           // numRotationPlanes
    identity3D,                  // identityMatrix (will be initialized)
    0.65f,                        // scale
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "3D Hypercube",              // name
    "shaders/3d.v",              // shaderVertPath
    "shaders/fragment.f"         // shaderFragPath
};


NDimObjectData simplex3D = {
    simplexVerts_3D,           // vertices
    simplexVerts_3D_size,      // vertexDataSize
    12,                          // vertexCount (3D cube has 8 vertices, 12 edges, 24 vertices for GL_LINES)
    3,                           // dimensions
    hypercube3D_rotations,       // defaultRotationPlanes
    1,                           // numRotationPlanes
    identity3D,                  // identityMatrix (will be initialized)
    0.65f,                        // scale
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "3D Simplex",              // name
    "shaders/3d.v",              // shaderVertPath
    "shaders/fragment.f"         // shaderFragPath
};

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
    1.5f,                        // scale
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
    4.0f,                        // scale
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "5D Hypercube",              // name
    "shaders/5d.v",              // shaderVertPath
    "shaders/fragment.f"         // shaderFragPath
};

// 6D Hypercube Construction
RotationPlane hypercube6D_rotations[] = {
    {1, 3, 0.45f},  // YW plane rotation at 0.45 rad/s
    {0, 4, 0.35f},  // XV plane rotation at 0.35 rad/s
    {2, 5, 0.28f}   // ZU plane rotation at 0.28 rad/s
};

static float identity6D[36];

NDimObjectData hypercube6D = {
    hypercubeVerts_6D,           // vertices
    hypercubeVerts_6D_size,      // vertexDataSize
    384,                         // vertexCount (6D hypercube has 64 vertices, 192 edges, 384 vertices for GL_LINES)
    6,                           // dimensions
    hypercube6D_rotations,       // defaultRotationPlanes
    3,                           // numRotationPlanes
    identity6D,                  // identityMatrix (will be initialized)
    10.0f,                        // scale
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "6D Hypercube",              // name
    "shaders/6d.v",              // shaderVertPath
    "shaders/fragment.f"         // shaderFragPath
};

// 7D Hypercube Construction
RotationPlane hypercube7D_rotations[] = {
    {1, 3, 0.4f},  // YW plane rotation at 0.4 rad/s
    {0, 4, 0.3f},  // XV plane rotation at 0.3 rad/s
    {2, 5, 0.25f}  // ZU plane rotation at 0.25 rad/s
};

static float identity7D[49];

NDimObjectData hypercube7D = {
    hypercubeVerts_7D,           // vertices
    hypercubeVerts_7D_size,      // vertexDataSize
    896,                         // vertexCount (7D hypercube has 128 vertices, 448 edges, 896 vertices for GL_LINES)
    7,                           // dimensions
    hypercube7D_rotations,       // defaultRotationPlanes
    3,                           // numRotationPlanes
    identity7D,                  // identityMatrix (will be initialized)
    25.0f,                        // scale
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "7D Hypercube",              // name
    "shaders/7d.v",              // shaderVertPath
    "shaders/fragment.f"         // shaderFragPath
};

// 8D Hypercube Construction
RotationPlane hypercube8D_rotations[] = {
    {1, 3, 0.38f},  // YW plane rotation at 0.38 rad/s
    {0, 4, 0.28f},  // XV plane rotation at 0.28 rad/s
    {2, 5, 0.23f},  // ZU plane rotation at 0.23 rad/s
    {6, 7, 0.18f}   // New 8D plane rotation at 0.18 rad/s
};

static float identity8D[64];

NDimObjectData hypercube8D = {
    hypercubeVerts_8D,           // vertices
    hypercubeVerts_8D_size,      // vertexDataSize
    2048,                        // vertexCount (8D hypercube has 256 vertices, 1024 edges, 2048 vertices for GL_LINES)
    8,                           // dimensions
    hypercube8D_rotations,       // defaultRotationPlanes
    4,                           // numRotationPlanes
    identity8D,                  // identityMatrix (will be initialized)
    55.0f,                       // scale
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "8D Hypercube",              // name
    "shaders/8d.v",              // shaderVertPath
    "shaders/fragment.f"         // shaderFragPath
};
