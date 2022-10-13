#include "bt_tutorial02/nd_say_something.hpp"
#include <ament_index_cpp/get_package_share_directory.hpp>
#include <behaviortree_cpp_v3/bt_factory.h>

int main()
{
  // This tutorial is not supported on galactic
  const std::string tree_dir = ament_index_cpp::get_package_share_directory(
    "bt_tutorial07") + "/trees/";

  BT::BehaviorTreeFactory factory;
  factory.registerNodeType<SaySomething>("SaySomething");

  factory.registerBehaviorTreeFromFile(tree_dir + "main_tree.xml");
  factory.registerBehaviorTreeFromFile(tree_dir + "subtree_A.xml");
  factory.registerBehaviorTreeFromFile(tree_dir + "subtree_B.xml");

  std::cout << "Registered BehaviorTrees:" << std::endl;
  for (const std::string & bt_name : factory.registeredBehaviorTrees()) {
    std::cout << " - " << bt_name << std::endl;
  }

  std::cout << "----- MainTree tick ----" << std::endl;
  auto main_tree = factory.createTree("MainTree");
  main_tree.tickRoot();

  std::cout << "----- SubA tick ----" << std::endl;
  auto subA_tree = factory.createTree("SubTreeA");
  subA_tree.tickRoot();

  return EXIT_SUCCESS;
}
