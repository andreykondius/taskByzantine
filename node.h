// класс с описанием узла

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <map>      // для тестов используется map, для большого проекта лучше использовать unordered_map

// структура, хранящая свойства узла
struct properties
{
    bool fType = true;      // тип генерала (true - честный, false - обманщик)
    int indexBase = -1;         // базовый ключ узла
    int index;              // ключ узла
    int count = 100;        // один из параметров для оценки (например, численность войска)
    // здесь должно быть больше данных, например параметры соединения
};

class node
{
    bool fType = false;
    int index = -1;         // ключ узла
    // первичный массив данных, полученный от других узлов с учётом своих данных (в кач-ве ключа может быть string, для простоты тестирования выбран int)
    std::multimap<int, properties> data;
    public:
        node(){}
        explicit node(const properties &prop);
        ~node();
        // ---- геттеры/сеттеры
        void setType(const bool val);
        bool isType() const;
        int getIndex() const;
        void setData(std::map<int, properties> &data);
        void pushData(const std::pair<int, properties> &val);       // добавление данных в контейнер data
        std::multimap<int, properties> &getData();
        // =======
        void sendMes(const int mes);     // отправка первонач. сведений о своём войске
};

// экземпляр контейнера узлов (для тестов реализован на std::vector)
extern std::map<int, node> nodes;

#endif // NODE_H
