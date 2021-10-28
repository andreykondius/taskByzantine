#include <random>
#include <ctime>

#include "state.h"

#include "message.h"

state::state()
{
}

// основная логика работы системы
void state::calc()
{
    message msg;
    // шаг 1 загрузка узлов
    std::cout << "Step 1: list nodes." << std::endl;
    msg.loadNodes();    // загрузка узлов

    // шаг 2: обмен начальными состояниями между узлами (прим. предатель отправляет ложные данные)
    std::cout << "Step 2: change properties." << std::endl;
    msg.initialize(nodes);       // формирование начальных векторов состояний

    // шаг 3: обмен векторами между узлами (прим. предатель отправляет ложные данные)
    std::cout << "Step 3: exchange of vectors between nodes:" << std::endl;
    msg.exchangeVectors(nodes);       // формирование полных векторов состояний (в тесте 4 x 4)

    // шаг 4: реализация алгоритма вмизантийских генералов
    std::cout << "Step 4: release algorithm:" << std::endl;
    fState = msg.alg(nodes);       // результирующий вектор (генералы и их статус)

    // шаг 5: принятое алгоритмом решение
    std::cout << "Step 5: output:" << std::endl;
    // Если большинстов (>=2/3 от общего числа) узлов отправили честные данные, то на выходе будет TRUE.
    // иначе FALSE
    msg.output(fState);

}
