cmake_minimum_required(VERSION 3.5)
project(parameter_set)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(Boost 1.71.0 REQUIRED COMPONENTS thread)
find_package(Qt5 COMPONENTS Widgets Core Gui Network REQUIRED)

# File collection
file(GLOB PRO_SOURCE_DIR src/*.cpp)
file(GLOB PRO_UI_DIR ui/*.ui)
file(GLOB PRO_INCLUDE_DIR include/parameter_set/*.h include/parameter_set/*.hpp)
file(GLOB PRO_RESOURCE_DIR resources/*.qrc)

# Qt specific wrapping
qt5_wrap_ui(QT_UI_HPP ${PRO_UI_DIR})
qt5_wrap_cpp(QT_MOC_HPP ${PRO_INCLUDE_DIR})
qt5_add_resources(QT_RESOURCE_HPP ${PRO_RESOURCE_DIR})

# Include directories
include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/parameter_set  # image_node.hpp 위치 추가
  ${CMAKE_CURRENT_BINARY_DIR}
)

# Executable setup
add_executable(${PROJECT_NAME} ${PRO_SOURCE_DIR} ${QT_MOC_HPP} ${QT_RESOURCE_HPP} ${QT_UI_HPP})

# Add dependencies to target
ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  sensor_msgs
  cv_bridge
  Boost
)

# Link Qt and OpenCV libraries
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network ${OpenCV_LIBRARIES})

# Install targets
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Optional testing setup
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
