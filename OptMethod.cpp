#include"optmethod.h"
#include <random>

template<typename T>
std::vector<T> VectSet(const std::vector<T> &a, T t, int index) {
    std::vector<T> x(a);
    x[index] = t;
    return x;
}

double ternary_search(func *f, const std::vector<double> &x, int k, double l, double r, double eps) {
    int i = 0;
    while (r - l > eps) {
        double l1 = (2 * l + r) / 3, r1 = (l + 2 * r) / 3;
        if (f->eval(VectSet(x, l1, k)) < f->eval(VectSet(x, r1, k)))
            r = r1;
        else l = l1;
        ++i;
    }
    return (l + r) / 2;
}

void CoordDescent::name_youself(){std::cout<<"COORDINATE DESCENT";}
void CoordDescent::set_eps(double t) {this->eps =t;}
void CoordDescent::set_len_of_seg(double t) {this->len_of_seg =t;}

std::vector<double> CoordDescent::optimize(func *f, area *a, StopCriteria* stop, std::vector<double> start, int iternum) {
    std::vector<std::vector<double>> path;
    std::vector<double> x(start);
    int niter=0;
    double fmin=INT32_MAX;
    for (int i = 0; i < iternum; ++i) {
        int coord = (i % (a->k));            //current coordinate
        int num_of_seg = (a->coord[coord].second - a->coord[coord].first) / this->len_of_seg;
        double prevf,ftemp,temp,argmin;
        prevf = fmin;                       // previous f(min)
        fmin =INT32_MAX;
        for (int j = 0; j < num_of_seg; ++j) {
           temp = ternary_search(f, x, coord, a->coord[coord].first + j * this->len_of_seg,
                                     a->coord[coord].first + (j + 1) * this->len_of_seg, this->eps);
            ftemp = f->eval(VectSet(x, temp, coord));   //x' = x: x[coord]= argmin; ftemp = f(x');
           if (ftemp < fmin) {
               fmin = ftemp;
               argmin =temp;
           }
        }
        x[coord] = argmin;
        ftemp = f->eval(x);
        path.push_back(x);
        if(abs(prevf-ftemp)<this->eps)
            ++niter;
        else
            niter = 0;
        if(i>0 && stop->condition(niter,abs(prevf-ftemp))) { //stop condition == true => leave
            stop->quit_message();
            return x;
        }
    }
    std::cout<<"Quit because of exceeding number of iterations.\n";
    return x;
}

void Stochastic::name_youself() {std::cout<<"STOCHASTIC: LOCAL SEARCH";}
void Stochastic::set_delta(double t) {this->delta =t;}
void Stochastic::set_p(double t) {this->p =t;}

std::vector<double> Stochastic::optimize(func *f, area *a, StopCriteria* stop, std::vector<double> start,int iternum) {

    std::random_device rd;      //random numner generator
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(0, 1);

    double a1,b1, fx,temp,df=1;
    int niter=0, n = a->k;   //number of coordinates
    fx=f->eval(start);
    std::vector<double> x, x0;
    x=x0=start;
    std::vector<std::vector<double>> path;

    for (int j = 0; j < iternum; ++j) {
        bool local = distrib(gen) >  this->p;
        for (int i = 0; i < n; ++i) {
            if (local){
                a1 = a->coord[i].first;
                b1 = a->coord[i].second;
            }
            else  {
                a1 = x[i]-this->delta<a->coord[i].first ? a->coord[i].first: x[i]-this->delta;
                b1 = x[i]+this->delta>a->coord[i].second ?a->coord[i].second: x[i]+this->delta;
            }
            x[i] = distrib(gen)*(b1-a1)+a1;
        }
        if ( (temp=f->eval(x)) < fx) {
            niter=0;
            x0 = x;
            df=fx-temp;
            fx = temp;
            path.push_back(x0);
        } else
            ++niter;
        if(j>0 && stop->condition(niter,df)) {   //stop condition == true => leave
            stop->quit_message();
            return x0;
        }
    }
    std::cout<<"Quit because of exceeding number of iterations.\n";
    return x0;
}
