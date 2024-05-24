#include "solver_sde.h"

Solver_sde::Solver_sde() :
    f1(0), f2(0), r1(85), r2(85),
    v_x(5), v_y(0),
    u1(5), u2(5), m(0.5)
{
    J = 1; //m*(pow(r1,2)+pow(r2,2));
}

void Solver_sde::eulerMethod(double &x, double &y, double &angle, double t_step)
{
    double omega0 = 0;
    angle = (f1*r1-f2*r2)/J*pow(t_step,2) + omega0*t_step + angle;
    double xNew = x + v_x*t_step + t_step*t_step*(f1+f2)/m*cos((90-angle)*3.14/180);
    double yNew = y + v_y*t_step + t_step*t_step*(f1+f2)/m*sin((90-angle)*3.14/180);
    x = xNew;
    y = yNew;
}
