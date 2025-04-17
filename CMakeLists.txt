#---------------------------------------------------------------------------------------------------
# CMake Build Configuration for the Ray Tracing Weekend Series
#
# See README.md for guidance.
#---------------------------------------------------------------------------------------------------

cmake_minimum_required (VERSION 3.1.0...3.27.0)

project (RTWeekend LANGUAGES CXX)

# Set to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add OpenMP manually for AppleClang (macOS)
if (APPLE)
    message(STATUS "Configuring OpenMP manually for AppleClang")
    set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp -I/usr/local/opt/libomp/include")
    set(OpenMP_CXX_LIB_NAMES "omp")
    set(OpenMP_omp_LIBRARY "/usr/local/opt/libomp/lib/libomp.dylib")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/opt/libomp/lib -lomp")
endif()

# Source files
set(EXTERNAL
    src/external/stb_image.h
)

set(SOURCE_ONE_WEEKEND
    src/InOneWeekend/main.cc
    src/InOneWeekend/camera.h
    src/InOneWeekend/color.h
    src/InOneWeekend/hittable.h
    src/InOneWeekend/hittable_list.h
    src/InOneWeekend/interval.h
    src/InOneWeekend/material.h
    src/InOneWeekend/ray.h
    src/InOneWeekend/rtweekend.h
    src/InOneWeekend/sphere.h
    src/InOneWeekend/vec3.h
)

set(SOURCE_NEXT_WEEK
    src/TheNextWeek/main.cc
    src/TheNextWeek/aabb.h
    src/TheNextWeek/bvh.h
    src/TheNextWeek/camera.h
    src/TheNextWeek/color.h
    src/TheNextWeek/constant_medium.h
    src/TheNextWeek/hittable.h
    src/TheNextWeek/hittable_list.h
    src/TheNextWeek/interval.h
    src/TheNextWeek/material.h
    src/TheNextWeek/perlin.h
    src/TheNextWeek/quad.h
    src/TheNextWeek/ray.h
    src/TheNextWeek/rtw_stb_image.h
    src/TheNextWeek/rtweekend.h
    src/TheNextWeek/sphere.h
    src/TheNextWeek/texture.h
    src/TheNextWeek/vec3.h
)

set(SOURCE_REST_OF_YOUR_LIFE
    src/TheRestOfYourLife/main.cc
    src/TheRestOfYourLife/aabb.h
    src/TheRestOfYourLife/camera.h
    src/TheRestOfYourLife/color.h
    src/TheRestOfYourLife/constant_medium.h
    src/TheRestOfYourLife/hittable.h
    src/TheRestOfYourLife/hittable_list.h
    src/TheRestOfYourLife/interval.h
    src/TheRestOfYourLife/material.h
    src/TheRestOfYourLife/onb.h
    src/TheRestOfYourLife/pdf.h
    src/TheRestOfYourLife/perlin.h
    src/TheRestOfYourLife/quad.h
    src/TheRestOfYourLife/ray.h
    src/TheRestOfYourLife/rtw_stb_image.h
    src/TheRestOfYourLife/rtweekend.h
    src/TheRestOfYourLife/sphere.h
    src/TheRestOfYourLife/texture.h
    src/TheRestOfYourLife/vec3.h
)

include_directories(src)

# Compiler warnings and optimizations
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options("/W4")
    add_compile_options("/we 4265")
    add_compile_options("/we 5204")
    add_compile_options("/wd 4100")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wnon-virtual-dtor)
    add_compile_options(-Wreorder)
    add_compile_options(-Wmaybe-uninitialized)
    add_compile_options(-Wunused-variable)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wnon-virtual-dtor)
    add_compile_options(-Wreorder)
    add_compile_options(-Wsometimes-uninitialized)
    add_compile_options(-Wunused-variable)
endif()

# Executables
add_executable(inOneWeekend ${EXTERNAL} ${SOURCE_ONE_WEEKEND})
# target_link_libraries(inOneWeekend OpenMP::OpenMP_CXX)

add_executable(theNextWeek ${EXTERNAL} ${SOURCE_NEXT_WEEK})
add_executable(theRestOfYourLife ${EXTERNAL} ${SOURCE_REST_OF_YOUR_LIFE})
add_executable(cos_cubed src/TheRestOfYourLife/cos_cubed.cc)
add_executable(cos_density src/TheRestOfYourLife/cos_density.cc)
add_executable(integrate_x_sq src/TheRestOfYourLife/integrate_x_sq.cc)
add_executable(pi src/TheRestOfYourLife/pi.cc)
add_executable(estimate_halfway src/TheRestOfYourLife/estimate_halfway.cc)
add_executable(sphere_importance src/TheRestOfYourLife/sphere_importance.cc)
add_executable(sphere_plot src/TheRestOfYourLife/sphere_plot.cc)
