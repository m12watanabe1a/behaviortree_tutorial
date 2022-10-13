#include <ament_index_cpp/get_package_share_directory.hpp>
#include <behaviortree_cpp_v3/bt_factory.h>

// ------------------------------------------------------------
#include <behaviortree_cpp_v3/loggers/bt_cout_logger.h>
#include <behaviortree_cpp_v3/loggers/bt_file_logger.h>
#include <behaviortree_cpp_v3/loggers/bt_minitrace_logger.h>
// ------------------------------------------------------------

#include "bt_tutorial05/crossdoor_nodes.hpp"


int main(int argc, char ** argv)
{
  BT::BehaviorTreeFactory factory;

  CrossDoorInterface::RegisterNodes(factory);

  const std::string tree_filename =
    ament_index_cpp::get_package_share_directory("bt_tutorial05") +
    "/trees/my_tree.xml";
  auto tree = factory.createTreeFromFile(tree_filename);

  BT::StdCoutLogger logger_cout(tree);
  BT::FileLogger logger_file(tree, "bt_trace.fbl");
  BT::MinitraceLogger logger_minitrace(tree, "bt_trace.json");

#ifdef ZMQ_FOUND
  // This logger publish status changes using ZeroMQ. Used by Groot
  PublisherZMQ publisher_zmq(tree);
#endif

  BT::printTreeRecursively(tree.rootNode());

  const bool LOOP = (argc == 2 && strcmp(argv[1], "loop") == 0);

  BT::NodeStatus status = tree.tickRoot();
  while (LOOP || status == BT::NodeStatus::RUNNING) {
    // NOTE:
    //   sleep function for BT::Tree is not implemented current ROS package
    //   Use thread sleep instead for just testing

    // tree.sleep(std::chrono::milliseconds(10));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    status = tree.tickRoot();
  }

  return EXIT_SUCCESS;
}
