#include "solver_sde.h"

Solver_sde::Solver_sde() :
    f1(0), f2(0), r1(85), r2(85),
    u1(5), u2(5), m(0.5)
{
    J = 1; //m*(pow(r1,2)+pow(r2,2));
}

void Solver_sde::eulerMethod(double &x, double &y, double &angle, double step)
{
    double v0 = 0, omega0 = 0;
    angle = (f1*r1-f2*r2)/J*pow(step,2) + omega0*step + angle;
    double xNew = x + v0*step + step*step*cos((90-angle)*3.14/180);
    double yNew = y + v0*step + step*step*sin((90-angle)*3.14/180);
    x = xNew;
    y = yNew;
}
