#include "node.h"

std::map<int, node> nodes;

// задание свойств узлу
node::node(const properties &prop)
{
    static int ind = 0;
    ++ind;
    index = ind;
    this->data.insert(std::pair<int, properties>(index, prop));
//    this->prop = prop;
    std::cout << "Node : " << index << ", count = " << prop.count <<
                 ", type = " << (prop.fType ? "truthful" : "faker") <<  std::endl;     // вывод номера узла
}

node::~node()
{
    data.clear();
}

void node::setType(const bool val)
{
    this->fType = val;
}

bool node::isType() const
{
    return this->fType;
}

int node::getIndex() const
{
    return index;
}

void node::setData(std::map<int, properties> &data)
{
    for(auto it : data)
        data.insert(std::pair<int, properties>(it.first, it.second));
}

void node::pushData(const std::pair<int, properties> &val)
{
    data.insert(std::pair<int, properties>(val.first, val.second));
}

std::multimap<int, properties> &node::getData()
{
    return this->data;
}
