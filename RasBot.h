#ifndef RASBOT_H
#define RASBOT_H

#include <iostream>

// Coment this line to work on RPi, only difine this if you are coding on another device:
// #define CHECK_CODE_OUTSIDE_RASP 

// Coment this line with don't want debug mensages:
#define PRINT_DEBUG 

//Default pins
#define M_LF_PORT 0
#define M_LB_PORT 1
#define M_RF_PORT 2
#define M_RB_PORT 3

class RasBot{
public:
	RasBot();
    RasBot(int _mLF_port, int _mLB_port, int _mRF_port, int _mRB_port);
    ~RasBot();

    bool setPorts(int _mLF_port, int _mLB_port, int _mRF_port, int _mRB_port);
    void stop();

    void moveF(int relative_velocity); 
    void moveB(int relative_velocity);
    void turnL(int relative_velocity);
    void turnR(int relative_velocity);

    void motorL(int direction, int relative_velocity);
    void motorR(int direction, int relative_velocity);

private:
    int m_LF, m_LB, en_L;
    int m_RF, m_RB, en_R;
};

#endif