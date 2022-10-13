#pragma once

#include <behaviortree_cpp_v3/bt_factory.h>


struct Pose2D
{
  double x, y, theta;
};

namespace BT
{
template<>
inline Pose2D convertFromString(StringView str)
{
  auto parts = splitString(str, ';');
  if (parts.size() != 3) {
    throw RuntimeError("invalid input");
  } else {
    Pose2D ret;
    ret.x = convertFromString<double>(parts[0]);
    ret.y = convertFromString<double>(parts[1]);
    ret.theta = convertFromString<double>(parts[2]);
    return ret;
  }
}
} // namespace BT


class MoveBaseAction : public BT::AsyncActionNode
{
private:
  std::atomic_bool halt_requested_;

public:
  MoveBaseAction(const std::string & name, const BT::NodeConfiguration & config)
  : BT::AsyncActionNode(name, config)
  {
  }

  static BT::PortsList providedPorts()
  {
    return {BT::InputPort<Pose2D>("goal")};
  }

  BT::NodeStatus tick() override;

  void halt() override
  {
    this->halt_requested_.store(true);
  }
};

BT::NodeStatus MoveBaseAction::tick()
{
  Pose2D goal;
  if (!this->getInput<Pose2D>("goal", goal)) {
    throw BT::RuntimeError("missing required input [goal]");
  }

  printf(
    "[ MoveBase: STARTED ] goal: x=%.1f y=%.1f theta=%.2f\n",
    goal.x, goal.y, goal.theta);

  this->halt_requested_.store(false);
  int count = 0;

  while (!this->halt_requested_ && count++ < 25) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  std::cout << "[ MoveBase: FINISHED ]" << std::endl;
  return this->halt_requested_ ?
         BT::NodeStatus::FAILURE : BT::NodeStatus::SUCCESS;
}
