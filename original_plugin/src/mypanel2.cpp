//ROS_INFOを表示するボタンのプラグイン
#include <stdio.h>
#include <ros/ros.h>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSlider>
#include <std_msgs/String.h>
#include "mypanel2.h"

mypanel2::mypanel2(QWidget* parent):rviz::Panel(parent) //初期化
{
    start_button=new QPushButton("start");
    stop_button=new QPushButton("stop");
    slider=new QSlider(Qt::Horizontal,this);
    QVBoxLayout* layout = new QVBoxLayout; //ボックスレイアウト
    layout->addWidget(start_button);
    layout->addWidget(stop_button);
    layout->addWidget(slider);
    setLayout(layout);
    // connect(slider,SIGNAL(sliderMoved(int)),this,SLOT(slider_move(int)));
    connect(start_button,&QPushButton::clicked,this,&mypanel2::start_push);
    connect(stop_button,&QPushButton::clicked,this,&mypanel2::stop_push);
}
void mypanel2::start_push(){
    std_msgs::String string;
    string.data="start";
    ROS_INFO("%s",string.data.c_str());
}

void mypanel2::stop_push(){
    std_msgs::String string;
    string.data="stop";
    ROS_INFO("%s",string.data.c_str());
}

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mypanel2, rviz::Panel)