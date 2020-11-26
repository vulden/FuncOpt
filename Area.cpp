#include"area.h"
#include<iostream>

area::area(int a):k(a),coord(a){};

area_easy::area_easy(int a):area(a){
    for(int i=0; i<a;++i)
        coord[i]=std::make_pair(-10.0,10.0);
}

area_hard::area_hard(const std::vector<std::pair<double, double>> & v):area(v.size()){
        coord=v;
}
