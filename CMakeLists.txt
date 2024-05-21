cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(Image_filter LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ImageFilter VERSION 1.0)

set(TIFF_NAMES ${TIFF_NAMES} tiff libtiff tiff3 libtiff3)

set(TIFF_LIBRARY "${CMAKE_CURRENT_LIST_DIR}/vcpkg_installed/x64-windows/lib/tiff.lib")
set(TIFF_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/vcpkg_installed/x64-windows/include")

find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(OpenCV CONFIG REQUIRED)
find_package(tiff REQUIRED)

include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/image_processor/inc)

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

target_link_libraries(${PROJECT_NAME} PRIVATE opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui unofficial::sqlite3::sqlite3 TIFF::TIFF fmt::fmt-header-only)

# Set build types
#set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")