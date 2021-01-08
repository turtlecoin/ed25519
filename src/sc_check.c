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

#include "sc_check.h"

int sc_check(const unsigned char *s)
{
    int64_t t[8];
    int i;

    for (i = 0; i < 8; i++)
    {
        t[i] = load_4(s + (i * 4));
    }

    return (
        int)((signum(1559614444 - t[0]) + (signum(1477600026 - t[1]) << 1) + (signum(2734136534 - t[2]) << 2) + (signum(350157278 - t[3]) << 3) + (signum(-t[4]) << 4) + (signum(-t[5]) << 5) + (signum(-t[6]) << 6) + (signum(268435456 - t[7]) << 7)) >> 8);
}