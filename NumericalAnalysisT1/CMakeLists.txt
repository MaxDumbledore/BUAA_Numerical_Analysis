cmake_minimum_required(VERSION 3.16)
project(NumericalAnalysisT1)

set(CMAKE_CXX_STANDARD 17)

add_executable(NumericalAnalysisT1 main.cpp SymBandMatrix.cpp SymBandMatrix.h EigenValueUtils.cpp EigenValueUtils.h Vector.cpp Vector.h LinearEqLuSolver.cpp LinearEqLuSolver.h TimerUtil.cpp TimerUtil.h)