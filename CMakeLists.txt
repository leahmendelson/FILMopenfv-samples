cmake_minimum_required (VERSION 2.8)

project (OpenFVSamples)

set (PROJECT_VERSION_MAJOR 1)
set (PROJECT_VERSION_MINOR 0)

find_package(OpenCV REQUIRED)

set(CUDA_INC_DIR "/usr/local/cuda/include" CACHE PATH "Path to CUDA Directory")
set(EIGEN_INC_DIR "/usr/include/eigen3" CACHE PATH "Path to Eigen Directory")
set(OFV_INC_DIR "/usr/local/include" CACHE PATH "Path to OpenFV Include Directory")
set(OFV_LIB_DIR "/usr/local/lib" CACHE PATH "Path to OpenFV Lib Directory")

# Python
set(Python_ADDITIONAL_VERSIONS "2.7")
find_package(PythonLibs REQUIRED)
if (PYTHONLIBS_FOUND)
  message("Python found!")
  message("Python Libraries: " ${PYTHON_LIBRARIES})
else()
  message("Python not found! Python wrappers will not be built.")
  set(BUILD_PYTHON OFF)
endif()
set(BOOST_PYTHON_VERSION "python" CACHE PATH "Boost Python Version [python or python3]")

find_package(Boost)
if(Boost_FOUND)
  find_package ( Boost COMPONENTS program_options filesystem system serialization REQUIRED )
  set(Boost_GENERAL ${Boost_LIBRARIES})
  find_package ( Boost COMPONENTS python REQUIRED )
  set(Boost_PY ${Boost_LIBRARIES})
elseif(NOT Boost_FOUND)
  message("Boost not found!")
endif() 

# Include directories
include_directories( ${OFV_INC_DIR} )
include_directories( ${PYTHON_INCLUDE_DIRS} )
include_directories( ${CUDA_INC_DIR} )
include_directories( ${Boost_INCLUDE_DIR} )
include_directories( ${EIGEN_INC_DIR} )

# Link directories
link_directories( ${OFV_LIB_DIR} )

set (OTHER_LIBS tiff ${Boost_GENERAL} ${Boost_PY} glog gflags)
set (PROF_LIBS profiler)

# B: Commenting this out for non-cuda build
#set (LIBS ${CUSTOM_LIBS} ${PROF_LIBS} ${OTHER_LIBS} ${OpenCV_LIBS} ${PYTHON_LIBRARIES} openfv cuda_openfv)
set (LIBS ${CUSTOM_LIBS} ${PROF_LIBS} ${OTHER_LIBS} ${OpenCV_LIBS} ${PYTHON_LIBRARIES} openfv)

# add_executable (track ${PROJECT_SOURCE_DIR}/track.cpp)
# target_link_libraries (track ${LIBS})

add_executable (refocus ${PROJECT_SOURCE_DIR}/refocus.cpp)
target_link_libraries (refocus ${LIBS})
