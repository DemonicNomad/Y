//
// Created by mikah on 12.06.2025.
//
#pragma once
#ifndef NODES_H
#define NODES_H

#include "Token.h"

namespace Node {
    struct EXPR {
        Token int_lit;
    };
    struct EXIT {
        EXPR expr;
    };
}
#endif //NODES_H
