#include "behaviortree_cpp_v3/bt_factory.h"
#include <ament_index_cpp/get_package_share_directory.hpp>


class SaySomething : public BT::SyncActionNode
{
public:
  SaySomething(const std::string & name, const BT::NodeConfiguration & config)
  : BT::SyncActionNode(name, config)
  {
  }

  static BT::PortsList providedPorts()
  {
    return {BT::InputPort<std::string>("message")};
  }

  BT::NodeStatus tick() override
  {
    BT::Optional<std::string> msg = this->getInput<std::string>("message");

    if (!msg) {
      throw BT::RuntimeError("missing required input [message]: ", msg.error());
    }

    std::cout << "Robot says: " << msg.value() << std::endl;
    return BT::NodeStatus::SUCCESS;
  }
};

BT::NodeStatus SaySomethingSimple(BT::TreeNode & self)
{
  BT::Optional<std::string> msg = self.getInput<std::string>("message");

  if (!msg) {
    throw BT::RuntimeError("missing required input [message]: ", msg.error());
  }

  std::cout << "Robot says: " << msg.value() << std::endl;
  return BT::NodeStatus::SUCCESS;
}

class ThinkWhatToSay : public BT::SyncActionNode
{
public:
  ThinkWhatToSay(const std::string & name, const BT::NodeConfiguration & config)
  : BT::SyncActionNode(name, config)
  {
  }

  static BT::PortsList providedPorts()
  {
    return {BT::OutputPort<std::string>("text")};
  }

  BT::NodeStatus tick() override
  {
    this->setOutput("text", "The answer is 42");
    return BT::NodeStatus::SUCCESS;
  }
};


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
