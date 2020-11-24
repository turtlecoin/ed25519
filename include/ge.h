/**
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/

#ifndef ED25519_GE_H
#define ED25519_GE_H

#include "fe.h"

typedef struct
{
    fe X;
    fe Y;
    fe Z;
} ge_p2;

typedef struct
{
    fe X;
    fe Y;
    fe Z;
    fe T;
} ge_p3;

typedef struct
{
    fe X;
    fe Y;
    fe Z;
    fe T;
} ge_p1p1;

typedef struct
{
    fe yplusx;
    fe yminusx;
    fe xy2d;
} ge_precomp;

typedef struct
{
    fe YplusX;
    fe YminusX;
    fe Z;
    fe T2d;
} ge_cached;

typedef ge_cached ge_dsmp[8];

#endif // ED25519_GE_H
