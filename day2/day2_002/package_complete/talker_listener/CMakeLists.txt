cmake_minimum_required(VERSION 3.5)
project(talker_listener)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(Boost 1.71.0 REQUIRED COMPONENTS thread)
find_package(Qt5 COMPONENTS Widgets Core Gui Network REQUIRED)

# Source files
file(GLOB PRO_SOURCE_DIR RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)
file(GLOB PRO_UI_DIR RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS ui/*.ui)
file(GLOB PRO_INCLUDE_DIR RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS include/${PROJECT_NAME}/*.h include/${PROJECT_NAME}/*.hpp)
file(GLOB PRO_RESOURCE_DIR RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS resource/*.qrc)

# Wrap UI and MOC files
qt5_wrap_ui(QT_UI_HPP ${PRO_UI_DIR})
qt5_wrap_cpp(QT_MOC_HPP ${PRO_INCLUDE_DIR})
qt5_add_resources(QT_RESOURCE_HPP ${PRO_RESOURCE_DIR})

# Include directories
include_directories(
  include/
  ${CMAKE_CURRENT_BINARY_DIR}
)

# Build the executable with the same name as the project
add_executable(talker_listener
  ${PRO_SOURCE_DIR}
  ${PRO_INCLUDE_DIR}
  ${PRO_UI_DIR}
  ${QT_MOC_HPP}
  ${QT_RESOURCE_HPP}
  ${QT_UI_HPP}
)
ament_target_dependencies(talker_listener rclcpp Boost std_msgs)
target_link_libraries(talker_listener Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network)

# Installation
install(TARGETS talker_listener DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
