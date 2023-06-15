#include <memory>
#include <rclcpp/rclcpp.hpp>

#include "parameter_test_parameters.hpp"

class ParameterTest : public rclcpp::Node
{
public:
  explicit ParameterTest(const rclcpp::NodeOptions & options);

  ~ParameterTest() = default;

private:
  std::shared_ptr<parameter_test::ParamListener> param_listener_;
  parameter_test::Params params_;
};

ParameterTest::ParameterTest(const rclcpp::NodeOptions & options) : Node("param_test", options)
{
  param_listener_ = std::make_shared<parameter_test::ParamListener>(get_node_parameters_interface());
  if (!param_listener_) {
    RCLCPP_ERROR(get_logger(), "Error allocating parameter listener");
    throw std::runtime_error(std::string("Could not allocate parameter listener"));
  }
  params_ = param_listener_->get_params();

  RCLCPP_INFO(get_logger(), "Test Double = %f", params_.test_double);
}

int main(int argc, char ** argv)
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
