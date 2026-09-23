from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='temperature_monitor',
            executable='sensor_node',
            name='sensor_node',
            output='screen'
        ),

        Node(
            package='temperature_monitor',
            executable='monitor_node',
            name='monitor_node',
            output='screen'
        )
    ])
