#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include "message.h"
#include "link.h"

message::message()
{

}
static int count = sizeof(arr)/sizeof(arr[0]);       // кол-во узлов
void message::loadNodes()
{
    link l;     // линковка узлов к сети

    std::mt19937 gen(static_cast<unsigned int>(time(nullptr)));

    for(auto i=0; i < count; ++i)
    {
        properties prop;    // установка свойств узлов (так же задаётся извне)
        prop.index = i;
        prop.indexBase = -1;
        std::uniform_int_distribution<> uid(0, count-1);
        // этот параметр задаётся для тестов случайным образом, в реальном проекте он должен считываться через класс link
        prop.count = arr[ uid(gen) ];
        std::uniform_int_distribution<> uid2(0, 1);
        // этот параметр задаётся для тестов случайным образом, в реальном проекте он должен считываться через класс link
        prop.fType = uid2(gen) == 0? true : false;
        nodes[i] = node(prop);
        nodes[i].setType(prop.fType);
    }
}

// первоначальная инициализация узлов
void message::initialize(std::map<int, node> &nodes)
{
    std::mt19937 gen(static_cast<unsigned int>(time(nullptr)));
    for(auto it : nodes)
    {
        for(auto it2 : nodes)
            if(it.first != it2.first)
            {
                properties prop = (it2.second.getData().lower_bound(it2.second.getIndex()))->second;
                // имитация предательcких сообщений
                if (!prop.fType)
                {
                    std::uniform_int_distribution<> uid(0, 999);
                    prop.count = uid(gen);
                }
                nodes[it.first].pushData( std::pair<int, properties>(it2.second.getIndex(),
                                                                      prop));

            }
    }
    std::cout << "Vectors after initialize:" << std::endl;
    for(auto it : nodes)
    {
        std::cout << "Node : " << it.second.getIndex() << std::endl;
        std::cout << "{";
        for(auto it2 : it.second.getData())
            std::cout << it2.second.count << " ";      // упрощённый вывод для тестов
        std::cout << "}" << std::endl;
    }
}

// обмен векторами между узлами
void message::exchangeVectors(std::map<int, node> &nodes)
{
    std::mt19937 gen(static_cast<unsigned int>(time(nullptr)));
    std::multimap<int, node> vec;
    for(auto it : nodes)
    {
        for(auto it2 : nodes)
            if(it.first != it2.first)
        {
            for(auto iter : it2.second.getData())
//                if(iter.second.count == it.first)
            {
                properties prop = iter.second;
                prop.indexBase = it.first;
                // имитация предательcких сообщений

                if (!nodes[it2.first].isType())
                {
                    std::uniform_int_distribution<> uid(0, 999);
                    prop.count = uid(gen);//arr[ uid(gen) ];
                }
                vec.insert(std::pair<int, node>(iter.first, node(prop)));
            }
        }
    }

    for(auto it : nodes)
    {
        for(auto it2 : vec)
        {
            for(auto j : it2.second.getData())
                if(j.second.indexBase == it.first)
            {
                properties prop = j.second;
                nodes[it.first].getData().insert(std::pair<int, properties>(j.first,
                                                                  prop));
            }
        }
    }

    std::cout << "Vectors after exchange:" << std::endl;
    for(auto it : nodes)
    {
        std::cout << "Node : " << it.second.getIndex() << std::endl;
        std::cout << "{";
        int i = 0;
        for(auto it2 : it.second.getData())
        {
            ++i;
//            std::cout <<"[" << it2.second.index << "] = " << it2.second.count << " ";      // упрощённый вывод для тестов
            std::cout << it2.second.count << " ";      // упрощённый вывод для тестов
            if(i == count)
            {
                i = 0;
                std::cout << std::endl;
            }
        }
        std::cout << "}" << std::endl;
    }
}

bool message::alg(std::map<int, node> &nodes)
{
    // суть алгоритма в том, чтоб 2/3 или более узлов отправляли правдивые данные
    std::cout << "Vector : " << std::endl;
    std::vector<int> vec;
    for(auto it : nodes)
    {
        vec.push_back(0);
        auto index = vec.size()-1;
        std::vector<int> vecNode;
        int indCount = -1;
        for(auto dt : it.second.getData())
        {
            ++indCount;
            if(indCount >= count)
                break;
            int i = 0;
            properties prop = dt.second;
            for(auto it2 : it.second.getData())
            {
                if(dt.first != it2.first)
                    if(dt.second.index == it2.second.index)
                    {
                        if(prop.count == it2.second.count)
                            ++i;
                    }
            }
            vecNode.push_back(0);
            auto indNode = vecNode.size()-1;
            vecNode[indNode] = 0;
            if (i >= 1)
                vecNode[indNode] = 1;
        }
        int j = 0;
        std::cout << "VecNode:" << std::endl;       // вектор узла с принятыми решениями
        for(unsigned int i=0; i < vecNode.size(); ++i)
        {
            std::cout << vecNode[i] << "  ";
            if(vecNode[i] > 0)
                ++j;
        }
        std::cout << std::endl;
        if(j >= 2.0/3.0 * count)
            vec[index] = 1;

        std::cout << "Solution " << index << " node = " << vec[index] << "  " << std::endl;
    }
    std::cout << std::endl;
    int index = 0;
    for(unsigned int i=0; i < vec.size(); ++i)
        if(vec[i] == 1)
            ++index;
    return (index >= 2.0/3.0*count);
}

void message::output(const bool val)
{
    std::cout << (val ? "TRUE" : "FALSE") << std::endl;
}
