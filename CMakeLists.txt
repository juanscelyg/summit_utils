cmake_minimum_required(VERSION 3.8)
project(summit_utils)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(ament_index_cpp REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(robot_localization REQUIRED)
find_package(ament_cmake_auto REQUIRED)

install(DIRECTORY launch include src  
        DESTINATION share/${PROJECT_NAME})

set(dependencies
  rclcpp
  std_msgs
  sensor_msgs
  geometry_msgs
  ament_index_cpp
  tf2
  tf2_geometry_msgs
  robot_localization
)

include_directories(include)
add_library(imu_orientation_lib SHARED
  src/IMUOrientation/IMUOrientation.cpp
)
ament_target_dependencies(imu_orientation_lib ${dependencies})
target_link_libraries(imu_orientation_lib)

add_executable(imu_orientation src/imu_orientation_node.cpp)

ament_target_dependencies(imu_orientation ${dependencies})
target_link_libraries(imu_orientation imu_orientation_lib)
install(TARGETS
  imu_orientation
  imu_orientation_lib
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()