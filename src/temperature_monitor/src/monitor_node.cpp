#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

class MonitorNode : public rclcpp::Node
{
public:
    MonitorNode() : Node("monitor_node")
    {
        temperature_subscription_ =
            this->create_subscription<std_msgs::msg::Float32>(
                "/temperature",
                10,
                std::bind(
                    &MonitorNode::temperature_callback,
                    this,
                    std::placeholders::_1));

        humidity_subscription_ =
            this->create_subscription<std_msgs::msg::Float32>(
                "/humidity",
                10,
                std::bind(
                    &MonitorNode::humidity_callback,
                    this,
                    std::placeholders::_1));

        uv_subscription_ =
            this->create_subscription<std_msgs::msg::Float32>(
                "/uv_index",
                10,
                std::bind(
                    &MonitorNode::uv_callback,
                    this,
                    std::placeholders::_1));
    }

private:
    void temperature_callback(
        const std_msgs::msg::Float32::SharedPtr msg)
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Temperature: %.1f C",
            msg->data);
    }

    void humidity_callback(
        const std_msgs::msg::Float32::SharedPtr msg)
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Humidity: %.1f %%",
            msg->data);
    }

    void uv_callback(
        const std_msgs::msg::Float32::SharedPtr msg)
    {
        RCLCPP_INFO(
            this->get_logger(),
            "UV index: %.1f",
            msg->data);
    }

    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr
        temperature_subscription_;

    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr
        humidity_subscription_;

    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr
        uv_subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MonitorNode>());
    rclcpp::shutdown();

    return 0;
}
