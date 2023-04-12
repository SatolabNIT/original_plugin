#ifndef Q_MOC_RUN
    #include <ros/ros.h>
    #include <rviz/panel.h>
#endif

class testpanel: public rviz::Panel {
Q_OBJECT //継承時に必要なマクロ
public:
    testpanel(QWidget* Parent = 0); //コンストラクタ
};