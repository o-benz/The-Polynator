#ifndef DRIVE_PATH
#define DRIVE_PATH

#define SPEED_WHEELS_LEFT 140 //140
#define SPEED_WHEELS_RIGHT 125
#define ROTATE_SPEED_LEFT 80 //80
#define ROTATE_SPEED_RIGHT 75
#define DELAY_ERROR 30
#define DELAY_180 2000
#define ROTATION_AXE 1000
#define PULSE 30
#define ROTATE_MARGE 200
#define WAIT 500
#define DELAY_ERROR_2 190
#define DELAY_ROTATE 100
#define PUSH_ROTATE_180 200


#define DELAY_TIMER 14000 // 14000


#include "exec.h"

uint8_t sensorPath = 0;

bool gExpiredTimer = false;

void driveLine()
{
    bool isDriveLine = true;

    robotExec.driveRatio(255,255);
    gExpiredTimer = false;
    robotExec.startTimer(DELAY_TIMER);
    _delay_ms(PULSE);
    while(isDriveLine && !gExpiredTimer)
    {
        sensorPath = robotExec.readSensor();
        switch (sensorPath)
        {
        case 0x04:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT);
            break;

        case 0x06:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT-30);
            break;
        
        case 0x03:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT-30);
            break;
        
        case 0x01:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT-30);
            break;

        case 0x02:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT-30);
            break;

        case 0x0C:
            robotExec.driveRatio(SPEED_WHEELS_LEFT-30,SPEED_WHEELS_RIGHT);
            break;
        
        case 0x18:
            robotExec.driveRatio(SPEED_WHEELS_LEFT-30,SPEED_WHEELS_RIGHT);
            break;
        
        case 0x10:
            robotExec.driveRatio(SPEED_WHEELS_LEFT-30,SPEED_WHEELS_RIGHT);
            break;

        case 0x08:
            robotExec.driveRatio(SPEED_WHEELS_LEFT-30,SPEED_WHEELS_RIGHT);
            break;

        case 0x0F:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x0F)
            {
                break;
            }
            _delay_ms(DELAY_ERROR_2);
            isDriveLine = false;
            break;

        case 0x07:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x07)
            {
                break;
            }
            _delay_ms(DELAY_ERROR_2);
            isDriveLine = false;
            break;
        
        case 0x1C:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x1C)
            {
                break;
            }
            _delay_ms(DELAY_ERROR_2);
            isDriveLine = false;
            break;
        
        case 0x1E:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT);
            _delay_ms(DELAY_ERROR);
            if (robotExec.readSensor() != 0x1E)
            {
                break;
            }
            _delay_ms(DELAY_ERROR_2);
            isDriveLine = false;
            break;
        
        case 0x1F:
            robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT);
            _delay_ms(DELAY_ERROR_2);
            isDriveLine = false;
            break;
        
        case 0x00:
            _delay_ms(DELAY_ERROR);
            if(robotExec.readSensor() == 0x00)
            {
                isDriveLine = false;
                break;
            }

        default:
            break;
        }
    }
    robotExec.stopTimer();
    robotExec.driveRatio(SPEED_WHEELS_LEFT,SPEED_WHEELS_RIGHT);
    _delay_ms(ROTATION_AXE);
    robotExec.driveRatio(0,0);
    _delay_ms(WAIT);
    return;
}

void turnRight()
{
    robotExec.driveRatio(255,255,true,false);
    _delay_ms(ROTATE_MARGE);
    robotExec.driveRatio(ROTATE_SPEED_LEFT,ROTATE_SPEED_RIGHT,true,false);
    while(!(sensorPath &= 0x04))
    {
        sensorPath = robotExec.readSensor();
        _delay_ms(DELAY_ROTATE);        // Maybe remove
    }
    robotExec.driveRatio(0,0);
    _delay_ms(WAIT);
    while(!(sensorPath == 0x04))
    {
        robotExec.driveRatio(ROTATE_SPEED_LEFT,ROTATE_SPEED_RIGHT,false,true);
        _delay_ms(DELAY_ERROR); // Délai à ajuster pour être parfaitement aligné
    }
    return;
}

void turnLeft()
{
    robotExec.driveRatio(255,255,false,true);
    _delay_ms(ROTATE_MARGE);
    robotExec.driveRatio(ROTATE_SPEED_LEFT,ROTATE_SPEED_RIGHT,false,true);
    while(!(sensorPath &= 0x04))
    {

        sensorPath = robotExec.readSensor();
        _delay_ms(DELAY_ROTATE) ;        // Maybe remove
    }
    robotExec.driveRatio(0,0);
    _delay_ms(WAIT);
    while(!(sensorPath == 0x04))
    {
        robotExec.driveRatio(ROTATE_SPEED_LEFT,ROTATE_SPEED_RIGHT,true,false);
        _delay_ms(DELAY_ERROR); // Délai à ajuster pour être parfaitement aligné
    }
    return;
}

void turn180()
{
    robotExec.driveRatio(255,255,false,true);
    _delay_ms(PUSH_ROTATE_180);
    robotExec.driveRatio(ROTATE_SPEED_LEFT,ROTATE_SPEED_RIGHT,false,true);
    _delay_ms(DELAY_180);
    sensorPath = robotExec.readSensor();
    while(!(sensorPath &= 0x04))
    {  
        sensorPath = robotExec.readSensor();
    }
    robotExec.driveRatio(0,0);
    _delay_ms(WAIT);
    while(!(sensorPath == 0x04))
    {
        robotExec.driveRatio(ROTATE_SPEED_LEFT,ROTATE_SPEED_RIGHT,true,false);
        _delay_ms(DELAY_ERROR); // Délai à ajuster pour être parfaitement aligné
    }
    return;
}

#endif