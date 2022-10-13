#pragma once

#include <behaviortree_cpp_v3/bt_factory.h>

BT::NodeStatus CheckBattery()
{
  std::cout << "[ Battery: OK ]" << std::endl;
  return BT::NodeStatus::SUCCESS;
}
