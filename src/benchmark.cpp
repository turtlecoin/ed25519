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

#include <chrono>
#include <iomanip>
#include <iostream>

extern "C"
{
#include "ed25519.h"
}

#define PERFORMANCE_ITERATIONS 5000

template<typename T>
void benchmark(T &&function, const std::string &functionName, uint64_t iterations = PERFORMANCE_ITERATIONS)
{
    std::cout << std::setw(40) << functionName << ": ";

    auto tenth = iterations / 10;

    auto startTimer = std::chrono::high_resolution_clock::now();

    for (uint64_t i = 0; i < iterations; ++i)
    {
        if (i % tenth == 0)
            std::cout << ".";

        function();
    }

    auto elapsedTime =
        std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startTimer)
            .count();

    auto timePer = elapsedTime / iterations;

    std::cout << "  " << std::setprecision(5) << std::setw(10) << timePer / 1000.0 << " ms" << std::endl;
}

int main()
{
    std::cout << "Benchmark Timings" << std::endl << std::endl;

    const uint8_t G[32] = {0x58, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
                           0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
                           0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66};

    const uint8_t scalar[32] = {0x31, 0x3b, 0x08, 0x3f, 0x84, 0x28, 0x2b, 0x00, 0xb9, 0xc8, 0x4f,
                                0x4c, 0xf4, 0x39, 0x24, 0xf6, 0x61, 0x27, 0xf5, 0xd2, 0x77, 0x2f,
                                0xdf, 0x36, 0x11, 0x09, 0x56, 0xa8, 0xda, 0xd5, 0x98, 0x04};

    ge_p3 G_point3;

    ge_p2 G_point2;

    ge_cached G_cached;

    ge_p1p1 G_p1p1;

    ge_frombytes_negate_vartime(&G_point3, G);

    ge_fromfe_frombytes_negate_vartime(&G_point2, G);

    ge_p3_to_cached(&G_cached, &G_point3);

    ge_add(&G_p1p1, &G_point3, &G_cached);

    std::cout << "Point Operations" << std::endl << std::endl;

    benchmark(
        [&G]() {
            ge_p3 point;

            ge_frombytes_negate_vartime(&point, G);
        },
        "ge_frombytes_negate_vartime");

    benchmark(
        [&G_point3]() {
            uint8_t bytes[32];

            ge_p3_tobytes(reinterpret_cast<unsigned char *>(&bytes), &G_point3);
        },
        "ge_p3_tobytes");

    benchmark(
        [&G_point3]() {
            ge_p2 point;

            ge_p3_to_p2(&point, &G_point3);
        },
        "ge_p3_to_p2");

    benchmark(
        [&G_point3]() {
            ge_cached point;

            ge_p3_to_cached(&point, &G_point3);
        },
        "ge_p3_to_cached");

    benchmark(
        [&G]() {
            ge_p2 point;

            ge_fromfe_frombytes_negate_vartime(&point, G);
        },
        "ge_fromfe_frombytes_negate_vartime");

    benchmark(
        [&G_point2]() {
            uint8_t bytes[32];

            ge_tobytes(reinterpret_cast<unsigned char *>(&bytes), &G_point2);
        },
        "ge_tobytes");

    benchmark(
        [&G_p1p1]() {
            ge_p2 point;

            ge_p1p1_to_p2(&point, &G_p1p1);
        },
        "ge_p1p1_to_p2");

    benchmark(
        [&G_p1p1]() {
            ge_p3 point;

            ge_p1p1_to_p3(&point, &G_p1p1);
        },
        "ge_p1p1_to_p3");

    benchmark(
        [&G_point3, &G_cached]() {
            ge_p1p1 point;

            ge_add(&point, &G_point3, &G_cached);
        },
        "ge_add");

    benchmark(
        [&G_point3, &G_cached]() {
            ge_p1p1 point;

            ge_sub(&point, &G_point3, &G_cached);
        },
        "ge_sub");

    benchmark(
        [&G_point2]() {
            ge_p1p1 point;

            ge_mul8(&point, &G_point2);
        },
        "ge_mul8");

    benchmark(
        [&G_point2]() {
            ge_p1p1 point;

            ge_p2_dbl(&point, &G_point2);
        },
        "ge_p3_dbl");

    benchmark(
        [&G_point3]() {
            ge_p1p1 point;

            ge_p3_dbl(&point, &G_point3);
        },
        "ge_p3_dbl");

    benchmark(
        [&scalar]() {
            ge_p3 point;

            ge_scalarmult_base(&point, scalar);
        },
        "ge_scalarmult_base");

    benchmark(
        [&G_point3, &scalar]() {
            ge_p2 point;

            ge_scalarmult(&point, scalar, &G_point3);
        },
        "ge_scalarmult");

    benchmark(
        [&G_point3, &scalar]() {
            ge_p2 point;

            ge_double_scalarmult_base_negate_vartime(&point, scalar, &G_point3, scalar);
        },
        "ge_double_scalarmult_base");

    benchmark(
        [&G_point3, &scalar, &G_cached]() {
            ge_p2 point;

            ge_double_scalarmult_negate_vartime(&point, scalar, &G_point3, scalar, &G_cached);
        },
        "ge_double_scalarmult");

    std::cout << std::endl << "Scalar Operations" << std::endl << std::endl;

    benchmark(
        [&scalar]() {
            unsigned char bytes[32];

            sc_add(bytes, scalar, scalar);
        },
        "sc_add");

    benchmark(
        [&scalar]() {
            unsigned char bytes[32];

            sc_sub(bytes, scalar, scalar);
        },
        "sc_sub");

    benchmark(
        [&scalar]() {
            unsigned char bytes[32];

            sc_mul(bytes, scalar, scalar);
        },
        "sc_mul");

    benchmark(
        [&scalar]() {
            unsigned char bytes[32];

            sc_muladd(bytes, scalar, scalar, scalar);
        },
        "sc_muladd");

    benchmark(
        [&scalar]() {
            unsigned char bytes[32];

            sc_mulsub(bytes, scalar, scalar, scalar);
        },
        "sc_mulsub");

    benchmark([&scalar]() { sc_reduce32((unsigned char *)&scalar); }, "sc_reduce32");
}