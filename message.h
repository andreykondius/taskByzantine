// класс с описанием системы сообщений между узлами

#ifndef MESSAGE_H
#define MESSAGE_H

#include "node.h"


const int arr[] = {100, 200, 300, 400};     // тестовые значения

class message
{
public:
    message();
    void loadNodes();         // добавление узлов
    void initialize(std::map<int, node> &nodes);            // инициализация узлов
    void exchangeVectors(std::map<int, node> &nodes);       // обмен векторами между узлами
    bool alg(std::map<int, node> &nodes);       // алгоритм
    void output(const bool val);      // вывод решения
};

#endif // CMESSAGE_H
