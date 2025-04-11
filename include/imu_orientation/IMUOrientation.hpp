#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/magnetic_field.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>

namespace imu_orientation
{


class IMUOrientation : public rclcpp::Node
{
public:
  IMUOrientation();
  ~IMUOrientation();

private:
  void imu_callback(const sensor_msgs::msg::Imu::SharedPtr msg);

  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;

  double roll_, pitch_, yaw_;
};

}  // namespace imu_orientation