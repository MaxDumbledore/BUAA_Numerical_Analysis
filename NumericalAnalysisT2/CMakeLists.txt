cmake_minimum_required(VERSION 3.16)
project(NumericalAnalysisT2)

set(CMAKE_CXX_STANDARD 17)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(NumericalAnalysisT2 main.cpp Matrix.cpp Matrix.h EigenUtils.cpp EigenUtils.h Vector.cpp Vector.h LinearEqUtil.cpp LinearEqUtil.h ZeroRangeGuard.h)