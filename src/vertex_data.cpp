#include "vertex_data.h"

float cubeVertices[] = {
    // positions         
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
};

const size_t cubeVertices_size = sizeof(cubeVertices);

float hypercubeVerts_3D[] = {
    // Edge 1 (connects vertex 0 and 1)
    -1.0000f, -1.0000f, -1.0000f,
    1.0000f, -1.0000f, -1.0000f,

    // Edge 2 (connects vertex 0 and 2)
    -1.0000f, -1.0000f, -1.0000f,
    -1.0000f, 1.0000f, -1.0000f,

    // Edge 3 (connects vertex 0 and 4)
    -1.0000f, -1.0000f, -1.0000f,
    -1.0000f, -1.0000f, 1.0000f,

    // Edge 4 (connects vertex 1 and 3)
    1.0000f, -1.0000f, -1.0000f,
    1.0000f, 1.0000f, -1.0000f,

    // Edge 5 (connects vertex 1 and 5)
    1.0000f, -1.0000f, -1.0000f,
    1.0000f, -1.0000f, 1.0000f,

    // Edge 6 (connects vertex 2 and 3)
    -1.0000f, 1.0000f, -1.0000f,
    1.0000f, 1.0000f, -1.0000f,

    // Edge 7 (connects vertex 2 and 6)
    -1.0000f, 1.0000f, -1.0000f,
    -1.0000f, 1.0000f, 1.0000f,

    // Edge 8 (connects vertex 3 and 7)
    1.0000f, 1.0000f, -1.0000f,
    1.0000f, 1.0000f, 1.0000f,

    // Edge 9 (connects vertex 4 and 5)
    -1.0000f, -1.0000f, 1.0000f,
    1.0000f, -1.0000f, 1.0000f,

    // Edge 10 (connects vertex 4 and 6)
    -1.0000f, -1.0000f, 1.0000f,
    -1.0000f, 1.0000f, 1.0000f,

    // Edge 11 (connects vertex 5 and 7)
    1.0000f, -1.0000f, 1.0000f,
    1.0000f, 1.0000f, 1.0000f,

    // Edge 12 (connects vertex 6 and 7)
    -1.0000f, 1.0000f, 1.0000f,
    1.0000f, 1.0000f, 1.0000f,

};
const size_t hypercubeVerts_3D_size = sizeof(hypercubeVerts_3D);

float hypercubeVerts_4D[] = {
    // Edge 1 (connects vertex 0 and 1)
    -1.0000f, -1.0000f, -1.0000f, -1.0000f,
    1.0000f, -1.0000f, -1.0000f, -1.0000f,

    // Edge 2 (connects vertex 0 and 2)
    -1.0000f, -1.0000f, -1.0000f, -1.0000f,
    -1.0000f, 1.0000f, -1.0000f, -1.0000f,

    // Edge 3 (connects vertex 0 and 4)
    -1.0000f, -1.0000f, -1.0000f, -1.0000f,
    -1.0000f, -1.0000f, 1.0000f, -1.0000f,

    // Edge 4 (connects vertex 0 and 8)
    -1.0000f, -1.0000f, -1.0000f, -1.0000f,
    -1.0000f, -1.0000f, -1.0000f, 1.0000f,

    // Edge 5 (connects vertex 1 and 3)
    1.0000f, -1.0000f, -1.0000f, -1.0000f,
    1.0000f, 1.0000f, -1.0000f, -1.0000f,

    // Edge 6 (connects vertex 1 and 5)
    1.0000f, -1.0000f, -1.0000f, -1.0000f,
    1.0000f, -1.0000f, 1.0000f, -1.0000f,

    // Edge 7 (connects vertex 1 and 9)
    1.0000f, -1.0000f, -1.0000f, -1.0000f,
    1.0000f, -1.0000f, -1.0000f, 1.0000f,

    // Edge 8 (connects vertex 2 and 3)
    -1.0000f, 1.0000f, -1.0000f, -1.0000f,
    1.0000f, 1.0000f, -1.0000f, -1.0000f,

    // Edge 9 (connects vertex 2 and 6)
    -1.0000f, 1.0000f, -1.0000f, -1.0000f,
    -1.0000f, 1.0000f, 1.0000f, -1.0000f,

    // Edge 10 (connects vertex 2 and 10)
    -1.0000f, 1.0000f, -1.0000f, -1.0000f,
    -1.0000f, 1.0000f, -1.0000f, 1.0000f,

    // Edge 11 (connects vertex 3 and 7)
    1.0000f, 1.0000f, -1.0000f, -1.0000f,
    1.0000f, 1.0000f, 1.0000f, -1.0000f,

    // Edge 12 (connects vertex 3 and 11)
    1.0000f, 1.0000f, -1.0000f, -1.0000f,
    1.0000f, 1.0000f, -1.0000f, 1.0000f,

    // Edge 13 (connects vertex 4 and 5)
    -1.0000f, -1.0000f, 1.0000f, -1.0000f,
    1.0000f, -1.0000f, 1.0000f, -1.0000f,

    // Edge 14 (connects vertex 4 and 6)
    -1.0000f, -1.0000f, 1.0000f, -1.0000f,
    -1.0000f, 1.0000f, 1.0000f, -1.0000f,

    // Edge 15 (connects vertex 4 and 12)
    -1.0000f, -1.0000f, 1.0000f, -1.0000f,
    -1.0000f, -1.0000f, 1.0000f, 1.0000f,

    // Edge 16 (connects vertex 5 and 7)
    1.0000f, -1.0000f, 1.0000f, -1.0000f,
    1.0000f, 1.0000f, 1.0000f, -1.0000f,

    // Edge 17 (connects vertex 5 and 13)
    1.0000f, -1.0000f, 1.0000f, -1.0000f,
    1.0000f, -1.0000f, 1.0000f, 1.0000f,

    // Edge 18 (connects vertex 6 and 7)
    -1.0000f, 1.0000f, 1.0000f, -1.0000f,
    1.0000f, 1.0000f, 1.0000f, -1.0000f,

    // Edge 19 (connects vertex 6 and 14)
    -1.0000f, 1.0000f, 1.0000f, -1.0000f,
    -1.0000f, 1.0000f, 1.0000f, 1.0000f,

    // Edge 20 (connects vertex 7 and 15)
    1.0000f, 1.0000f, 1.0000f, -1.0000f,
    1.0000f, 1.0000f, 1.0000f, 1.0000f,

    // Edge 21 (connects vertex 8 and 9)
    -1.0000f, -1.0000f, -1.0000f, 1.0000f,
    1.0000f, -1.0000f, -1.0000f, 1.0000f,

    // Edge 22 (connects vertex 8 and 10)
    -1.0000f, -1.0000f, -1.0000f, 1.0000f,
    -1.0000f, 1.0000f, -1.0000f, 1.0000f,

    // Edge 23 (connects vertex 8 and 12)
    -1.0000f, -1.0000f, -1.0000f, 1.0000f,
    -1.0000f, -1.0000f, 1.0000f, 1.0000f,

    // Edge 24 (connects vertex 9 and 11)
    1.0000f, -1.0000f, -1.0000f, 1.0000f,
    1.0000f, 1.0000f, -1.0000f, 1.0000f,

    // Edge 25 (connects vertex 9 and 13)
    1.0000f, -1.0000f, -1.0000f, 1.0000f,
    1.0000f, -1.0000f, 1.0000f, 1.0000f,

    // Edge 26 (connects vertex 10 and 11)
    -1.0000f, 1.0000f, -1.0000f, 1.0000f,
    1.0000f, 1.0000f, -1.0000f, 1.0000f,

    // Edge 27 (connects vertex 10 and 14)
    -1.0000f, 1.0000f, -1.0000f, 1.0000f,
    -1.0000f, 1.0000f, 1.0000f, 1.0000f,

    // Edge 28 (connects vertex 11 and 15)
    1.0000f, 1.0000f, -1.0000f, 1.0000f,
    1.0000f, 1.0000f, 1.0000f, 1.0000f,

    // Edge 29 (connects vertex 12 and 13)
    -1.0000f, -1.0000f, 1.0000f, 1.0000f,
    1.0000f, -1.0000f, 1.0000f, 1.0000f,

    // Edge 30 (connects vertex 12 and 14)
    -1.0000f, -1.0000f, 1.0000f, 1.0000f,
    -1.0000f, 1.0000f, 1.0000f, 1.0000f,

    // Edge 31 (connects vertex 13 and 15)
    1.0000f, -1.0000f, 1.0000f, 1.0000f,
    1.0000f, 1.0000f, 1.0000f, 1.0000f,

    // Edge 32 (connects vertex 14 and 15)
    -1.0000f, 1.0000f, 1.0000f, 1.0000f,
    1.0000f, 1.0000f, 1.0000f, 1.0000f,

};
const size_t hypercubeVerts_4D_size = sizeof(hypercubeVerts_4D);