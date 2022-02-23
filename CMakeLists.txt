cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0054 NEW)
cmake_policy(SET CMP0048 NEW)
cmake_minimum_required(VERSION 3.21)
project(trigger)

set(CMAKE_CXX_STANDARD 11)

find_package(Qt5 COMPONENTS Core Sql REQUIRED)


file(GLOB HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
        )

file(GLOB SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
        )


qt5_wrap_cpp(WRAPPED_HEADERS ${HEADERS})
add_executable(trigger source/main.cpp ${WRAPPED_HEADERS})
target_link_libraries(trigger Qt5::Core Qt5::Sql)
