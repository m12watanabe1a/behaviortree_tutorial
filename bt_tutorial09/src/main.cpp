#include <behaviortree_cpp_v3/bt_factory.h>


class MyAsyncAction : public BT::CoroActionNode
{
public:
  MyAsyncAction(const std::string & name)
  : BT::CoroActionNode(name, {})
  {}

private:
  BT::NodeStatus tick() override
  {
    std::cout << name() << ": Started. Send Request to server." << std::endl;

    auto Now = []() {return std::chrono::high_resolution_clock::now();};

    BT::TimePoint initial_time = Now();
    BT::TimePoint time_before_reply = initial_time + std::chrono::milliseconds(100);

    int count = 0;
    bool reply_received = false;

    while (!reply_received) {
      if (count++ == 0) {
        // call this only once
        std::cout << name() << ": Waiting Reply..." << std::endl;
      }
      // pretend that we received a reply
      if (Now() >= time_before_reply) {
        reply_received = true;
      }

      if (!reply_received) {
        // set status to RUNNING and "pause/sleep"
        // If halt() is called, we will not resume execution (stack destroyed)
        setStatusRunningAndYield();
      }
    }

    // This part of the code is never reached if halt() is invoked,
    // only if reply_received == true;
    std::cout << name() << ": Done. 'Waiting Reply' loop repeated " << count << " times" <<
      std::endl;
    cleanup(false);
    return BT::NodeStatus::SUCCESS;
  }

  // you might want to cleanup differently if it was halted or successful
  void cleanup(bool halted)
  {
    if (halted) {
      std::cout << name() << ": cleaning up after an halt()\n" << std::endl;
    } else {
      std::cout << name() << ": cleaning up after SUCCESS\n" << std::endl;
    }
  }
  void halt() override
  {
    std::cout << name() << ": Halted." << std::endl;
    cleanup(true);
    // Do not forget to call this at the end.
    BT::CoroActionNode::halt();
  }
};


static const char * xml_text =
  R"(
<root >
  <BehaviorTree>
    <Timeout msec="150">
      <SequenceStar name="sequence">
        <MyAsyncAction name="action_A"/>
        <MyAsyncAction name="action_B"/>
      </SequenceStar>
    </Timeout>
  </BehaviorTree>
</root>
)";


int main()
{
  BT::BehaviorTreeFactory factory;
  factory.registerNodeType<MyAsyncAction>("MyAsyncAction");

  auto tree = factory.createTreeFromText(xml_text);

  while (tree.tickRoot() == BT::NodeStatus::RUNNING) {
    std::this_thread::sleep_for(
      std::chrono::milliseconds(10));
  }

  return EXIT_SUCCESS;
}
