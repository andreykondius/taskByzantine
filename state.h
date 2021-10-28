#ifndef STATE_H
#define STATE_H

#include "node.h"

// управление узлами
class state
{    
    bool fState = false;        // результирующее состояние узлов
public:
    state();
    void eraseNode(const int index)         // удаление определённого узла
    {// некий код
        // ..........
    }
    void calc();            // общая функция обработки узлов

};

#endif // STATE_H
