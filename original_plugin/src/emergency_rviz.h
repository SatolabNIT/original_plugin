#ifndef Q_MOC_RUN
    #include <ros/ros.h>
    #include <rviz/panel.h>
#endif
#include <QPushButton>
#include <QSlider>

class emergency_rviz: public rviz::Panel {
Q_OBJECT //継承時に必要なマクロ
public:
    emergency_rviz(QWidget* Parent = 0); //作成するクラス

    //関数
private Q_SLOTS:
    void stop_push();
    void start_push();
    void slider_move(int);

private:
    QPushButton* start_button;
    QPushButton* stop_button;
    QSlider* slider;
    ros::NodeHandle node;
};