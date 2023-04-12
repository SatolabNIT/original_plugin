#include <cstdlib> // for system()
#include <ros/package.h> // for ros::package::getPath()
#include <string>
#include <ros/ros.h>

int main(int argc, char **argv)
{
    // Initialize ROS node
    ros::init(argc, argv, "my_node");
    ros::NodeHandle nh;

    // Get path to the launch file
    std::string pkg_path = ros::package::getPath("basic_lecture");
    std::string launch_file = pkg_path + "/launch/pubsub1.launch";

    // Construct roslaunch command and execute it in a new terminal
    std::string roslaunch_command = "gnome-terminal -- roslaunch " + launch_file;
    system(roslaunch_command.c_str());

    return 0;
}
