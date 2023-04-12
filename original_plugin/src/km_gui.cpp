//ROS_INFOを表示するボタンのプラグイン
#include <stdio.h>
#include <ros/ros.h>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSlider>
#include <std_msgs/String.h>
#include "km_gui.h"

km_gui::km_gui(QWidget* parent):rviz::Panel(parent) //初期化
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

void km_gui::pushbutton(){
//   ROS_INFO("");
  glipper_move(1);
}

void km_gui::pushbutton_b(){
    // ROS_INFO("Pushed release Button");
    glipper_move(2);
}

void km_gui::glipper_move(int i){//
    // std_msgs::Float32MultiArray array;
    // std::cout<<i<<std::endl;
    if(i==1){
        array.data.resize(1);
        array.data[0] = -1.0f;
        pub.publish(array);
    }
    if(i==2){
        array.data.resize(1);
        array.data[0] = 1.0f;
        pub.publish(array);
    }
}

void km_gui::pushbutton_reset(){
  std_msgs::Float32MultiArray reset;
  reset.data.resize(1);
  reset.data[0] = -1.0f;
  pub1.publish(reset);
}

// void km_gui::keyPressEvent(QKeyEvent *event)
// {  switch (event->key()) {
//        // case Qt::Key_E:  label1->setText("EMERGENCY STOP!!");/*qDebug("keyPress %x", event->key()); */MainDialog::pushbutton();  break;
//         //case Qt::Key_R:  label1->setText("Power ON");/*qDebug("keyPress %x", event->key());*/ MainDialog::pushbutton_b(); break;
//         default: label1->setText(event->text());break;
//     }
// }

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(km_gui, rviz::Panel)