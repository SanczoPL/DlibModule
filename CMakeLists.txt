cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(dlibModule VERSION 0.0.1 DESCRIPTION "dlibModule v1.0" LANGUAGES C CXX)

set(DEFAULT_BUILD_TYPE "Debug")
set(CMAKE_BUILD_TYPE "Debug")

#STNDARD STUFF
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_COMMON}")
if (UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -lX11 -Wall" )
endif (UNIX)
if (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP" )
endif (WIN32)

set(TARGET_NAME "dlibModule")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

macro(copy_json jsonname)
	configure_file(${jsonname} ${CMAKE_BINARY_DIR}/${jsonname})
	configure_file(${jsonname} ${CMAKE_BUILD_TYPE}/${jsonname})
	configure_file(${jsonname} ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${jsonname})
endmacro()

#copy_json("configs/config.json")
#copy_json("configs/preprocess.json")
#copy_json("configs/postprocess.json")
#copy_json("configs/dataset.json")

include_directories( "include" )
include_directories( "../PostProcessingModules/include" )
include_directories( "../ProcessingModules/include" )
include_directories( "../DataManagement/include" )
include_directories( "../ProcessingGraph/include" )
include_directories( "../Utils/include" )

if (WIN32)
	set(QT5_PATH  "E:\\Qt\\5.15.2\\msvc2019_64")
	list(APPEND CMAKE_PREFIX_PATH ${QT5_PATH})
	list(APPEND CMAKE_PREFIX_PATH "E:\\repo\\opencvBuild")
	list(APPEND CMAKE_PREFIX_PATH "E:\\repo\\opencvBuild\\bin\\Debug")
	list(APPEND CMAKE_PREFIX_PATH "E:\\repo\\opencvBuild\\install\\include")
	list(APPEND CMAKE_PREFIX_PATH "E:\\repo\\opencvBuild\\install")
	list(APPEND CMAKE_PREFIX_PATH "E:\\repo\\dlib\\build\\installDebug\\lib\\cmake\\dlib")
endif (WIN32)

if (UNIX)
	find_package(X11 REQUIRED)
endif (UNIX)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
find_package(OpenCV QUIET COMPONENTS core highgui imgproc imgcodecs videoio)
find_package(dlib REQUIRED)

find_package(graph_lib REQUIRED)
find_package(utils_lib REQUIRED)

enable_testing()

set(SRC_MAIN_TRAIN src/maintrain.cc)
set(SRC_MAIN_TEST src/maintest.cc)

set(SRC_NETWORK
	include/network/dnn_instance_segmentation_ex.h
	include/network/structures.h
)

set(SRC_TRAIN
	src/train/dlibcase.cc
	src/train/mainloop.cc
)

set(HEADERS_TRAIN
	include/train/dlibcase.h
	include/train/mainloop.h
)

set(SRC_TEST
	src/test/dlibcase.cc
	src/test/mainloop.cc
)

set(HEADERS_TEST
	include/test/dlibcase.h
	include/test/mainloop.h
)

add_library(${PROJECT_NAME}_lib_test STATIC
	${SRC_NETWORK}
	${SRC_TEST} ${HEADERS_TEST})

add_library(${PROJECT_NAME}_lib_train STATIC
	${SRC_NETWORK}
	${SRC_TRAIN} ${HEADERS_TRAIN})

add_executable(${PROJECT_NAME}_train
    ${SRC_MAIN_TRAIN})

add_executable(${PROJECT_NAME}_test
    ${SRC_MAIN_TEST})

message(" cv_libs:     " ${OpenCV_LIBS})
message(" cv_includes: " ${OPENCV_INCLUDE_DIRS})


#file(GLOB_RECURSE SRC_HEADERS_TEST gtest/*.cc gtest/*.h)
#file(GLOB_RECURSE SRC_HEADERS_TEST_IT gtest_it/*.cc gtest_it/*.h)
#add_executable(g_test ${SRC_HEADERS_TEST})
#add_executable(g_test_it ${SRC_HEADERS_TEST_IT})


target_link_libraries(${PROJECT_NAME}_lib_test ${QT_LIBRARIES} ${OpenCV_LIBS} Threads::Threads utils_lib data_lib graph_lib)
target_link_libraries(${PROJECT_NAME}_lib_test Qt5::Core dlib::dlib)

target_link_libraries(${PROJECT_NAME}_lib_train utils_lib data_lib graph_lib)
target_link_libraries(${PROJECT_NAME}_lib_train dlib::dlib)

if (UNIX)
target_link_libraries(${PROJECT_NAME}_lib_train X11)
target_link_libraries(${PROJECT_NAME}_lib_test X11)
endif (UNIX)

target_link_libraries(${PROJECT_NAME}_train ${PROJECT_NAME}_lib_train)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_lib_test)


message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE} ")

if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND WIN32)
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release" AND WIN32)
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()
