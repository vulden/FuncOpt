#include"stopCrit.h"
#include<iostream>
bool StopNumLI::condition(int n, double value) {
    return n>itern;
}

bool StopValLI::condition(int n, double value)  {
    return value<eps;
}

bool StopNULL::condition(int n, double value) {
    return false;
}

void StopNumLI::quit_message() {std::cout<<"Quit because of exceeding number of iterations since last improvement.\n";} ;
void StopNULL::quit_message() {std::cout<<"Quit because of exceeding number of iterations.\n";} ;
void StopValLI::quit_message() {std::cout<<"Quit because of too low change of value.\n";} ;
