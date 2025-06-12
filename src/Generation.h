//
// Created by mikah on 12.06.2025.
//
#pragma once

#include <sstream>

#include "Nodes.h"


class Generator {
public:
    explicit Generator(Node::EXIT root):
    m_root (std::move(root)) {}

    [[nodiscard]] std::string generate() const;

private:
    const Node::EXIT m_root;
};


