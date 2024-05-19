# CMakeList.txt : CMake project for image_filter_cv, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("image_filter_cv")

# Add source to this project's executable.
add_executable (image_filter_cv "image_filter_cv.cpp" "image_filter_cv.h")

# TODO: Add tests and install targets if needed.
