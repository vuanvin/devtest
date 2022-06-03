
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(myops)

find_package(Torch REQUIRED)
# find_package(OpenCV REQUIRED)

# Define our library target
add_library(myops SHARED op.cpp)
# Enable C++14
target_compile_features(myops PRIVATE cxx_std_14)
# Link against LibTorch
target_link_libraries(myops "${TORCH_LIBRARIES}")
# Link against OpenCV
# target_link_libraries(warp_perspective opencv_core opencv_imgproc)