from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():

    imu_topic = LaunchConfiguration("imu_topic", default="/imu/data")


    ld = LaunchDescription()

    imu_node = Node(
            package='summit_utils',  
            executable='imu_orientation',  
            name='imu_orientation',
            output='screen',
            parameters=[
                {"imu_topic": imu_topic}
            ]
        )
    ld.add_action(imu_node)
    return ld