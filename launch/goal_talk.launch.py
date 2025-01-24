import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription

from launch_ros.actions import Node


def generate_launch_description():
  # pkg_tb3_sim = get_package_share_directory('tb3_sim')
  pkg_goal_talk = get_package_share_directory('goal_talk')
  x_pose = LaunchConfiguration('x_pose', default= 0.75)
  y_pose = LaunchConfiguration('y_pose', default= 0.75)

  goal_talk_node_cmd = Node(
      package="goal_talk",
      executable="goal_talk_node",
      name="goal_talk_node",
      #parameters=[{
      #    "location_file": os.path.join(pkg_goal_talk, "config", "sim_house_locations.yaml")
      #}]
  )

  ld = LaunchDescription()

  # Add the commands to the launch description
  ld.add_action(goal_talk_node_cmd)

  return ld