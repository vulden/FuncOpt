#ifndef FUNCOPT_H
#define FUNCOPT_H
/*!
\file
\brief Заголовочный файл с описанием классов, относящихся к функциям, для которых будет искаться минимум.
*/

#include <vector>
#include <iostream>
#include <cmath>
#pragma once


/*******************************************************************************
 *
 * \author Владимир Попов <popov99vlad@gmail.com>
 *	\version 1.0
 *	\date Ноябрь 2020 года
 *
 * \section Описание:
 *
 * Программа позволяет вычислять минимум функции в области.
 * Функция, область, метод оптимизации и критерий остановки могут быть заданы пользователем.
 *
 *******************************************************************************/

const double pi = 3.1415926;

/*!
    \brief Родительский виртуальный класс функций.
*/
class func {
public:
    /*!
    Вычисляет значение функции в точке.
    \param[in] x Вектор, содержащий координаты точки.
    */
    virtual double eval(const std::vector<double>& x) = 0;
    /*!
    Выводит в консоль вид функции.
    */
    virtual void print()=0;
    /*!
    Выводит в консоль точку, в которой достигается минимум.
    */
    virtual void expectedArgMin ()=0;
    /*!
    \return Число координат у вектора, который принимает на вход функция.
    */
    virtual int dimentions ()=0;
};
/*!
    \brief Дочерний класс функций.
    Тривиальная функция от двух аргументов.
    Унаследован от ранее созданного класса func.
*/
class func_1 : public func {
public:
    double eval(const std::vector<double>& x) override;
    void print() override;
    void expectedArgMin() override;
    int dimentions ()override;
};
/*!
    \brief Дочерний класс функций.
    Функция Розенброка.
    Унаследован от ранее созданного класса func.
*/
class func_2 : public func {
public:
    double eval(const  std::vector<double>& x) override ;
    void print() override ;
    void expectedArgMin() override;
    int dimentions ()override;
};
/*!
    \brief Дочерний класс функций.
    Функция Бута.
    Унаследован от ранее созданного класса func.
*/
class func_3 : public func {
public:
    double eval(const  std::vector<double>& x) override ;
    void print() override ;
    void expectedArgMin() override;
    int dimentions ()override;
};
/*!
    \brief Дочерний класс функций.
    Функция Изома.
    Унаследован от ранее созданного класса func.
*/
class func_4 : public func {
public:
    double eval(const  std::vector<double>& x) override;
    void print() override ;
    void expectedArgMin() override;
    int dimentions ()override;
};
/*!
    \brief Дочерний класс функций.
    Тривиальная функция трёх аргументов.
    Унаследован от ранее созданного класса func.
*/
class func_5 : public func {
public:
    double eval(const  std::vector<double>& x) override ;
    void print() override ;
    void expectedArgMin() override;
    int dimentions ()override;
};
#endif // FUNCOPT_H
