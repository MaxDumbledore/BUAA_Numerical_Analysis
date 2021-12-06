cmake_minimum_required(VERSION 3.16)
project(NumericalAnalysisT8)

set(CMAKE_CXX_STANDARD 17)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(NumericalAnalysisT8 main.cpp NonLinFormula.cpp NonLinFormula.h NonLinItemMatrix.cpp NonLinItemMatrix.h NonLinearEqUtil.cpp NonLinearEqUtil.h Vector.cpp Vector.h Matrix.cpp Matrix.h LinearEqUtil.cpp LinearEqUtil.h ZeroRangeGuard.h InterpolationUtil.cpp InterpolationUtil.h NonSqMatrix.cpp NonSqMatrix.h)
