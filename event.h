// класс с описанием системы событий

#ifndef CEVENT_H
#define CEVENT_H

// описание основных событий
enum revent
{
    _SendNodes,         // отправить широковещательное сообщение всем узлам
    _IsRead,            // проверка готовности всех узлов
    _Calc               // посчитать логику узлов ("наступаем/отступаем")
};

class event
{
public:
    event();
    void start(const revent &ev);       // старт обработки событий
};

#endif // CEVENT_H
