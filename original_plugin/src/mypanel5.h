#ifndef Q_MOC_RUN
    #include <ros/ros.h>
    #include <rviz/panel.h>
#endif
#include <QPushButton>
#include <QSlider>

class mypanel5: public rviz::Panel {
Q_OBJECT //継承時に必要なマクロ
public:
    mypanel5(QWidget* Parent = 0); //作成するクラス

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