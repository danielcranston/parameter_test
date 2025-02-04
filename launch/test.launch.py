# Copyright (c) 2021, Schilling Robotics
# All rights reserved.
#
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential

from ament_index_python.packages import get_package_share_directory
import os

from launch import LaunchDescription
from launch.actions import OpaqueFunction, DeclareLaunchArgument
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration


def launch_setup(context, *args, **kwargs):
    test_node = Node(
        package="parameter_test",
        executable="parameter_test",
        output="screen",
        name="param_test",
        parameters=[{"param": [LaunchConfiguration("param")]}],
    )

    nodes_to_launch = [test_node]
    return nodes_to_launch


def generate_launch_description():
    # Declare arguments
    declared_arguments = [
        DeclareLaunchArgument("param", default_value="launch-defaulted value"),
    ]

    ld = LaunchDescription(
        declared_arguments
        + [
            OpaqueFunction(function=launch_setup),
        ]
    )

    return ld
