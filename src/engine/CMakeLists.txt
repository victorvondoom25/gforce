file(GLOB_RECURSE ENGINE_SOURCES *.cpp)
list(FILTER ENGINE_SOURCES EXCLUDE REGEX ".*UCI\\.cpp$")

add_library(engine_lib STATIC ${ENGINE_SOURCES})
set_property(TARGET engine_lib PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

add_executable(G-ForceZero UCI.cpp)
set_property(TARGET G-ForceZero PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

target_link_libraries(G-ForceZero PRIVATE engine_lib)

if (NOT MSVC)
    find_package(Threads REQUIRED)
    target_link_libraries(engine_lib PRIVATE Threads::Threads)
    target_link_libraries(G-ForceZero PRIVATE Threads::Threads)
    if (NUMA_FOUND)
        target_link_libraries(engine_lib PRIVATE NUMA::numa)
        target_link_libraries(G-ForceZero PRIVATE NUMA::numa)
    endif()
endif()
