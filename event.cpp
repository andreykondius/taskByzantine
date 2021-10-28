#include "event.h"
#include "message.h"

event::event()
{

}

void event::start(const revent &ev)
{
    // обработка сообщений для всех узлов
    switch(ev)
    {
        case _SendNodes :       // обменяться данными между узлами
//            changeMessage();
            break;
        case _IsRead :          // опросить все узлы и проверить их готовность
            break;
        case _Calc :            // посчитать логику узлов ("наступаем/отступаем")
            break;
    }
}
