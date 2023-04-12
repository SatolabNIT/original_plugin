//ROS_INFOを表示するボタンのプラグイン
#include <stdio.h>
#include <ros/ros.h>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSlider>
#include <std_msgs/String.h>
#include "mypanel5.h"

mypanel5::mypanel5(QWidget* parent):rviz::Panel(parent) //初期化
{
    start_button=new QPushButton("start");
    stop_button=new QPushButton("stop");
    slider=new QSlider(Qt::Horizontal,this);
    QPalette start_palette = start_button -> palette();//ボタンの背景色を変える、ここから
    start_palette.setColor(QPalette::ButtonText,Qt::red);
    start_button->setAutoFillBackground(true);
    start_button->setPalette(start_palette);
    //ここまで
    QVBoxLayout* layout = new QVBoxLayout; //ボックスレイアウト
    layout->addWidget(start_button);
    layout->addWidget(stop_button);
    layout->addWidget(slider);
    setLayout(layout);
    // connect(slider,SIGNAL(sliderMoved(int)),this,SLOT(slider_move(int)));
    connect(start_button,&QPushButton::clicked,this,&mypanel5::start_push);
    connect(stop_button,&QPushButton::clicked,this,&mypanel5::stop_push);
}
void mypanel5::start_push(){
    std_msgs::String string;
    string.data="start";
    ROS_INFO("%s",string.data.c_str());
}

void mypanel5::stop_push(){
    std_msgs::String string;
    string.data="stop";
    ROS_INFO("%s",string.data.c_str());
}

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mypanel5, rviz::Panel)