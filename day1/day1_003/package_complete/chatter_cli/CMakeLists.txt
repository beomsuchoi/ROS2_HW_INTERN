cmake_minimum_required(VERSION 3.8)
project(chatter_cli)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# include 디렉토리 추가
include_directories(include)

# Add the libraries for talker and listener nodes
add_library(talker_lib src/talker.cpp)
ament_target_dependencies(talker_lib rclcpp std_msgs)

add_library(listener_lib src/listener.cpp)
ament_target_dependencies(listener_lib rclcpp std_msgs)

# Add the executable for main node and link libraries
add_executable(main src/main.cpp)
ament_target_dependencies(main rclcpp std_msgs)
target_link_libraries(main talker_lib listener_lib)  # main에 talker_lib와 listener_lib를 링크

# Install executables
install(TARGETS
  main
  DESTINATION lib/${PROJECT_NAME})

# Install libraries
install(TARGETS
  talker_lib
  listener_lib
  DESTINATION lib/${PROJECT_NAME})

# Testing and linting (if enabled)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
