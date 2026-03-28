cmake_minimum_required(VERSION 3.10)
project(DAProj1)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(myProg
        src/main.cpp
        src/parser/CsvParser.cpp
        src/graph/Graph.cpp
        src/graph/MaxFlow.cpp
        src/core/AssignmentEngine.cpp
        src/core/RiskAnalyzer.cpp
        src/core/OutputWriter.cpp
        src/ui/Menu.cpp
)
