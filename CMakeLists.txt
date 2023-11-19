cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND ENV{CMAKE_TOOLCHAIN_FILE})
    set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()


project(ClothSim_build)

find_package(NGL CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(ExName ClothSim)
add_executable(${ExName}
        src/main.cpp
        src/ClothSim.cpp
        src/ClothMesh.cpp
        src/Particle.cpp
        src/Constraint.cpp
        include/ClothSim.h
        include/ClothMesh.h
        include/Particle.h
        include/Constraint.h
)
target_include_directories(${ExName} PRIVATE include $ENV{HOME}/NGL/include)
target_link_libraries(${ExName} PRIVATE NGL)

### Testing Code
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
set(TestName ClothSimTests)
add_executable(${TestName}
        tests/ClothSimTests.cpp
        tests/ParticleTests.cpp
        src/ClothSim.cpp
        src/Particle.cpp
        src/ClothMesh.cpp
        include/ClothMesh.h
        include/Particle.h

)
target_include_directories(${TestName} PRIVATE include $ENV{HOME}/NGL/include)
target_link_libraries(${TestName} PRIVATE GTest::gtest GTest::gtest_main NGL)
gtest_discover_tests(${TestName})
