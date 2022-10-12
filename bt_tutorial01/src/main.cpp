#include <behaviortree_cpp_v3/bt_factory.h>
#include <ament_index_cpp/get_package_share_directory.hpp>

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

BT::NodeStatus CheckBattery()
{
  std::cout << "[ Battery: OK ]" << std::endl;
  return BT::NodeStatus::SUCCESS;
}

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

int main()
{
  BT::BehaviorTreeFactory factory;

  factory.registerNodeType<ApproachObject>("ApproachObject");

  factory.registerSimpleCondition("CheckBattery", std::bind(CheckBattery));

  GripperInterface gripper;
  factory.registerSimpleAction(
    "OpenGripper",
    std::bind(&GripperInterface::open, &gripper));
  factory.registerSimpleAction(
    "CloseGripper",
    std::bind(&GripperInterface::close, &gripper));

  const std::string tree_filename =
    ament_index_cpp::get_package_share_directory("bt_tutorial01") +
    "/trees/my_tree.xml";
  auto tree = factory.createTreeFromFile(tree_filename);

  tree.tickRoot();
  return 0;
}
