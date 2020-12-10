#include <iostream>
#include <utility>
#include <random>
#include "funcOpt.h"
#include "area.h"
#include "stopCrit.h"
#include"optmethod.h"

template <typename T>
T getValueInBounders(T left,T right)
{
    while (true)
    {
        std::cout << "Enter a value between "<<left<<" and "<<right<<" :";
        T a;
        std::cin >> a;
        if (std::cin.fail()||(!std::cin.fail() && (a<left||a>right)))
        {
            std::cin.clear();
            std::cin.ignore(2048,'\n');
            std::cout << "Input is invalid.  Please try again.\n";
        }
        else
        {
            std::cin.ignore(2048,'\n');
            return a;
        }
    }
}



int main() {
    while(true){
        int num_of_dimentions;
        std::cout<<"Choose function from list:\n"
                   "1. Trivial 2arg function, (1-x)^2+3y^2\n"
                   "2. Rosenbrock function, (1-x)^2+100(y-x^2)^2\n"
                   "3. Boot function, (x+2y-7)^2+(2x+y-5)^2\n"
                   "4. Easom function, -cos(x)*cos(y)*exp(-((x-pi)^2+(y-pi)^2))\n"
                   "5. Trivial 3arg function, (1-x)^2+ (2-y)^2+ (4-z)^2\n";
        int functype,methodtype,num_of_iter;
        func * f;
        functype=getValueInBounders(1,5);
        switch (functype) {
        case 1:{
            f = new func_1();
            break;
        }
        case 2:{
            f = new func_2();
            break;
        }
        case 3:{
            f = new func_3();
            break;
        }
        case 4:{
            f = new func_4();
            break;
        }
        case 5:{
            f = new func_5();
            break;
        }
        }
        num_of_dimentions = f->dimentions();
        std::vector<double> result(num_of_dimentions);

        std::cout<<"Choose method from list:\n"
                   "1. Local search (stochastic).\n"
                   "2. Coordinate descent.\n";
        methodtype=getValueInBounders(1,2);
        double z;
        OptMethod* method;
        switch (methodtype) {
        case 1:{
            method = new Stochastic;
            std:: cout<<"Enter p:\n";
            z = getValueInBounders(0.0,1.0);
            method->set_p(z);
            std:: cout<<"Enter delta:\n";
            z = getValueInBounders(0.0,1.0);
            method->set_delta(z);
            break;
        }
        case 2:{
            method = new CoordDescent;
            std::cout<<"Enter length of segment:\n";
            z = getValueInBounders(0.0,100000.0);
            method->set_len_of_seg(z);
            std::cout<<"Enter epsilon:\n";
            z = getValueInBounders(0.0,1.0);
            method ->set_eps(z);
            break;
        }
        }

        std::cout<<"Choose stop criteria from list.\n"
                   "1. Number of iterations.\n"
                   "2. Number of iterations since last improvement.\n"
                   "3. Too low change of value.\n";
        methodtype=getValueInBounders(1,3);

        StopCriteria* stop;
        switch (methodtype) {
        case 1:{
            stop = new StopNULL();
            break;
        }
        case 2:{
            std::cout<<"Enter the number of iterations to quit since last improvement:\n";
            int temp;
            temp = getValueInBounders(0,1000000);
            stop = new StopNumLI(temp,0);
            break;
        }
        case 3:{
            std::cout<<"Enter the minimal acceptable change of value:\n";
            double temp;
            temp = getValueInBounders(0.0,1000000.0);
            stop = new StopValLI(0,temp);
            break;
        }
        }
        std::cout<<"Enter number of iteration:\n";
        num_of_iter=getValueInBounders(1,1000000000);

        std::cout<<"Choose area type from list.\n"
                   "1. Easy area - each coordinate varies from -10 to 10 .\n"
                   "2. Hard area - each coordinate should be given.\n";
        methodtype=getValueInBounders(1,2);
        area * my_area;
        switch (methodtype) {
        case 1:{
            my_area = new area_easy(num_of_dimentions);
            break;
        }
        case 2:{
            std::vector<std::pair<double, double>> coord;
            for(int i=0; i<num_of_dimentions;++i)
            {

                std::cout<<"Enter bounders x,y: x<y, "<<num_of_dimentions-i<<" pairs left\n";
                double x,y;
                x=getValueInBounders(-1000.0,1000.0);
                y=getValueInBounders(x,1000.0);
                coord.push_back(std::make_pair(x,y));
            }
            my_area = new area_hard(coord);
            break;
        }
        }

        std::cout<<"Choose starting point (each coordinate should be in corresponding bounders) :\n";
        for (int i = 0; i < num_of_dimentions; ++i){
            std::cout<<"Enter "<<i+1<<"st coordinate \n";
            result[i]=getValueInBounders(my_area->coord[i].first,my_area->coord[i].second);
        }

        result = method->optimize(f, my_area, stop, result, num_of_iter);
        std::cout<<"Result is: (";
        for (int i = 0; i < num_of_dimentions; ++i)
            std::cout << result[i] << " , ";
        std::cout<<")";
        f->expectedArgMin();
        std::cout<<"\nDo you want to continue? [Y/n]";
        char t;
        std::cin>>t;
        if(t!='Y') break;

    }
    return 0;
}
