#include <behaviortree_cpp_v3/bt_factory.h>
#include <ament_index_cpp/get_package_share_directory.hpp>

#include "bt_tutorial01/sc_check_battery.hpp"
#include "bt_tutorial01/nd_approach_object.hpp"
#include "bt_tutorial01/gripper_interface.hpp"


int main()
{
  BT::BehaviorTreeFactory factory;

  factory.registerNodeType<ApproachObject>("ApproachObject");

  factory.registerSimpleCondition("CheckBattery", std::bind(CheckBattery));

  GripperInterface gripper;
  factory.registerSimpleAction(
    "OpenGripper",
    std::bind(&GripperInterface::open, &gripper));
  factory.registerSimpleAction(
    "CloseGripper",
    std::bind(&GripperInterface::close, &gripper));

  const std::string tree_filename =
    ament_index_cpp::get_package_share_directory("bt_tutorial01") +
    "/trees/my_tree.xml";
  auto tree = factory.createTreeFromFile(tree_filename);

  tree.tickRoot();
  return 0;
}
