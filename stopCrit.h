#ifndef STOPCRIT_H
#define STOPCRIT_H
/*!
\file
\brief Заголовочный файл с описанием классов, относящихся к критериям остановки процесса поиска минимума.
*/

#pragma once
#include<vector>

/*!
    \brief Родительский виртуальный класс критерия остановки.
*/
class StopCriteria {
public:
    /*!
    Проверяет условие выхода из процесс поиска минимума.
    \return  True, если условие выполнено, false иначе.
    */
    virtual bool condition(int, double)=0;
    /*!
    Выводит в консоль сообщение о выходе.
    */
    virtual void quit_message()=0;
    //! Конструктор.
    /*! Конструктор по умолчанию.
     */
    StopCriteria(){};
    /*! Конструктор.
     * \param[in] x Предельное число итераций без улучшения.
     * \param[in] y Минимально допустимая разница значений.
    */
    StopCriteria(int x,double y):itern(x),eps(y){};
    //! Целочисленная переменная.
    /*! Хранит предельное число итераций без улучшения.*/
    int itern=100;
    //! Вещественная переменная.
    /*! Хранит минимально допустимая разница значений.*/
    double eps=0.001;
};
/*!
    \brief Дочерний класс критерия остановки.
    Останавливает процесс поиска минимума при достижении порового числа итераций с момента последнего улучшения.
    Унаследован от ранее созданного класса StopCriteria.
*/
class StopNumLI: public StopCriteria{       //stop criteria: number of iterations since last improvement
public:
   bool condition(int, double) override;
   void quit_message() override;
   StopNumLI(){};
   StopNumLI(int x,double y):StopCriteria(x,y){};
};
/*!
    \brief Дочерний класс методов.
    Останавливает процесс поиска минимума при слишком малом улучшении.
    Унаследован от ранее созданного класса StopCriteria.
*/
class StopValLI: public StopCriteria{        //stop criteria: value of last improvement
public:
   bool condition(int, double) override;
   void quit_message() override;

   StopValLI(){};
   StopValLI(int x,double y):StopCriteria(x,y){};
};
/*!
    \brief Дочерний класс критерия остановки.
    Останавливает процесс поиска минимума при достижении порового числа итераций.
    Унаследован от ранее созданного класса StopCriteria.
*/
class StopNULL: public StopCriteria{        //stop criteria: value of last improvement
public:
   bool condition(int, double) override;
   void quit_message() override;
   StopNULL(){};
   StopNULL(int x,double y):StopCriteria(x,y){};
};

#endif // STOPCRIT_H
