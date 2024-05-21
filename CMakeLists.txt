cmake_minimum_required(VERSION 3.10)

project(Image_filter LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ImageFilter VERSION 1.0)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set( OpenCV_DIR "./vcpkg_installed/x64-windows/share/fmt" )
set( OpenCV_DIR "./vcpkg_installed/x64-windows/share/unofficial-sqlite3" )
set( OpenCV_DIR "./vcpkg_installed/x64-windows/share/opencv" )
set( OpenCV_DIR "./vcpkg_installed/x64-windows/share/opencv4" )
set( TIFF_INCLUDE_DIR   "./vcpkg/packages/tiff_x64-windows/include")
set( TIFF_LIBRARY  "./vcpkg/packages/tiff_x64-windows/lib/tiffd.lib")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ./vcpkg_installed/x64-windows/share/opencv)

find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(OpenCV CONFIG REQUIRED)
find_package(TIFF REQUIRED)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS} ${SQLite3_INCLUDE_DIRS} ${TIFF_INCLUDE_DIR} image_processor/inc)

# Source files
set(SOURCE_FILES
    main.cpp
    image_processor/src/convolution_tools.cpp
    image_processor/src/filters.cpp
    image_processor/src/gauss_filter.cpp
    image_processor/src/image_mat_tools.cpp
    image_processor/src/image_estimator.cpp
    image_processor/src/image_noiser.cpp
    image_processor/src/image_estimator.cpp
    image_processor/src/image_plotter.cpp
    image_processor/src/median_filter.cpp
    image_processor/src/nlm_filter.cpp
    image_processor/src/simple_image_filters.cpp
    image_processor/src/stream_manager.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${SQLite3_LIBRARIES} ${TIFF_LIBRARY} fmt::fmt-header-only)

# Set build types
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")