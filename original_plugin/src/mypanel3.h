//original_plugin/src/rviz/tool/point_tool.h
//ros講座102
#ifndef SET_MARKER_H
#define SET_MARKER_H

#include <ros/ros.h>
#include <rviz/tool.h>
#include <rviz/ogre_helpers/shape.h>

namespace Ogre//ogreという描画エンジン、Rvizの3D表示に使うもの
{
class SceneNode;
class Vector3;
}  // namespace Ogre

namespace rviz
{
class VectorProperty;
class VisualizationManager;
class ViewportMouseEvent;
}  // namespace rviz

namespace original_plugin//namespace
{
class mypanel3 : public rviz::Tool//クラスの作成
{
  Q_OBJECT
public:
  mypanel3();
  ~mypanel3();

  virtual void onInitialize();
  virtual void activate();
  virtual void deactivate();
  virtual int processMouseEvent(rviz::ViewportMouseEvent& event);

  ros::NodeHandle nh_;
  ros::Publisher point_pub_;
  boost::shared_ptr<rviz::Shape> vis_shape_;//Rvizの3Dビューの中で円柱を表示するためのクラス
};

}  // namespace original_plugin

#endif  // SET_MARKER_H