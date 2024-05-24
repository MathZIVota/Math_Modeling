#ifndef SOLVER_SDE_H
#define SOLVER_SDE_H

#include <QMainWindow>
#include <cmath>

class Solver_sde
{
public:
    Solver_sde();
    void eulerMethod(double &x, double &y, double &angle, double step);

    double f1,f2;
    double r1,r2;
    double u1, u2;
    double m, J;

};

#endif // SOLVER_SDE_H
