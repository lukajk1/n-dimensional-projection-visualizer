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
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "2D Hypercube",              // name
    "shaders/2d.v",              // shaderVertPath
    "shaders/ws-coloring.f"         // shaderFragPath
};

// 2D Simplex Construction
static float identity2D_simplex[4];

NDimObjectData simplex2D = {
    simplexVerts_2D,           // vertices
    simplexVerts_2D_size,      // vertexDataSize
    6,                           // vertexCount (2D simplex/triangle has 3 vertices, 3 edges, 6 vertices for GL_LINES)
    2,                           // dimensions
    hypercube2D_rotations,       // defaultRotationPlanes
    1,                           // numRotationPlanes
    identity2D_simplex,          // identityMatrix (will be initialized)
    1.0f,                        // scale
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "2D Simplex",              // name
    "shaders/2d.v",              // shaderVertPath
    "shaders/ws-coloring.f"         // shaderFragPath
};

// 2D Cross-Polytope Construction
static float identity2D_cross[4];

NDimObjectData crossPolytope2D = {
    crossPolytopeVerts_2D,       // vertices
    crossPolytopeVerts_2D_size,  // vertexDataSize
    8,                           // vertexCount (2D cross-polytope has 4 vertices, 4 edges, 8 vertices for GL_LINES)
    2,                           // dimensions
    hypercube2D_rotations,       // defaultRotationPlanes
    1,                           // numRotationPlanes
    identity2D_cross,            // identityMatrix (will be initialized)
    1.0f,                        // scale
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "2D Cross-Polytope",         // name
    "shaders/2d.v",              // shaderVertPath
    "shaders/ws-coloring.f"      // shaderFragPath
};

// 3D Hypercube Construction
RotationPlane hypercube3D_rotations[] = {
    {0, 1, 0.4f}  // XY plane rotation at 0.4 rad/s
};
// 3D Cross-Polytope Construction
static float identity3D_cross[9];

NDimObjectData crossPolytope3D = {
    crossPolytopeVerts_3D,       // vertices
    crossPolytopeVerts_3D_size,  // vertexDataSize
    24,                          // vertexCount (3D cross-polytope has 6 vertices, 12 edges, 24 vertices for GL_LINES)
    3,                           // dimensions
    hypercube3D_rotations,       // defaultRotationPlanes
    1,                           // numRotationPlanes
    identity3D_cross,            // identityMatrix (will be initialized)
    1.2f,                        // scale
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "3D Cross-Polytope",         // name
    "shaders/3d.v",              // shaderVertPath
    "shaders/ws-coloring.f"      // shaderFragPath
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
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "3D Hypercube",              // name
    "shaders/3d.v",              // shaderVertPath
    "shaders/ws-coloring.f"         // shaderFragPath
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
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "4D Hypercube",              // name
    "shaders/4d.v",            // shaderVertPath
    "shaders/ws-coloring.f"         // shaderFragPath
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
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "5D Hypercube",              // name
    "shaders/5d.v",              // shaderVertPath
    "shaders/ws-coloring.f"         // shaderFragPath
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
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "6D Hypercube",              // name
    "shaders/6d.v",              // shaderVertPath
    "shaders/ws-coloring.f"         // shaderFragPath
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
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "7D Hypercube",              // name
    "shaders/7d.v",              // shaderVertPath
    "shaders/ws-coloring.f"         // shaderFragPath
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
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "8D Hypercube",              // name
    "shaders/8d.v",              // shaderVertPath
    "shaders/ws-coloring.f"         // shaderFragPath
};

NDimObjectData simplex3D = {
    simplexVerts_3D,           // vertices
    simplexVerts_3D_size,      // vertexDataSize
    12,                          // vertexCount (3D simplex has 4 vertices, 6 edges, 12 vertices for GL_LINES)
    3,                           // dimensions
    hypercube3D_rotations,       // defaultRotationPlanes
    1,                           // numRotationPlanes
    identity3D,                  // identityMatrix (will be initialized)
    1.2f,                        // scale
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "3D Simplex",              // name
    "shaders/3d.v",              // shaderVertPath
    "shaders/ws-coloring.f"         // shaderFragPath
};

// 4D Simplex Construction
static float identity4D_simplex[16];

NDimObjectData simplex4D = {
    simplexVerts_4D,           // vertices
    simplexVerts_4D_size,      // vertexDataSize
    20,                          // vertexCount (4D simplex has 5 vertices, 10 edges, 20 vertices for GL_LINES)
    4,                           // dimensions
    hypercube4D_rotations,       // defaultRotationPlanes
    1,                           // numRotationPlanes
    identity4D_simplex,          // identityMatrix (will be initialized)
    3.5f,                        // scale
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "4D Simplex",              // name
    "shaders/4d.v",              // shaderVertPath
    "shaders/ws-coloring.f"         // shaderFragPath
};

// 5D Simplex Construction
static float identity5D_simplex[25];

NDimObjectData simplex5D = {
    simplexVerts_5D,           // vertices
    simplexVerts_5D_size,      // vertexDataSize
    30,                          // vertexCount (5D simplex has 6 vertices, 15 edges, 30 vertices for GL_LINES)
    5,                           // dimensions
    hypercube5D_rotations,       // defaultRotationPlanes
    2,                           // numRotationPlanes
    identity5D_simplex,          // identityMatrix (will be initialized)
    8.0f,                        // scale
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "5D Simplex",              // name
    "shaders/5d.v",              // shaderVertPath
    "shaders/ws-coloring.f"         // shaderFragPath
};

// 6D Simplex Construction
static float identity6D_simplex[36];

NDimObjectData simplex6D = {
    simplexVerts_6D,           // vertices
    simplexVerts_6D_size,      // vertexDataSize
    42,                          // vertexCount (6D simplex has 7 vertices, 21 edges, 42 vertices for GL_LINES)
    6,                           // dimensions
    hypercube6D_rotations,       // defaultRotationPlanes
    3,                           // numRotationPlanes
    identity6D_simplex,          // identityMatrix (will be initialized)
    30.0f,                        // scale
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "6D Simplex",              // name
    "shaders/6d.v",              // shaderVertPath
    "shaders/ws-coloring.f"         // shaderFragPath
};

// 7D Simplex Construction
static float identity7D_simplex[49];

NDimObjectData simplex7D = {
    simplexVerts_7D,           // vertices
    simplexVerts_7D_size,      // vertexDataSize
    56,                          // vertexCount (7D simplex has 8 vertices, 28 edges, 56 vertices for GL_LINES)
    7,                           // dimensions
    hypercube7D_rotations,       // defaultRotationPlanes
    3,                           // numRotationPlanes
    identity7D_simplex,          // identityMatrix (will be initialized)
    35.0f,                       // scale
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "7D Simplex",              // name
    "shaders/7d.v",              // shaderVertPath
    "shaders/ws-coloring.f"         // shaderFragPath
};

// 8D Simplex Construction
static float identity8D_simplex[64];

NDimObjectData simplex8D = {
    simplexVerts_8D,           // vertices
    simplexVerts_8D_size,      // vertexDataSize
    72,                          // vertexCount (8D simplex has 9 vertices, 36 edges, 72 vertices for GL_LINES)
    8,                           // dimensions
    hypercube8D_rotations,       // defaultRotationPlanes
    4,                           // numRotationPlanes
    identity8D_simplex,          // identityMatrix (will be initialized)
    300.0f,                       // scale
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "8D Simplex",              // name
    "shaders/8d.v",              // shaderVertPath
    "shaders/ws-coloring.f"         // shaderFragPath
};

// 4D Cross-Polytope Construction
static float identity4D_cross[16];

NDimObjectData crossPolytope4D = {
    crossPolytopeVerts_4D,       // vertices
    crossPolytopeVerts_4D_size,  // vertexDataSize
    48,                          // vertexCount (4D cross-polytope has 8 vertices, 24 edges, 48 vertices for GL_LINES)
    4,                           // dimensions
    hypercube4D_rotations,       // defaultRotationPlanes
    1,                           // numRotationPlanes
    identity4D_cross,            // identityMatrix (will be initialized)
    3.5f,                        // scale
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "4D Cross-Polytope",         // name
    "shaders/4d.v",              // shaderVertPath
    "shaders/ws-coloring.f"      // shaderFragPath
};

// 5D Cross-Polytope Construction
static float identity5D_cross[25];

NDimObjectData crossPolytope5D = {
    crossPolytopeVerts_5D,       // vertices
    crossPolytopeVerts_5D_size,  // vertexDataSize
    80,                          // vertexCount (5D cross-polytope has 10 vertices, 40 edges, 80 vertices for GL_LINES)
    5,                           // dimensions
    hypercube5D_rotations,       // defaultRotationPlanes
    2,                           // numRotationPlanes
    identity5D_cross,            // identityMatrix (will be initialized)
    8.0f,                        // scale
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "5D Cross-Polytope",         // name
    "shaders/5d.v",              // shaderVertPath
    "shaders/ws-coloring.f"      // shaderFragPath
};

// 6D Cross-Polytope Construction
static float identity6D_cross[36];

NDimObjectData crossPolytope6D = {
    crossPolytopeVerts_6D,       // vertices
    crossPolytopeVerts_6D_size,  // vertexDataSize
    132,                         // vertexCount (6D cross-polytope has 12 vertices, 66 edges, 132 vertices for GL_LINES)
    6,                           // dimensions
    hypercube6D_rotations,       // defaultRotationPlanes
    3,                           // numRotationPlanes
    identity6D_cross,            // identityMatrix (will be initialized)
    30.0f,                       // scale
        true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "6D Cross-Polytope",         // name
    "shaders/6d.v",              // shaderVertPath
    "shaders/ws-coloring.f"      // shaderFragPath
};

// 7D Cross-Polytope Construction
static float identity7D_cross[49];

NDimObjectData crossPolytope7D = {
    crossPolytopeVerts_7D,       // vertices
    crossPolytopeVerts_7D_size,  // vertexDataSize
    196,                         // vertexCount (7D cross-polytope has 14 vertices, 98 edges, 196 vertices for GL_LINES)
    7,                           // dimensions
    hypercube7D_rotations,       // defaultRotationPlanes
    3,                           // numRotationPlanes
    identity7D_cross,            // identityMatrix (will be initialized)
    35.0f,                       // scale
    true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "7D Cross-Polytope",         // name
    "shaders/7d.v",              // shaderVertPath
    "shaders/ws-coloring.f"      // shaderFragPath
};

// 8D Cross-Polytope Construction
static float identity8D_cross[64];

NDimObjectData crossPolytope8D = {
    crossPolytopeVerts_8D,       // vertices
    crossPolytopeVerts_8D_size,  // vertexDataSize
    272,                         // vertexCount (8D cross-polytope has 16 vertices, 136 edges, 272 vertices for GL_LINES)
    8,                           // dimensions
    hypercube8D_rotations,       // defaultRotationPlanes
    4,                           // numRotationPlanes
    identity8D_cross,            // identityMatrix (will be initialized)
    300.0f,                      // scale
        true,                        // renderEdges
    0,                           // VAO (will be set by setupBuffers)
    0,                           // VBO (will be set by setupBuffers)
    nullptr,                     // shader (will be initialized by initShader)
    "8D Cross-Polytope",         // name
    "shaders/8d.v",              // shaderVertPath
    "shaders/ws-coloring.f"      // shaderFragPath
};
