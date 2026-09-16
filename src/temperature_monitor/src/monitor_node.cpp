#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

class MonitorNode : public rclcpp::Node
{
public:
    MonitorNode() : Node("monitor_node")
    {
        subscription_ = this->create_subscription<std_msgs::msg::Float32>(
            "/temperature",
            10,
            std::bind(&MonitorNode::temperature_callback, this, std::placeholders::_1));
    }

private:
    void temperature_callback(const std_msgs::msg::Float32::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(),
                    "Received temperature: %.1f C", msg->data);
    }

    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MonitorNode>());
    rclcpp::shutdown();
    return 0;
}
