#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

using namespace std::chrono_literals;

class SensorNode : public rclcpp::Node
{
public:
    SensorNode() : Node("sensor_node")
    {
        temperature_publisher_ =
            this->create_publisher<std_msgs::msg::Float32>(
                "/temperature", 10);

        humidity_publisher_ =
            this->create_publisher<std_msgs::msg::Float32>(
                "/humidity", 10);

        uv_publisher_ =
            this->create_publisher<std_msgs::msg::Float32>(
                "/uv_index", 10);

        timer_ = this->create_wall_timer(
            2s,
            std::bind(&SensorNode::publish_data, this));
    }

private:
    void publish_data()
    {
        std_msgs::msg::Float32 temperature;
        std_msgs::msg::Float32 humidity;
        std_msgs::msg::Float32 uv_index;

        temperature.data = 25.5;
        humidity.data = 48.0;
        uv_index.data = 3.2;

        temperature_publisher_->publish(temperature);
        humidity_publisher_->publish(humidity);
        uv_publisher_->publish(uv_index);

        RCLCPP_INFO(
            this->get_logger(),
            "Temperature: %.1f C | Humidity: %.1f %% | UV index: %.1f",
            temperature.data,
            humidity.data,
            uv_index.data);
    }

    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr
        temperature_publisher_;

    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr
        humidity_publisher_;

    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr
        uv_publisher_;

    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SensorNode>());
    rclcpp::shutdown();

    return 0;
}
