#include "funcOpt.h"
double func_1::eval(const std::vector<double> &x)  {
    return pow((1 - x[0]), 2) + 3 * x[1]*x[1];
}
void func_1::print()  {
    std::cout<<"Trivial 2arg function, (1-x)^2+3y^2";
    return;
}
void func_1::expectedArgMin() {
    std::cout<<"expected Argument of minimum is (1,0)";
    return;
}

int func_1::dimentions() {return 2;}

double func_2::eval(const  std::vector<double>& x)  {
    return pow((1 - x[0]), 2) + 100*pow((x[1]-x[0]*x[0]),2);
}
void func_2::print()  {
    std::cout<<" Rosenbrock function, (1-x)^2+100(y-x^2)^2";
    return;
}
void func_2::expectedArgMin() {
    std::cout<<"expected Argument of minimum is (1,1)";
    return;
}
int func_2::dimentions() {return 2;}


double func_3::eval(const  std::vector<double>& x)  {
    return pow(x[0]+2*x[1]-7,2)+ pow(2*x[0]+x[1]-5,2);
}
void func_3::print()  {
    std::cout<<" Boot function, (x+2y-7)^2+(2x+y-5)^2";
    return;
}
void func_3::expectedArgMin() {
    std::cout<<"expected Argument of minimum is (1,3)";
    return;
}
int func_3::dimentions() {return 2;}


double func_4::eval(const  std::vector<double>& x)  {
    return -cos(x[0])*cos(x[1])*exp(-(pow(x[0]-pi,2)+pow(x[1]-pi,2)));
}
void func_4::print()  {
    std::cout<<" Easom function, -cos(x)*cos(y)*exp(-((x-pi)^2+(y-pi)^2))";
    return;
}
void func_4::expectedArgMin() {
    std::cout<<"expected Argument of minimum is ("<<pi<<","<<pi<<")";
    return;
}
int func_4::dimentions() {return 2;}


double func_5::eval(const  std::vector<double>& x)  {
    return pow((1 - x[0]), 2) +  pow((2 - x[1]), 2)+  pow((4 - x[2]), 2);
}
void func_5::print()  {
    std::cout<<"Trivial 3arg function, (1-x)^2+ (2-y)^2+ (4-z)^2";
    return;
}
void func_5::expectedArgMin() {
    std::cout<<"expected Argument of minimum is (1,2,4)";
    return;
}
int func_5::dimentions() {return 3;}
