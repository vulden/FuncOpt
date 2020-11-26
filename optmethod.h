#ifndef OPTMETHOD_H
#define OPTMETHOD_H
/*!
\file
\brief Заголовочный файл с описанием классов, относящихся к методам, с помощью которых будет искаться минимум.
*/

#include <random>
#include "funcOpt.h"
#include "area.h"
#include "stopCrit.h"
#pragma once
/*!
    \brief Родительский виртуальный класс методов.
    Метод позволяет находить аргумент минимума функции.
*/
class OptMethod {
public:
    /*!
    Ищет аргумент, на котором реализуется минимум функции на области.
    \param[in] x Функция для которой ищется минимум.
    \param[in] a Область, в которой ищется минимум.
    \param[in] stop Критерий остановки процесса поиска минимума.
    \param[in] start Точка, с которой начинается процесс поиска минимума.
    \param[in] iternum Число итераций.
    \param[in] y Некоторый параметр.
    \param[in] z Некоторый параметр.
    \return Вектор координат значения, на котором реализуется минимум.
    */
    virtual std::vector<double> optimize(func * x, area * a, StopCriteria* stop, std::vector<double> start, int iternum, double y, double z) =0;
    /*!
    Выводит в консоль название метода.
    */
    virtual void name_youself()=0;
};

/*!
    \brief Дочерний класс методов.
    Реализует поиск минимума вероятностным методом.
    Унаследован от ранее созданного класса OptMethod.
*/
class CoordDescent: public OptMethod {
public:
    /*!
    Ищет аргумент, на котором реализуется минимум функции на области.
    \param[in] x Функция для которой ищется минимум.
    \param[in] a Область, в которой ищется минимум.
    \param[in] stop Критерий остановки процесса поиска минимума.
    \param[in] start Точка, с которой начинается процесс поиска минимума.
    \param[in] iternum Число итераций.
    \param[in] len_of_seg Длина интервала, на который разбиваются исходные отрезки.
    \param[in] eps Точность, с которой ищется минимум.
    \return Вектор координат значения, на котором реализуется минимум.
    */
    std::vector<double> optimize(func *f, area *a, StopCriteria* stop, std::vector<double>, int iternum, double len_of_seg, double eps)override;
    /*!
    Выводит в консоль название метода.
    */
    void name_youself() override;
};

/*!
    \brief Дочерний класс методов.
    Реализует поиск минимума методом c спуска.
    Унаследован от ранее созданного класса OptMethod.
*/
class Stochastic:public OptMethod {
public:
    /*!
    Ищет аргумент, на котором реализуется минимум функции на области.
    \param[in] x Функция для которой ищется минимум.
    \param[in] a Область, в которой ищется минимум.
    \param[in] stop Критерий остановки процесса поиска минимума.
    \param[in] start Точка, с которой начинается процесс поиска минимума.
    \param[in] iternum Число итераций.
    \param[in] p Вероятность того, что поиск будет продолжен в окрестности предыдущей точки.
    \param[in] delta Размер окрестности.
    \return Вектор координат значения, на котором реализуется минимум.
    */
    std::vector<double> optimize(func *f, area *a, StopCriteria* stop, std::vector<double>, int iternum, double p,  double delta)override;
    /*!
    Выводит в консоль название метода.
    */
    void name_youself() override;
};


#endif // OPTMETHOD_H
