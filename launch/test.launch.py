# Copyright (c) 2021, Schilling Robotics
# All rights reserved.
#
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential

from ament_index_python.packages import get_package_share_directory
import os

from launch import LaunchDescription
from launch.actions import (
    ExecuteProcess,
    OpaqueFunction,
)

def launch_setup(context, *args, **kwargs):
    # Initialize Arguments

    config = os.path.join(
        get_package_share_directory('parameter_test'),
        'config',
        'params.yaml'
        )
    
    parameter_test_node = [
        ExecuteProcess(
            cmd=[
                f"ros2 run parameter_test parameter_test --ros-args --params-file {config} -r __node:='ParamTest'"
            ],
            name="ParamTest",
            shell=True,
            output="screen",
        )
    ]

    nodes_to_launch = (parameter_test_node)
    return nodes_to_launch


def generate_launch_description():
    # Declare arguments
    declared_arguments = []

    ld = LaunchDescription(
        declared_arguments
        + [
            OpaqueFunction(function=launch_setup),
        ]
    )

    return ld
