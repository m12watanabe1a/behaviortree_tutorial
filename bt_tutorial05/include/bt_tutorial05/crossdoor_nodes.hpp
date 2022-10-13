#pragma once

#include "behaviortree_cpp_v3/bt_factory.h"


class CrossDoorInterface
{
private:
  static bool door_open_;
  static bool door_locked_;

public:
  static BT::NodeStatus IsDoorOpen();
  static BT::NodeStatus IsDoorLocked();
  static BT::NodeStatus UnlockDoor();
  static BT::NodeStatus PassThroughDoor();
  static BT::NodeStatus PassThroughWindow();
  static BT::NodeStatus OpenDoor();
  static BT::NodeStatus CloseDoor();

  static void RegisterNodes(BT::BehaviorTreeFactory &);
};
