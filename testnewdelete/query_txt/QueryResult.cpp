/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-08 20:21:32
 * @LastEditTime : 2021-08-08 21:13:10
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testnewdelete/QueryResult.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include "QueryResult.h"

std::ostream &print(std::ostream &os, const QueryResult &qr)
{
    os << qr.word << " occurs " << qr.lines->size() << (qr.lines->size() > 1 ? " times\n" : " time\n");
    for (auto &&num : *qr.lines)
        os << "\t(line " << num + 1 << ")" << *(qr.file->begin() + num) << std::endl;
    return os;
}