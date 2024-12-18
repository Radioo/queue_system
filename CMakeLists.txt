cmake_minimum_required(VERSION 3.25.1)
PROJECT(queue_system)

set(CMAKE_CXX_STANDARD 26)

if(WIN32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

    # Set runtime library for each configuration
#    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")  # Use for static runtime in Debug
#    set(CMAKE_CXX_FLAGS_DEBUG "/MTd")  # Debug flags

    #set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")  # Use for static runtime in Release
    #set(CMAKE_CXX_FLAGS_RELEASE "/MT")  # Release flags
endif()

find_package(wxWidgets CONFIG REQUIRED)
find_package(boost_math REQUIRED CONFIG)
find_package(QuantLib CONFIG REQUIRED)

file(GLOB_RECURSE sources src/*.cpp)

if(WIN32)
    add_executable(queue_system WIN32 ${sources})
else()
    add_executable(queue_system ${sources})
endif()

target_include_directories(queue_system PRIVATE
        src
)
target_link_libraries(queue_system PRIVATE wx::core Boost::math QuantLib::QuantLib)

if(UNIX)
    target_link_libraries(queue_system PRIVATE X11)
endif()

if(WIN32)
    target_sources(queue_system PRIVATE queue_system.manifest)
endif()