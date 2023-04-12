#ifndef Q_MOC_RUN
    #include <ros/ros.h>
    #include <rviz/panel.h>
#endif
#include <QPushButton>
#include <QSlider>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <std_srvs/SetBool.h>
#include <QLabel>
#include <QApplication>
#include <QDialog>
#include <QLineEdit>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QGridLayout>

#include <termios.h>
#include <unistd.h>
#include <unordered_map>
#include <std_msgs/Float32MultiArray.h>
class km_gui: public rviz::Panel {
Q_OBJECT //継承時に必要なマクロ
public:
    km_gui(QWidget* Parent=0); //作成するクラス

    //関数
private Q_SLOTS:
//   void keyPressEvent(QKeyEvent *event);
  void pushbutton();
  void pushbutton_b();
  void pushbutton_reset();
  void glipper_move(int i);

private:
 QPushButton* setButton1;
 QPushButton* setButton2;
 QPushButton* setButton3;

 QLineEdit* lineEdit;
QLabel* label1;
QLabel* label2;
QLabel* label3;
ros::NodeHandle n;
ros::Publisher pub=n.advertise<std_msgs::Float32MultiArray>("/km_gui",1);
ros::Publisher pub1=n.advertise<std_msgs::Float32MultiArray>("/km_reset",1);
std_msgs::Float32MultiArray array;

};