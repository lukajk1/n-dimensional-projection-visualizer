#pragma once
#include <cstddef>

// Using extern tells the compiler that this variable is defined in another source file.
extern float cubeVertices[];


// We also provide the size of the array in bytes, since sizeof() won't work on an extern array.

extern float hypercubeVerts_2D[];
extern const size_t hypercubeVerts_2D_size;

extern float hypercubeVerts_3D[];
extern const size_t hypercubeVerts_3D_size;

extern float simplexVerts_3D[];
extern const size_t simplexVerts_3D_size;

extern float hypercubeVerts_4D[];
extern const size_t hypercubeVerts_4D_size;

extern float hypercubeVerts_5D[];
extern const size_t hypercubeVerts_5D_size;

extern float hypercubeVerts_6D[];
extern const size_t hypercubeVerts_6D_size;

extern float hypercubeVerts_7D[];
extern const size_t hypercubeVerts_7D_size;

extern float hypercubeVerts_8D[];
extern const size_t hypercubeVerts_8D_size;
