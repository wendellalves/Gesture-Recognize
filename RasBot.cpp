#include "RasBot.h"

#ifndef CHECK_CODE_OUTSIDE_RASP
#include <wiringPi.h>
#include <softPwm.h>
#endif

#ifdef PRINT_DEBUG
#include <iostream>
#endif

RasBot::RasBot(){
    m_LF = M_LF_PORT;
    m_LB = M_LB_PORT;
    m_RF = M_RF_PORT;
    m_RB = M_RB_PORT;

    #ifndef CHECK_CODE_OUTSIDE_RASP
    if(wiringPiSetup() == -1){
        #ifdef PRINT_DEBUG
        std::cout << "Erro config GPIO" << std::endl;
        #endif
        exit(1);
    }

    softPwmCreate(m_LF, 0, 100);
    softPwmCreate(m_LB, 0, 100);
    softPwmCreate(m_RF, 0, 100);
    softPwmCreate(m_RB, 0, 100);
    #endif

    #ifdef PRINT_DEBUG
    std::cout << "Config GPIO ... Done" << std::endl;
    #endif
}
RasBot::RasBot(int _mLF_port, int _mLB_port, int _mRF_port, int _mRB_port){
    m_LF = _mLF_port;
    m_LB = _mLB_port;
    m_RF = _mRF_port;
    m_RB = _mRB_port;

    #ifndef CHECK_CODE_OUTSIDE_RASP
    if(wiringPiSetup() == -1){
        #ifdef PRINT_DEBUG
        std::cout << "Erro config GPIO" << std::endl;
        #endif
        exit(1);
    }

    softPwmCreate(m_LF, 0, 100);
    softPwmCreate(m_LB, 0, 100);
    softPwmCreate(m_RF, 0, 100);
    softPwmCreate(m_RB, 0, 100);
    #endif

    #ifdef PRINT_DEBUG
    std::cout << "Config GPIO ... Done" << std::endl;
    #endif
}
RasBot::~RasBot(){
    #ifndef CHECK_CODE_OUTSIDE_RASP
    softPwmWrite(m_LF,0);
    softPwmWrite(m_LB,0);
    softPwmWrite(m_RF,0);
    softPwmWrite(m_RB,0);
    delay(10);
    #endif
}

bool RasBot::setPorts(int _mLF_port, int _mLB_port, int _mRF_port, int _mRB_port){
    m_LF = _mLF_port;
    m_LB = _mLB_port;
    m_RF = _mRF_port;
    m_RB = _mRB_port;

    #ifndef CHECK_CODE_OUTSIDE_RASP
    if(wiringPiSetup() == -1){
        #ifdef PRINT_DEBUG
        std::cout << "Config GPIO ... Error" << std::endl;
        #endif
        return false;
    }

    softPwmCreate(m_LF, 0, 100);
    softPwmCreate(m_LB, 0, 100);
    softPwmCreate(m_RF, 0, 100);
    softPwmCreate(m_RB, 0, 100);
    #endif

    #ifdef PRINT_DEBUG
    std::cout << "Config GPIO ... Done" << std::endl;
    #endif

    return true;
}

void RasBot::stop(){
    #ifndef CHECK_CODE_OUTSIDE_RASP
    softPwmWrite(m_LF,0);
    softPwmWrite(m_LB,0);
    softPwmWrite(m_RF,0);
    softPwmWrite(m_RB,0);
    delay(10);
    #endif
}
void RasBot::moveF(int relative_velocity){
    #ifdef PRINT_DEBUG
    std::cout << "Forward  -> ";
    #endif

    motorL(1, relative_velocity);
    motorR(1, relative_velocity);

    #ifdef PRINT_DEBUG
    std::cout << std::endl;
    #endif
}
void RasBot::moveB(int relative_velocity){
    #ifdef PRINT_DEBUG
    std::cout << "Backward -> ";
    #endif

    motorL(0, relative_velocity);
    motorR(0, relative_velocity);

    #ifdef PRINT_DEBUG
    std::cout << std::endl;
    #endif
}
void RasBot::turnL(int relative_velocity){
    #ifdef PRINT_DEBUG
    std::cout << "Left     -> ";
    #endif

    motorL(0, relative_velocity);
    motorR(1, relative_velocity);
    
    #ifdef PRINT_DEBUG
    std::cout << std::endl;
    #endif
}
void RasBot::turnR(int relative_velocity){
    #ifdef PRINT_DEBUG
    std::cout << "Right    -> ";
    #endif

    motorL(1, relative_velocity);
    motorR(0, relative_velocity);
    
    #ifdef PRINT_DEBUG
    std::cout << std::endl;
    #endif
}
void RasBot::motorL(int direction, int relative_velocity){
    if(direction){
        #ifndef CHECK_CODE_OUTSIDE_RASP
        softPwmWrite(m_LB,0);
        softPwmWrite(m_LF, relative_velocity);
        #endif
        #ifdef PRINT_DEBUG
        std::cout << " \t L:  " << relative_velocity;
        #endif
    }else{
        #ifndef CHECK_CODE_OUTSIDE_RASP
        softPwmWrite(m_LF,0);
        softPwmWrite(m_LB, relative_velocity);
        #endif
        #ifdef PRINT_DEBUG
        std::cout << " \t L: -" << relative_velocity;
        #endif
    }
}
void RasBot::motorR(int direction, int relative_velocity){
    if(direction){
        #ifndef CHECK_CODE_OUTSIDE_RASP
        softPwmWrite(m_RB,0);
        softPwmWrite(m_RF, relative_velocity);
        #endif
        #ifdef PRINT_DEBUG
        std::cout << " \t R:  " << relative_velocity;
        #endif
    }else{
        #ifndef CHECK_CODE_OUTSIDE_RASP
        softPwmWrite(m_RF,0);
        softPwmWrite(m_RB, relative_velocity);
        #endif
        #ifdef PRINT_DEBUG
        std::cout << " \t R: -" << relative_velocity;
        #endif
    }
}