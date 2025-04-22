#include "imu_orientation/IMUOrientation.hpp"
#include <cmath>
#include <chrono>
#include <memory>

namespace imu_orientation
{

using std::placeholders::_1;

IMUOrientation::IMUOrientation(): Node("imu_orientation")
{
  declare_parameter("imu_topic", "/imu");
  std::string imu_topic = get_parameter("imu_topic").as_string();


    rclcpp::QoS imu_qos(rclcpp::KeepLast(1));
    imu_qos.best_effort();
    rclcpp::SubscriptionOptions options;



  // Subscription to IMU data to get the robot's orientation
  imu_sub_ = create_subscription<sensor_msgs::msg::Imu>(
    imu_topic, imu_qos, std::bind(&IMUOrientation::imu_callback, this, _1), options);
}

IMUOrientation::~IMUOrientation()
{
    // Destructor
    imu_sub_.reset();
    RCLCPP_INFO(this->get_logger(), "IMUOrientation node destroyed");
    rclcpp::shutdown();
    rclcpp::sleep_for(std::chrono::milliseconds(100));
}

// IMU callback to update orientation when new IMU data is received
void IMUOrientation::imu_callback(const sensor_msgs::msg::Imu::SharedPtr msg)
{
  tf2::Quaternion q(
    msg->orientation.x,
    msg->orientation.y,
    msg->orientation.z,
    msg->orientation.w);
  tf2::Matrix3x3 m(q);
  // Extract roll, pitch, and yaw from IMU quaternion
  m.getRPY(roll_, pitch_, yaw_);
  // Mark IMU data as ready
    RCLCPP_INFO(this->get_logger(), "*--------*");
  RCLCPP_INFO(this->get_logger(), "roll: '%f'", roll_);
  RCLCPP_INFO(this->get_logger(), "pitch: '%f'", pitch_);
  RCLCPP_INFO(this->get_logger(), "yaw: '%f'", yaw_);
}

} // namespace imu_orientation