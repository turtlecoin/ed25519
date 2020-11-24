cmake_minimum_required(VERSION 2.8.12)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "ED25519: Found ccache package... Activating...")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

set(LIB_MAJOR_VERSION "1")
set(LIB_MINOR_VERSION "0")
set(LIB_PATCH_VERSION "0")
set(LIB_VERSION_STRING "${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION}.${LIB_PATCH_VERSION}")

if(CMAKE_VERSION VERSION_LESS 3.0)
    project(ed25519 CXX)
    enable_language(C)
else()
    cmake_policy(SET CMP0048 NEW)
    project(ed25519 VERSION "${LIB_VERSION_STRING}" LANGUAGES C)
endif()

## This section describes our general CMake setup options
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_SKIP_INSTALL_RULES OFF FORCE)
set(CMAKE_SKIP_PACKAGE_ALL_DEPENDENCY ON FORCE)
set(CMAKE_SUPPRESS_REGENERATION ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Enable c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## We only build static binaries -- this is left here for our dependencies
set(STATIC ON CACHE BOOL FORCE "Link libraries statically? Forced to ON")
add_definitions(-DSTATICLIB)

if(NOT MSVC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wno-c99-compat")
endif()

include_directories(include)

set(ED25119_SRC
    src/equal.c
    src/fe_0.c
    src/fe_1.c
    src/fe_add.c
    src/fe_cmov.c
    src/fe_copy.c
    src/fe_divpowm1.c
    src/fe_frombytes.c
    src/fe_invert.c
    src/fe_isnegative.c
    src/fe_isnonzero.c
    src/fe_mul.c
    src/fe_neg.c
    src/fe_pow22523.c
    src/fe_sq.c
    src/fe_sq2.c
    src/fe_sub.c
    src/fe_tobytes.c
    src/ge_add.c
    src/ge_cached_0.c
    src/ge_cached_cmov.c
    src/ge_check_subgroup_precomp_negate_vartime.c
    src/ge_double_scalarmult_negate_vartime.c
    src/ge_double_scalarmult_base_negate_vartime.c
    src/ge_dsm_precomp.c
    src/ge_frombytes_negate_vartime.c
    src/ge_fromfe_frombytes_negate_vartime.c
    src/ge_madd.c
    src/ge_msub.c
    src/ge_mul8.c
    src/ge_p1p1_to_p2.c
    src/ge_p1p1_to_p3.c
    src/ge_p2_0.c
    src/ge_p2_dbl.c
    src/ge_p3_0.c
    src/ge_p3_dbl.c
    src/ge_p3_to_cached.c
    src/ge_p3_to_p2.c
    src/ge_p3_tobytes.c
    src/ge_precomp_0.c
    src/ge_precomp_cmov.c
    src/ge_scalarmult.c
    src/ge_scalarmult_base.c
    src/ge_sub.c
    src/ge_tobytes.c
    src/load_3.c
    src/load_4.c
    src/negative.c
    src/sc_0.c
    src/sc_add.c
    src/sc_check.c
    src/sc_isnonzero.c
    src/sc_mul.c
    src/sc_muladd.c
    src/sc_mulsub.c
    src/sc_reduce.c
    src/sc_reduce32.c
    src/sc_sub.c
    src/signum.c
    src/slide.c
)

add_library(ed25519 STATIC ${ED25119_SRC})

set_property(TARGET ed25519 PROPERTY C_STANDARD 90)
set_property(TARGET ed25519 PROPERTY SOVERSION 1)

foreach(flag_var
        CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    string(REGEX REPLACE "/RTC[^ ]*" "" ${flag_var} "${${flag_var}}")
endforeach(flag_var)
