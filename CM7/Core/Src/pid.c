#include "pid.h"

void PID_init(PID* pid, double kp, double ki, double kd, double iMax, double outMin, double outMax) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->iMax = iMax;
    pid->outMin = outMin;
    pid->outMax = outMax;
}

/*
typedef struct
{
    // all starts as 0
    float kp;
    float ki;
    float kd;
    float iMax;
    float error_sum;
    float error_last;
    float outMin;
    float outMax;
} PID;
*/

float PID_calc(PID *pid, float target, float current) {
    float error = target - current;
    float pTerm = pid->kp * error;
    pid->error_sum += error;
    float iTerm = pid->ki * pid->error_sum;
    float dTerm = pid->kd * (error - pid->error_last);
    pid->error_last = error;
    float output = pTerm + iTerm + dTerm;
    if (output > pid->outMax) {
        output = pid->outMax;
    } else if (output < pid->outMin) {
        output = pid->outMin;
    }
    return output;
}