#ifndef _MOTOR_CONTROL
#define _MOTOR_CONTROL

void Forward(double del, int vel);
void setupMotors();
void Backward(double del, int vel);
void Right(double del, int vel);
void Left(double del, int vel);
void Stop(double del);
void Tleft();
void Tright();
void BreakR();
void BreakL();
void BreakF();

#endif // _MOTOR_CONTROL