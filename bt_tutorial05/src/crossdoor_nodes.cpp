#include "bt_tutorial05/crossdoor_nodes.hpp"


BT_REGISTER_NODES(factory)
{
  CrossDoorInterface::RegisterNodes(factory);
}

bool CrossDoorInterface::door_open_ = false;
bool CrossDoorInterface::door_locked_ = true;

inline void sleepMs(int ms)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

BT::NodeStatus CrossDoorInterface::IsDoorOpen()
{
  sleepMs(500);
  return CrossDoorInterface::door_open_ ?
         BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
}

BT::NodeStatus CrossDoorInterface::IsDoorLocked()
{
  sleepMs(500);
  return CrossDoorInterface::door_locked_ ?
         BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
}

BT::NodeStatus CrossDoorInterface::UnlockDoor()
{
  if (CrossDoorInterface::door_locked_) {
    sleepMs(2000);
    CrossDoorInterface::door_locked_ = false;
  }
  return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus CrossDoorInterface::PassThroughDoor()
{
  sleepMs(1000);
  return CrossDoorInterface::door_open_ ?
         BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
}


BT::NodeStatus CrossDoorInterface::PassThroughWindow()
{
  sleepMs(1000);
  return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus CrossDoorInterface::OpenDoor()
{
  if (CrossDoorInterface::door_locked_) {
    return BT::NodeStatus::FAILURE;
  }

  sleepMs(2000);
  CrossDoorInterface::door_open_ = true;
  return BT::NodeStatus::SUCCESS;
}


BT::NodeStatus CrossDoorInterface::CloseDoor()
{
  if (CrossDoorInterface::door_open_) {
    sleepMs(1500);
    CrossDoorInterface::door_open_ = false;
  }

  return BT::NodeStatus::SUCCESS;
}

void CrossDoorInterface::RegisterNodes(BT::BehaviorTreeFactory & factory)
{
  factory.registerSimpleCondition(
    "IsDoorOpen", std::bind(CrossDoorInterface::IsDoorOpen));
  factory.registerSimpleAction(
    "PassThroughDoor", std::bind(CrossDoorInterface::PassThroughDoor));
  factory.registerSimpleAction(
    "PassThroughWindow", std::bind(CrossDoorInterface::PassThroughWindow));
  factory.registerSimpleAction(
    "OpenDoor", std::bind(CrossDoorInterface::OpenDoor));
  factory.registerSimpleAction(
    "CloseDoor", std::bind(CrossDoorInterface::CloseDoor));
  factory.registerSimpleCondition(
    "IsDoorLocked", std::bind(CrossDoorInterface::IsDoorLocked));
  factory.registerSimpleAction(
    "UnlockDoor", std::bind(CrossDoorInterface::UnlockDoor));
}
