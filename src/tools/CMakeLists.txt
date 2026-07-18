# Optional CUDA support
# find_package(CUDAToolkit QUIET)

include(CheckLanguage)
check_language(CUDA)
if (CMAKE_CUDA_COMPILER)
    enable_language(CUDA)
    message(STATUS "CUDA found: enabling CUDA trainer")
else()
    message(STATUS "CUDA not found: CUDA trainer disabled")
endif()

file(
    GLOB_RECURSE GEFORCE_UTILS_SOURCES
    *.cpp *.hpp *.c *.h *.cu
)

# Exclude CUDA sources when CUDA is not available
if (NOT CMAKE_CUDA_COMPILER)
    list(FILTER GEFORCE_UTILS_SOURCES EXCLUDE REGEX ".*\\.cu$")
    list(FILTER GEFORCE_UTILS_SOURCES EXCLUDE REGEX ".*/cudaTrainer/.*")
    list(FILTER GEFORCE_UTILS_SOURCES EXCLUDE REGEX ".*CudaNetworkTrainer\\.cpp$")
endif()

foreach(_source IN ITEMS ${GEFORCE_UTILS_SOURCES})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

add_executable(trainer ${GEFORCE_UTILS_SOURCES})

set_property(TARGET trainer PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

add_dependencies(trainer engine_lib)

target_link_libraries(trainer PRIVATE engine_lib)

if (NOT MSVC)
	find_package(Threads REQUIRED)
	target_link_libraries(trainer PRIVATE Threads::Threads)

	if (NUMA_FOUND)
		target_link_libraries(trainer PRIVATE NUMA::numa)
	endif()
endif()

if (FALSE)
    target_compile_definitions(trainer PRIVATE USE_CUDA)
    target_link_libraries(trainer PRIVATE CUDA::cudart)
    set_property(TARGET trainer PROPERTY CUDA_ARCHITECTURES native)
    set_property(TARGET trainer PROPERTY CUDA_SEPARABLE_COMPILATION ON)
    set_target_properties(trainer PROPERTIES
        CUDA_STANDARD 20
        CUDA_STANDARD_REQUIRED ON
    )
endif()
