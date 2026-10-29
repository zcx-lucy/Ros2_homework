#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "my_interface/msg/point_xy.hpp"

class PointSubscriber : public rclcpp::Node {
public:
    PointSubscriber() : Node("point_subscriber") {
        subscription_ = this->create_subscription<my_interface::msg::PointXY>(
            "point_topic", 10,
            std::bind(&PointSubscriber::topic_callback, this, std::placeholders::_1));
    }
private:
    void topic_callback(const my_interface::msg::PointXY::SharedPtr msg) const {
        RCLCPP_INFO(this->get_logger(), "Received -> X: %.2f, Y: %.2f", msg->x, msg->y);
    }
    rclcpp::Subscription<my_interface::msg::PointXY>::SharedPtr subscription_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PointSubscriber>());
    rclcpp::shutdown();
    return 0;
}