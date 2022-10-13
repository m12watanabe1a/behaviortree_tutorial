#include <behaviortree_cpp_v3/bt_factory.h>
#include <ament_index_cpp/get_package_share_directory.hpp>

#include <bt_tutorial01/sc_check_battery.hpp>
#include <bt_tutorial02/nd_say_something.hpp>

#include "bt_tutorial04/nd_move_base_action.hpp"

int main()
{
  BT::BehaviorTreeFactory factory;
  factory.registerSimpleCondition("BatteryOK", std::bind(CheckBattery));
  factory.registerNodeType<MoveBaseAction>("MoveBase");
  factory.registerNodeType<SaySomething>("SaySomething");

  const std::string tree_filename =
    ament_index_cpp::get_package_share_directory("bt_tutorial04") +
    "/trees/my_tree_reactive.xml";
  auto tree = factory.createTreeFromFile(tree_filename);

  BT::NodeStatus status;

  std::cout << "\n--- 1st executeTick() ---" << std::endl;
  status = tree.tickRoot();

  // NOTE:
  //   sleep function for BT::Tree is not implemented current ROS package
  //   Use thread sleep instead for just testing

  // tree.sleep(std::chrono::milliseconds(150));
  std::this_thread::sleep_for(std::chrono::milliseconds(150));
  std::cout << "\n--- 2nd executeTick() ---" << std::endl;
  status = tree.tickRoot();

  // tree.sleep(std::chrono::milliseconds(150));
  std::this_thread::sleep_for(std::chrono::milliseconds(150));
  std::cout << "\n--- 3rd executeTick() ---" << std::endl;
  status = tree.tickRoot();

  (void)status;

  std::cout << std::endl;

  return EXIT_SUCCESS;
}
