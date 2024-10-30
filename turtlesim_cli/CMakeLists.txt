cmake_minimum_required(VERSION 3.8)
project(turtlesim_cli)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)  # ROS2 기본 라이브러리
find_package(geometry_msgs REQUIRED)  # Twist 메시지를 사용하기 위한 의존성
find_package(turtlesim REQUIRED)  # turtlesim 패키지 추가 (헤더 파일 사용을 위함)

# add executable
add_executable(turtlesim_cli src/turtlesim_cli.cpp)  # 실행 파일 설정
ament_target_dependencies(turtlesim_cli rclcpp geometry_msgs turtlesim)  # turtlesim 의존성 추가

# install targets
install(TARGETS
  turtlesim_cli
  DESTINATION lib/${PROJECT_NAME})

# 빌드 테스트 설정
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # 다음 줄은 저작권 확인을 건너뜁니다 (모든 소스 파일에 저작권이 추가된 경우 주석 처리)
  set(ament_cmake_copyright_FOUND TRUE)
  # 다음 줄은 cpplint를 건너뜁니다 (git 저장소에서만 유효)
  # 소스 파일에 저작권이 추가된 경우 주석 처리
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

