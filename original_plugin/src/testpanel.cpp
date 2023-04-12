#include <stdio.h>
#include <ros/ros.h>
#include <QLabel>
#include <QVBoxLayout>
#include "testpanel.h"

testpanel::testpanel(QWidget* parent)
    :rviz::Panel(parent) //初期化
{
    QVBoxLayout* layout = new QVBoxLayout; //ボックスレイアウト
    QLabel* label = new QLabel("Hello World!"); //ラベルオブジェクトを作成
    layout->addWidget(label);
    setLayout(layout);
}

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(testpanel, rviz::Panel)