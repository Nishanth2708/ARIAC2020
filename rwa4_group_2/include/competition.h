#ifndef COMPETITION_H
#define COMPETITION_H

#include <vector>

#include <ros/ros.h>

#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <rosgraph_msgs/Clock.h>
#include <nist_gear/Order.h>
#include <nist_gear/LogicalCameraImage.h>
#include <nist_gear/Order.h>
#include <nist_gear/Proximity.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/Range.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <std_srvs/Trigger.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h> //--needed for tf2::Matrix3x3
#include <algorithm>
#include <vector>
#include <stdio.h>
#include "utils.h"


/**
 * @brief Competition class
 * 
 */
class Competition
{
public:
    explicit Competition(ros::NodeHandle & node);
    void init();

    void startCompetition();
    void endCompetition();


    void competition_state_callback(const std_msgs::String::ConstPtr & msg);
    void competition_clock_callback(const rosgraph_msgs::Clock::ConstPtr & msg);
    void breakbeam_sensor_callback(const nist_gear::Proximity::ConstPtr &msg);
    void logical_camera_callback(const nist_gear::LogicalCameraImage::ConstPtr &msg, int id);
    void quality_sensor_status_callback(const nist_gear::LogicalCameraImage::ConstPtr &msg);
    void quality_sensor_status_callback2(const nist_gear::LogicalCameraImage::ConstPtr &msg);
    part quality_sensor_status();
    part quality_sensor_status1();
    void order_callback(const nist_gear::Order::ConstPtr & msg);
    void print_order_callback();
    std::array<std::array<modelparam, 36>, 17> getter_logicam_callback();
    std::array<std::array<std::array<part, 10>, 5>, 5> getter_part_callback();
    double getClock();
    double getStartTime();
    bool beam_detect;
    std::string getCompetitionState();
    stats getStats(std::string function);
    std::vector<nist_gear::Order> received_orders_;


private:
    ros::NodeHandle node_;

    std::string competition_state_;
    double current_score_;
    ros::Time competition_clock_;
    double competition_start_time_; // wall time in sec

    ros::Subscriber current_score_subscriber_;
    ros::Subscriber competition_state_subscriber_;
    ros::Subscriber competition_clock_subscriber_;
    ros::Subscriber orders_subscriber_;
    ros::Subscriber fp_subscriber_,fp_subscriber1_,breakbeam_subscriber_;


    // to collect statistics
    stats init_;

};

#endif
