cmake_minimum_required(VERSION 3.20)
project(5c_complexityAssessment C)

set(CMAKE_C_STANDARD 11)

add_executable(5c_complexityAssessment main.c
        estimationOfComplexityOfAlgorithms/estimationOfComplexityOfAlgorithms.c estimationOfComplexityOfAlgorithms/estimationOfComplexityOfAlgorithms.h
        sorts/sorts.c sorts/sorts.h)



