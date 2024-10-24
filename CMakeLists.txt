cmake_minimum_required(VERSION 3.25.1)
PROJECT(queue_system)

set(CMAKE_CXX_STANDARD 26)

find_package(wxWidgets CONFIG REQUIRED)
find_package(boost_math REQUIRED CONFIG)

file(GLOB_RECURSE sources src/*.cpp)

if(WIN32)
    add_executable(queue_system WIN32 ${sources})
else()
    add_executable(queue_system ${sources})
endif()

target_include_directories(queue_system PRIVATE
        src
)
target_link_libraries(queue_system PRIVATE wx::core Boost::math)

if(UNIX)
    target_link_libraries(queue_system PRIVATE X11)
endif()

if(WIN32)
    target_sources(queue_system PRIVATE queue_system.manifest)
endif()