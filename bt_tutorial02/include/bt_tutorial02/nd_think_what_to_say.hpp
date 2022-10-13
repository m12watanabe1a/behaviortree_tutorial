#pragma once
#include <behaviortree_cpp_v3/bt_factory.h>

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
