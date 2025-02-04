#include <memory>
#include <rclcpp/rclcpp.hpp>

class ParameterTest : public rclcpp::Node
{
public:
  explicit ParameterTest(const rclcpp::NodeOptions &options) : Node("param_test", options)
  {
    std::string param = this->declare_parameter<std::string>("param", "node-defaulted param");
    RCLCPP_INFO_STREAM(get_logger(), "param is " << param);
  }

  ~ParameterTest() = default;

private:
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  rclcpp::executors::MultiThreadedExecutor executor;

  rclcpp::NodeOptions options;
  auto node = std::make_shared<ParameterTest>(options);
  executor.add_node(node);

  executor.spin();

  rclcpp::shutdown();
  return 0;
}
