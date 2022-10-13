#include <behaviortree_cpp_v3/bt_factory.h>

struct Position2D
{
  double x;
  double y;
};


namespace BT
{
template<>
inline Position2D convertFromString(StringView str)
{
  printf("Converting string: \"%s\"\n", str.data());

  auto parts = splitString(str, ';');
  if (parts.size() != 2) {
    throw RuntimeError("invalid input");
  } else {
    Position2D output;
    output.x = convertFromString<double>(parts[0]);
    output.y = convertFromString<double>(parts[1]);
    return output;
  }
}
} // namespace BT


class CalculateGoal : public BT::SyncActionNode
{
public:
  CalculateGoal(const std::string & name, const BT::NodeConfiguration & config)
  : BT::SyncActionNode(name, config)
  {}

  static BT::PortsList providedPorts()
  {
    return {BT::OutputPort<Position2D>("goal")};
  }

  BT::NodeStatus tick() override
  {
    Position2D my_goal = {1.1, 2.3};
    this->setOutput<Position2D>("goal", my_goal);
    return BT::NodeStatus::SUCCESS;
  }
};

class PrintTarget : public BT::SyncActionNode
{
public:
  PrintTarget(const std::string & name, const BT::NodeConfiguration & config)
  : BT::SyncActionNode(name, config)
  {
  }

  static BT::PortsList providedPorts()
  {
    const char * description = "Simply print the goal on console....";
    return {BT::InputPort<Position2D>("target", description)};
  }

  BT::NodeStatus tick() override
  {
    auto res = this->getInput<Position2D>("target");
    if (!res) {
      throw BT::RuntimeError("error reading port [target]:", res.error());
    }

    Position2D target = res.value();
    printf("Target positions : [%.1f, %.1f]\n", target.x, target.y);
    return BT::NodeStatus::SUCCESS;
  }
};


static const char * xml_text =
  R"(
<root main_tree_to_execute = "MainTree" >
  <BehaviorTree ID="MainTree">
    <SequenceStar name="root">
      <CalculateGoal   goal="{GoalPosition}" />
      <PrintTarget     target="{GoalPosition}" />
      <SetBlackboard   output_key="OtherGoal" value="-1;3" />
      <PrintTarget     target="{OtherGoal}" />
    </SequenceStar>
  </BehaviorTree>
</root>
)";


int main()
{
  BT::BehaviorTreeFactory factory;
  factory.registerNodeType<CalculateGoal>("CalculateGoal");
  factory.registerNodeType<PrintTarget>("PrintTarget");

  auto tree = factory.createTreeFromText(xml_text);
  tree.tickRoot();

  return EXIT_SUCCESS;
}
