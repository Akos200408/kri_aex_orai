#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

using namespace std::chrono_literals;

class SensorNode : public rclcpp::Node
{
public:
    SensorNode() : Node("sensor_node")
    {
        publisher_ = this->create_publisher<std_msgs::msg::Float32>(
            "/temperature", 10);

        timer_ = this->create_wall_timer(
            2s,
            std::bind(&SensorNode::publish_temperature, this));
    }

private:
    void publish_temperature()
    {
        std_msgs::msg::Float32 message;
        message.data = 25.5;

        RCLCPP_INFO(this->get_logger(),
                    "Temperature: %.1f C", message.data);

        publisher_->publish(message);
    }

    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SensorNode>());
    rclcpp::shutdown();
    return 0;
}
