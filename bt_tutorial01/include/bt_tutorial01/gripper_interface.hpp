#pragma once
#include <behaviortree_cpp_v3/bt_factory.h>

class GripperInterface
{
private:
  bool open_;

public:
  GripperInterface()
  : open_(false) {}

  BT::NodeStatus open()
  {
    this->open_ = true;
    std::cout << "GripperInterface::open" << std::endl;
    return BT::NodeStatus::SUCCESS;
  }

  BT::NodeStatus close()
  {
    std::cout << "GripperInterface::close" << std::endl;
    this->open_ = false;
    return BT::NodeStatus::SUCCESS;
  }
};
