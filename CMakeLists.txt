cmake_minimum_required(VERSION 3.14)

project(G-means LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#*****************************************************
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
#******************************************************
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
#-------------------------------------------------------------------------------------------------------------
find_path(PYCLUSTERING_INCLUDE_DIRS definitions.hpp REQUIRED)
find_library(PYCLUSTERING_LIBRARIES NAMES pyclustering REQUIRED)


#-------------------------------------------------------------------------------------------------------------
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Charts)


add_executable(G-means
    src/main.cpp
    src/chartview.h
    src/chartview.cpp
#    src/clustering.h notworking
#    src/gmeansmodel.h notworking
#    src/gmeansmodel.cpp notworking
    src/filehandler.h
    src/filehandler.cpp
    src/clusterer.h
    src/clusterer.cpp
    src/custom_definitions.h
    src/clusteringmetrics.h
    src/clusteringmetrics.cpp
)
target_link_libraries(G-means Qt${QT_VERSION_MAJOR}::Core Qt5::Charts ${PYCLUSTERING_LIBRARIES})
target_include_directories(G-means PUBLIC ${PYCLUSTERING_INCLUDE_DIRS})
install(TARGETS G-means
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
