#include <memory>
#include <rclcpp/rclcpp.hpp>

class ParameterTest : public rclcpp::Node
{
public:
  explicit ParameterTest(const rclcpp::NodeOptions &options) : Node("param_test", options)
  {
    std::string test_string1 = this->declare_parameter<std::string>("test_string1", "default string1");
    RCLCPP_INFO_STREAM(get_logger(), "test_string1 is " << test_string1);

    std::string test_string2 = this->declare_parameter<std::string>("test_string2", "default string1");
    RCLCPP_INFO_STREAM(get_logger(), "test_string2 is " << test_string2);
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
