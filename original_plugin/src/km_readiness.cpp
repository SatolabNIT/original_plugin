//rviz上にボタンを配置し、onボタンで任意のroslaunchを起動し、offボタンでlaunchによって起動したnodeをkillする。
//ROS_INFOを表示するボタンのプラグイン
#include <stdio.h>
#include <ros/ros.h>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSlider>
#include <std_msgs/String.h>
#include "km_readiness.h"

namespace bp = boost::process;
km_readiness::km_readiness(QWidget* parent):rviz::Panel(parent) //初期化
{
  setButton1 = new QPushButton("glipper open");
  setButton2 = new QPushButton("glipper close");
  setButton3 = new QPushButton("reset button");
  label1 = new QLabel("press key", this);
  label2=new QLabel("",this);
  label3=new QLabel("",this);

  QPalette palette = setButton1->palette();
  palette.setColor(QPalette::Button, Qt::red);
  setButton1->setAutoFillBackground(true);
  setButton1->setPalette(palette);
  palette.setColor(QPalette::Button, Qt::green);
  setButton2->setAutoFillBackground(true);
  setButton2->setPalette(palette);
  palette.setColor(QPalette::Button, Qt::blue);
  setButton3->setAutoFillBackground(true);
  setButton3->setPalette(palette);


  connect(setButton1,SIGNAL(clicked()),this,SLOT(pushbutton()));
  connect(setButton2,SIGNAL(clicked()),this,SLOT(pushbutton_b()));
  connect(setButton3,SIGNAL(clicked()),this,SLOT(pushbutton_reset()));



//QVBoxLayout* layout = new QVBoxLayout;
QGridLayout* layout =new QGridLayout(parent);
const QSize btnSize = QSize(200, 100);
setButton1->setFixedSize(btnSize);
setButton2->setFixedSize(btnSize);
setButton3->setFixedSize(btnSize);
layout->setSpacing(0);

layout->addWidget(label1);
layout->addWidget(setButton1);
layout->addWidget(setButton2);
layout->addWidget(label2);
layout->addWidget(setButton3);
layout->addWidget(label3);
setLayout(layout);
}

void km_readiness::pushbutton(){
//   ROS_INFO("");
  glipper_move(1);
}

void km_readiness::pushbutton_b(){
    // ROS_INFO("Pushed release Button");
    glipper_move(2);
}

void km_readiness::glipper_move(int i){//
    // std_msgs::Float32MultiArray array;
    // std::cout<<i<<std::endl;
    if(i==1){
         // roslaunch実行
        std::string pkg_path = ros::package::getPath("basic_lecture");//pkg名を指定
        std::string launch_file = pkg_path + "/launch/pubsub1.launch";///launchファイルを指定
        //gnome-terminal で新たなターミナルを起動し、そこで設定したlaunchを起動するコマンド名
        // std::string command="gnome-terminal -- cd catkin_ws_4";
        // std::string roslaunch_command = "roslaunch " + launch_file;
        // std::string roslaunch_command = "gnome-terminal -- roslaunch " + launch_file;
        std::string termi = "terminator"
        std::string roslaunch_command = "gnome-terminal -- roslaunch " + launch_file;
        // system(command.c_str());//launchファイル起動
        system(roslaunch_command.c_str());//launchファイル起動
    }
    if(i==2){
        std::string kill1 = "rosnode kill /basic_simple_listener";//killするnodeを設定する
        std::string kill2 = "rosnode kill /basic_simple_talker";
        int res1 = std::system(kill1.c_str());//nodeをkillする
        int res2 = std::system(kill2.c_str());
    }
}

void km_readiness::pushbutton_reset(){
  std_msgs::Float32MultiArray reset;
  reset.data.resize(1);
  reset.data[0] = -1.0f;
  pub1.publish(reset);
}

// void km_readiness::keyPressEvent(QKeyEvent *event)
// {  switch (event->key()) {
//        // case Qt::Key_E:  label1->setText("EMERGENCY STOP!!");/*qDebug("keyPress %x", event->key()); */MainDialog::pushbutton();  break;
//         //case Qt::Key_R:  label1->setText("Power ON");/*qDebug("keyPress %x", event->key());*/ MainDialog::pushbutton_b(); break;
//         default: label1->setText(event->text());break;
//     }
// }

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(km_readiness, rviz::Panel)