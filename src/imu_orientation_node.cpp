#include "imu_orientation/IMUOrientation.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto imu_node = std::make_shared<imu_orientation::IMUOrientation>();
  rclcpp::spin(imu_node);

  rclcpp::shutdown();
  return 0;
}