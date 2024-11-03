cmake_minimum_required(VERSION 3.8)
project(turtlesim_cli)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)
find_package(std_srvs REQUIRED)

# include directory 추가
include_directories(include)

# add executable with main.cpp
add_executable(turtlesim_cli_node src/turtlesim_cli.cpp src/main.cpp)
ament_target_dependencies(turtlesim_cli_node rclcpp geometry_msgs turtlesim std_srvs)

# install targets
install(TARGETS turtlesim_cli_node
    DESTINATION lib/${PROJECT_NAME}
)

# 빌드 테스트 설정
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
