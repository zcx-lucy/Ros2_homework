#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "my_interface/msg/point_xy.hpp"

using namespace std::chrono_literals;

class PointPublisher : public rclcpp::Node {
public:
    PointPublisher() : Node("point_publisher"), count_(0.0) {
        publisher_ = this->create_publisher<my_interface::msg::PointXY>("point_topic", 10);
        timer_ = this->create_wall_timer(1s, std::bind(&PointPublisher::timer_callback, this));
    }
private:
    void timer_callback() {
        auto message = my_interface::msg::PointXY();
        message.x = count_;
        message.y = count_ * 2.0;
        RCLCPP_INFO(this->get_logger(), "Publishing: x=%.2f, y=%.2f", message.x, message.y);
        publisher_->publish(message);
        count_ += 1.0;
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<my_interface::msg::PointXY>::SharedPtr publisher_;
    double count_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PointPublisher>());
    rclcpp::shutdown();
    return 0;
}