//original_plugin/src/rviz/tool/point_tool.cpp
//ros講座102
#include "mypanel3.h"
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreEntity.h>
#include <ros/ros.h>
#include <rviz/viewport_mouse_event.h>
#include <rviz/visualization_manager.h>
#include <rviz/geometry.h>
#include <rviz/ogre_helpers/shape.h>
#include <rviz/frame_manager.h>
#include <geometry_msgs/PointStamped.h>
#include <pluginlib/class_list_macros.h>

namespace original_plugin
{
mypanel3::mypanel3() : nh_()
{
  shortcut_key_ = 'm';//ショートカットキーの登録
}

mypanel3::~mypanel3()
{
}

void mypanel3::onInitialize()//初期化処理
{//vis_shape_はRvizの3Dビューの中で円柱を表示するためのクラス
  vis_shape_.reset(new rviz::Shape(rviz::Shape::Cylinder, scene_manager_));
  Ogre::Vector3 shape_pos(0, 2, 0);//activeになったら、shape_posというベクトルを設定
  vis_shape_->setPosition(shape_pos);//初期位置を設定
  Ogre::Quaternion shape_q(0.7, 0.7, 0, 0);//(いまいちわからない、値を変更すると回転する)
  vis_shape_->setOrientation(shape_q);//形を設定する
  vis_shape_->setColor(0, 0, 1, 1);//図形の色を設定
  vis_shape_->getRootNode()->setVisible(false);//falseでは、表示されない

  point_pub_ = nh_.advertise<geometry_msgs::PointStamped>("point", 10);//publishする
}

void mypanel3::activate()//ツールが選択されると動く関数（ツールボタンを押されると）
{
  vis_shape_->setColor(0, 0, 1, 1);//図形の色を設定
  vis_shape_->getRootNode()->setVisible(true);//上はfalseで、activeになることでtrueとなり、表示される
}

void mypanel3::deactivate()//ツールの選択が解除されると動く関数
{
  vis_shape_->setColor(0.5, 0.5, 0.5, 1);//図形の色を設定
}

int mypanel3::processMouseEvent(rviz::ViewportMouseEvent& event)//3Dビューの上にマウスが来ると動く関数
//これ以外にもイベントを指定できる
{
  Ogre::Vector3 intersection;
  Ogre::Plane ground_plane(Ogre::Vector3::UNIT_Z, 0.0f);
  if (rviz::getPointOnPlaneFromWindowXY(event.viewport, ground_plane, event.x, event.y, intersection))
  {//rviz::getPointOnPlaneFromWindowXYは、ユーザーのマウスが設置平面のどこを指しているのかを示す
    vis_shape_->setPosition(intersection);//おく物体の位置を設定
    if (event.leftDown())
    {
      geometry_msgs::PointStamped point_msg;//pointStampedの型のメッセージ
      point_msg.header.frame_id = context_->getFrameManager()->getFixedFrame(); //idの取得
      point_msg.header.stamp = ros::Time::now();//Timestampに時間を表示
      point_msg.point.x = intersection.x;//x座標
      point_msg.point.y = intersection.y;//y座標
      point_msg.point.z = intersection.z;//z座標の値
      point_pub_.publish(point_msg);//rostopic echo /point で、値を取得できる（上の部分）
      return Render | Finished;//Renderは描画イベントを起こす Finishedはツールの選択が解除される
      //            |は、どちらもreturnする
    }
  }
  return Render;//return でrvizに指令を送れる
}

}  // namespace original_plugin
PLUGINLIB_EXPORT_CLASS(original_plugin::mypanel3, rviz::Tool)