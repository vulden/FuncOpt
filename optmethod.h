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
    \return Вектор координат значения, на котором реализуется минимум.
    */
    virtual std::vector<double> optimize(func * x, area * a, StopCriteria* stop, std::vector<double> start, int iternum) =0;
    virtual void set_eps(double){}
    virtual void set_p(double){}
    virtual void set_delta(double){}
    virtual void set_len_of_seg(double){}
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
    //! Вещественная переменная.
    /*! Xранит длину отрезка. */
    double len_of_seg;
    //! Вещественная переменная.
    /*! Xранит желаемую точность вычислений. */
    double eps;
    /*!
    Устанавливает точность.
    \param[in] x Точность.
    */
    void set_eps(double t)override;
    /*!
    Устанавливает длину отрезка.
    \param[in] x Длина отрезка.
    */
    void set_len_of_seg(double t)override;
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
    std::vector<double> optimize(func *f, area *a, StopCriteria* stop, std::vector<double>, int iternum)override;
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
    //! Вещественная переменная.
    /*! Xранит вероятность выбора окрестности в качестве области.*/
    double p;
    //! Вещественная переменная.
    /*! Xранит размер окрестности. */
    double delta;
    /*!
    Устанавливает вероятность выбора окрестности в качестве области.
    \param[in] x Вероятность.
    */
    void set_p(double t)override;
    /*!
    Устанавливает размер окрестности.
    \param[in] x Размер окрестности.
    */
    void set_delta(double t)override;
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
    std::vector<double> optimize(func *f, area *a, StopCriteria* stop, std::vector<double>, int iternum)override;
    /*!
    Выводит в консоль название метода.
    */
    void name_youself() override;
};


#endif // OPTMETHOD_H
