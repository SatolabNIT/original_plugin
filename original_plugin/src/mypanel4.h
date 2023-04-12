//ros_lecture/original_plugin/src/rviz/display/point_display.h
//ros講座111
#ifndef POINT_DISPLAY_H
#define POINT_DISPLAY_H

#ifndef Q_MOC_RUN
#include <boost/circular_buffer.hpp>
#include <rviz/message_filter_display.h>
#include <rviz/ogre_helpers/arrow.h>
#include <geometry_msgs/PointStamped.h>
#endif

namespace Ogre
{
class SceneNode;
}

namespace rviz
{
class ColorProperty;
class FloatProperty;
class IntProperty;
}  // namespace rviz

namespace original_plugin

{
class mypanel4 : public rviz::MessageFilterDisplay<geometry_msgs::PointStamped>//:publicの書き方は、継承を表している
//rviz::MessageFilterDisplay<geometry_msgs::PointStamped １つのトピックをsubscribeして何かを表示するだけに使えるクラス、
{
  Q_OBJECT
public:
  mypanel4();
  virtual ~mypanel4();

  virtual void onInitialize();
  virtual void reset();

private Q_SLOTS:
  void updateColorAndAlpha();
  void updateHistoryLength();

private:
  void processMessage(const geometry_msgs::PointStamped::ConstPtr& msg);
  Ogre::SceneNode* frame_node_;//ノード作成？
  boost::shared_ptr<rviz::Arrow> vis_arrow_;
  rviz::ColorProperty* color_property_;
  rviz::FloatProperty* alpha_property_;
};

}  // namespace original_plugin

#endif  // POINT_DISPLAY_H