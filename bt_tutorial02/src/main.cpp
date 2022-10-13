#include "behaviortree_cpp_v3/bt_factory.h"
#include <ament_index_cpp/get_package_share_directory.hpp>

#include "bt_tutorial02/nd_say_something.hpp"
#include "bt_tutorial02/nd_think_what_to_say.hpp"

int main()
{
  BT::BehaviorTreeFactory factory;
  factory.registerNodeType<SaySomething>("SaySomething");
  factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");

  BT::PortsList say_something_ports = {BT::InputPort<std::string>("message")};
  factory.registerSimpleAction(
    "SaySomething2",
    SaySomethingSimple,
    say_something_ports);

  const std::string tree_filename =
    ament_index_cpp::get_package_share_directory("bt_tutorial02") +
    "/trees/my_tree.xml";
  auto tree = factory.createTreeFromFile(tree_filename);

  tree.tickRoot();

  return EXIT_SUCCESS;
}
