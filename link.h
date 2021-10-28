#ifndef LINK_H
#define LINK_H
#include "node.h"

// загрузка состояний узла
class link
{
public:
    link();
    void setProperties(const int index)        // задать состояние узла index
    {
        // некий код по загрузке свойств узла, например:
        // node n;
        // n.prop.count = 10;
        // .........
    }
    properties &getProperties(const int index)         // прочитать состояние для выбранного узла
    {
        // некий код
        // nodes.getproperties ........
    }

};

#endif // LINK_H
