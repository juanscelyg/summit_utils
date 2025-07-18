cmake_minimum_required(VERSION 3.8)
project(summit_utils)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

install(DIRECTORY config launch   
        DESTINATION share/${PROJECT_NAME})

# Library
add_library(${PROJECT_NAME} SHARED
  src/IMUOrientation/IMUOrientation.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  rclcpp::rclcpp
  ${std_msgs_TARGETS}
  ${geometry_msgs_TARGETS}
  ${sensor_msgs_TARGETS}
  ament_index_cpp::ament_index_cpp
  tf2::tf2
  tf2_geometry_msgs::tf2_geometry_msgs
)

# Executable
add_executable(imu_orientation_node src/imu_orientation_node.cpp)
target_link_libraries(imu_orientation_node PUBLIC
  ${PROJECT_NAME}
)

# Install headers
install(DIRECTORY include/
  DESTINATION include/${PROJECT_NAME}
)

# Install targets
install(TARGETS
  ${PROJECT_NAME}
  imu_orientation_node
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

# Export
ament_export_include_directories("include/${PROJECT_NAME}")
ament_export_libraries(${PROJECT_NAME})
ament_export_targets(export_${PROJECT_NAME})
ament_export_dependencies(
  rclcpp
  std_msgs
  sensor_msgs
  geometry_msgs
  ament_index_cpp
  tf2
  tf2_geometry_msgs
  robot_localization
)

ament_package()