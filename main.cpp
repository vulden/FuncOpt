#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <random>

using namespace std;
random_device rd;  //Will be used to obtain a seed for the random number engine
mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

class func {
public:
    virtual double eval(const vector<double> x) = 0;
};

class func_1 : public func {
public:
    double eval(const vector<double> x) override {
        return pow((1 - x[0]), 2) + 3 * x[1]*x[1];
    }
};

class func_2 : public func {
public:
    double eval(const vector<double> x) override {
        return pow((1 - x[0]), 2) + 100*pow((x[1]-x[0]*x[0]),2);
    }
};

class area {
public:
    int k;
    vector<pair<double, double>> coord;

    area(int a) : k(a), coord(a) {};

    area(int a, vector<pair<double, double>> s) : k(a), coord(std::move(s)) {};
public:

};

class area_1 {
public:

};

template<typename T>
vector<T> operator+(const vector<T> &a, const vector<T> &b) {
    vector<T> x(a);
    for (int i = 0; i < a.size(); ++i) {
        x[i] += b[i];
    }
    return x;
}

template<typename T>
vector<T> VectSet(const vector<T> &a, T t, int index) {
    vector<T> x(a);
    x[index] = t;
    return x;
}

int minv(const vector<double> &v, const vector<double> &x, int n, func *f, int index) {
    double tmp = INT32_MAX;
    int ind = 0;
    for (int i = 0; i < n; ++i) {
        double temp = f->eval(VectSet(x, v[i], index));
        if (temp < tmp) {
            tmp = temp;
            ind = i;
        }
    }
    return ind;
}

double ternary_search(func *f, const vector<double> &x, int k, double l, double r, double eps) {
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

class OptMethod {
public:
        virtual vector<double> optimize(func *, area *, int, double , double) =0;
    };
class CoordDescent: public OptMethod {
public:
    vector<double> optimize(func *f, area *a,  int iternum, double len_of_seg, double eps)override {

        vector<double> x(a->k, 0);
        vector<double> x1(x);
        for (int i = 0; i < iternum; ++i) {
            x = x1;
            int n = (i % (a->k));
            int num_of_seg = (a->coord[n].second - a->coord[n].first) / len_of_seg;
            vector<double> mins(num_of_seg + 1);
            for (int j = 0; j < num_of_seg; ++j) {
                mins[j] = ternary_search(f, x1, n, a->coord[n].first + j * len_of_seg,
                                         a->coord[n].first + (j + 1) * len_of_seg, eps);
            }
            mins[num_of_seg] = ternary_search(f, x1, n, a->coord[n].first + (num_of_seg - 1) * len_of_seg,
                                              a->coord[n].second, eps);
            int ind_of_min = minv(mins, x1, num_of_seg + 1, f, n);
            x1[n] = ternary_search(f, x1, n, a->coord[n].first + ind_of_min * len_of_seg,
                                   a->coord[n].first + (ind_of_min + 1) * len_of_seg, eps);
        }
        return x1;
    }
};

class Stochastic:public OptMethod {
public:
    vector<double> optimize(func *f, area *a,int iternum, double p,  double delta)override {
        int n = a->k;
        vector<double> x(n, 0);
        vector<double> x0(n, INT32_MAX);
        uniform_real_distribution<> distrib(0, 1);
        if (distrib(gen) >  p) {
            for (int j = 0; j < iternum; ++j) {
                for (int i = 0; i < n; ++i) {
                    uniform_real_distribution<> distrib(a->coord[i].first, a->coord[i].second);
                    x[i] = distrib(gen);
                }
                if (f->eval(x) <= f->eval(x0)) x0 = x;
            }
        } else {
            for (int j = 0; j < iternum; ++j) {
                for (int i = 0; i < n; ++i) {
                    uniform_real_distribution<> distrib(x[i]-delta<a->coord[i].first ? a->coord[i].first: x[i]-delta, x[i]+delta>a->coord[i].second ?a->coord[i].second:x[i]+delta);
                    x[i] = distrib(gen);
                }
                if (f->eval(x) <= f->eval(x0)) x0 = x;
            }

        }
        return x0;
    }
};

class StopCriteria {
};

int main() {

    func *f = new func_1();
    vector<double> result(3, 0);
    OptMethod *m = new CoordDescent();
    vector<pair<double, double>> l;
    l.push_back(make_pair(-10, 10));
    l.push_back(make_pair(-10, 10));
    area *a = new area(2, l);
    cout<<"COORDINATE DESCENT\n";
    cout<<"Enter number of iteration\n"; //надо бы сделать, чтобы вычислялось по эпсилон
    double x2,x3;
    int x1; cin>>x1;
    cout<<"Enter length of segment\n";
    cin>>x2;
    cout<<"Enter epsilon\n";
    cin>>x3;
    cout<<"Coordinate descent for function (1-x)^2 + 3y^2, arg min :";
    result = m->optimize(f, a, x1, x2, x3);
    for (int i = 0; i < 2; ++i) {
        cout << result[i] << " ";
    }
    cout<<"\n";
    OptMethod* m1 = new Stochastic;
    func *f1 = new func_2();
    cout<<"STOCHASTIC: LOCAL SEARCH\n";
    cout<<"Enter number of iteration\n"; //надо бы сделать, чтобы вычислялось по эпсилон
    cin>>x1;
    cout<<"Enter p \n";
    cin>>x2;
    cout<<"Enter delta\n";
    cin>>x3;
    cout<<"Coordinate descent for function (1-x)^2 + 100(x-y^2)^2, arg min :";
    result = m1->optimize(f1, a, x1,x2,x3);
    for (int i = 0; i < 2; ++i) {
        cout << result[i] << " ";
    }
    return 0;
}
