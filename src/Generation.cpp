//
// Created by mikah on 12.06.2025.
//

#include "Generation.h"

std::string Generator::generate() const {
    std::stringstream output;
    output << "global _main\n";
    output << "section .text\n";
    output << "_main:\n";

    output << "    mov eax, " << m_root.expr.int_lit.value.value() << '\n';
    output << "    ret";

    return output.str();
}
