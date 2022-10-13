#pragma once
#include <behaviortree_cpp_v3/bt_factory.h>


class ApproachObject : public BT::SyncActionNode
{
public:
  ApproachObject(const std::string & name)
  : BT::SyncActionNode(name, {})
  {
  }

  BT::NodeStatus tick() override
  {
    std::cout << "ApproachObject: " << this->name() << std::endl;
    return BT::NodeStatus::SUCCESS;
  }
};
