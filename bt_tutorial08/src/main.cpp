#include <behaviortree_cpp_v3/bt_factory.h>

class ActionA : public BT::SyncActionNode
{
private:
  int arg1_;
  double arg2_;
  std::string arg3_;

public:
  ActionA(
    const std::string & name,
    const BT::NodeConfiguration & config,
    const int arg1, const double arg2, const std::string & arg3)
  : BT::SyncActionNode(name, config),
    arg1_(arg1), arg2_(arg2), arg3_(arg3)
  {}

  BT::NodeStatus tick() override
  {
    std::cout <<
      "ActinA: " <<
      this->arg1_ << " / " << this->arg2_ << " / " << this->arg3_ <<
      std::endl;

    return BT::NodeStatus::SUCCESS;
  }

  static BT::PortsList providedPorts()
  {
    return {};
  }
};


class ActionB : public BT::SyncActionNode
{
private:
  int arg1_;
  double arg2_;
  std::string arg3_;

public:
  ActionB(const std::string & name, const BT::NodeConfiguration & config)
  : BT::SyncActionNode(name, config)
  {}

  void init(const int arg1, const double arg2, const std::string & arg3)
  {
    this->arg1_ = arg1;
    this->arg2_ = arg2;
    this->arg3_ = arg3;
  }

  BT::NodeStatus tick() override
  {
    std::cout <<
      "ActinB: " <<
      this->arg1_ << " / " << this->arg2_ << " / " << this->arg3_ <<
      std::endl;

    return BT::NodeStatus::SUCCESS;
  }

  static BT::PortsList providedPorts()
  {
    return {};
  }
};


static const char * xml_text =
  R"(
<root>
  <BehaviorTree>
    <Sequence>
      <Action_A/>
      <Action_B/>
    </Sequence>
  </BehaviorTree>
</root>
 )";

int main()
{
  BT::BehaviorTreeFactory factory;

  BT::NodeBuilder builder_A = [](
    const std::string & name,
    const BT::NodeConfiguration & config) {
      return std::make_unique<ActionA>(
        name, config, 42, 3.14, "hello world");
    };

  factory.registerBuilder<ActionA>("Action_A", builder_A);

  factory.registerNodeType<ActionB>("Action_B");

  auto tree = factory.createTreeFromText(xml_text);

  for (auto & node : tree.nodes) {
    if (auto action_B_node = dynamic_cast<ActionB *>(node.get())) {
      action_B_node->init(69, 9.99, "interesting_value");
    }
  }

  while (tree.tickRoot() == BT::NodeStatus::RUNNING) {
    std::this_thread::sleep_for(
      std::chrono::milliseconds(10));
  }

  return EXIT_SUCCESS;
}
