#include <ament_index_cpp/get_package_share_directory.hpp>
#include <behaviortree_cpp_v3/bt_factory.h>

#include <behaviortree_cpp_v3/loggers/bt_file_logger.h>

#include "bt_tutorial02/nd_say_something.hpp"
#include "bt_tutorial04/nd_move_base_action.hpp"


int main()
{
  BT::BehaviorTreeFactory factory;
  factory.registerNodeType<SaySomething>("SaySomething");
  factory.registerNodeType<MoveBaseAction>("MoveBase");


  const std::string xml_file =
    ament_index_cpp::get_package_share_directory("bt_tutorial06") +
    "/trees/my_tree.xml";
  auto tree = factory.createTreeFromFile(xml_file);

  BT::FileLogger logger_file(tree, "bt_trace.fbl");

  BT::NodeStatus status = BT::NodeStatus::RUNNING;
  while (status == BT::NodeStatus::RUNNING) {
    status = tree.tickRoot();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

  }

  std::cout << "--------------" << std::endl;
  for (const auto & stack : tree.blackboard_stack) {
    stack->debugMessage();
    std::cout << "--------------" << std::endl;
  }

  return EXIT_SUCCESS;
}
