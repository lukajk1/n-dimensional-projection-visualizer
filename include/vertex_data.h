#pragma once

#include <cstddef>

// Using extern tells the compiler that this variable is defined in another source file.
extern float cubeVertices[];

// We also provide the size of the array in bytes, since sizeof() won't work on an extern array.
extern const size_t cubeVertices_size;
