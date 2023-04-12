//point_display.cpp
//ros講座111
#include "mypanel4.h"
#include <OGRE/OgreSceneNode.h>//scenenode使うのに必要
#include <OGRE/OgreSceneManager.h>
#include <tf/transform_listener.h>
#include <rviz/visualization_manager.h>
#include <rviz/properties/color_property.h>
#include <rviz/properties/float_property.h>
#include <rviz/properties/int_property.h>
#include <rviz/frame_manager.h>
#include <pluginlib/class_list_macros.h>

namespace original_plugin
{
mypanel4::mypanel4()
{
  color_property_ = new rviz::ColorProperty("Color", QColor(200, 50, 50), "Color to draw the acceleration arrows.",
                                            this, SLOT(updateColorAndAlpha()));//パネル上での値が変更されると、updateColorAndAlpha()が実行

  alpha_property_ = new rviz::FloatProperty("Alpha", 1.0, "0 is fully transparent, 1.0 is fully opaque.", this,
                                            SLOT(updateColorAndAlpha()));//パネル上での値が変更されると、updateColorAndAlpha()が実行
}

void mypanel4::onInitialize()
{
  frame_node_ = scene_node_->createChildSceneNode();
  vis_arrow_.reset(new rviz::Arrow(scene_manager_, frame_node_));
  float alpha = alpha_property_->getFloat();
  Ogre::ColourValue color = color_property_->getOgreColor();
  vis_arrow_->setColor(color.r, color.g, color.b, alpha);
  Ogre::Vector3 arrow_scale(0, 0, 0);
  vis_arrow_->setScale(arrow_scale);
  MFDClass::onInitialize();  // MFDClass := MessageFilterDisplay<message type>
}

mypanel4::~mypanel4()
{
}

void mypanel4::reset()
{
  MFDClass::reset();
}

void mypanel4::updateColorAndAlpha()
{
  float alpha = alpha_property_->getFloat();
  Ogre::ColourValue color = color_property_->getOgreColor();
  vis_arrow_->setColor(color.r, color.g, color.b, alpha);
}

void mypanel4::updateHistoryLength()
{
}

void mypanel4::processMessage(const geometry_msgs::PointStamped::ConstPtr& msg)//目的のROSトピックを受信すると呼ばれる関数
//トピックによるメッセージをmsgとしている？
{//３Dビューに表示されるものの記述↓
  Ogre::Quaternion orientation;
  Ogre::Vector3 position;
  if (!context_->getFrameManager()->getTransform(msg->header.frame_id, msg->header.stamp, position, orientation))//msgにあるheaderとrvizのFixedFrameが違っていた場合？
  //context_->getFrameManager()->getTransform(msg->header.frame_id, msg->header.stamp, position, orientation)により、Fixed Frame->msgへのheaderのtransformを取得し、描画？
  {
    ROS_DEBUG("Error transforming from frame '%s' to frame '%s'", msg->header.frame_id.c_str(),
              qPrintable(fixed_frame_));
    return;
  }
  frame_node_->setPosition(position);
  frame_node_->setOrientation(orientation);
  Ogre::Vector3 arrow_dir(msg->point.x, msg->point.y, msg->point.z);//クリックしたポイントの座標をベクトルに
  float arrow_length = arrow_dir.length() * 0.77;//ベクトルの長さに0.77かけている
  Ogre::Vector3 arrow_scale(arrow_length, arrow_length, arrow_length);
  vis_arrow_->setScale(arrow_scale);//大きさを設定
  vis_arrow_->setDirection(arrow_dir);//方向を設定
}

}  // namespace original_plugin

PLUGINLIB_EXPORT_CLASS(original_plugin::mypanel4, rviz::Display)