cmake_minimum_required(VERSION 3.8)
project(turtlesim_draw)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(turtlesim REQUIRED)  # turtlesim 패키지 추가
find_package(geometry_msgs REQUIRED)
# include directories
include_directories(
  include
)

# add executable
add_executable(turtlesim_draw_node src/turtlesim_draw.cpp src/main.cpp)
ament_target_dependencies(turtlesim_draw_node rclcpp std_msgs turtlesim geometry_msgs)

# install executables and headers
install(TARGETS
  turtlesim_draw_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include/
)

# testing
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # 다음 라인은 저작권 확인을 건너뜁니다.
  # 모든 소스 파일에 저작권 및 라이선스를 추가할 때 주석 처리하십시오.
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
