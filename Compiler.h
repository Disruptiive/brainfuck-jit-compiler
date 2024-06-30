#pragma once

#include <stack>
#include <vector>
#include <array>
#include <string_view>
#include <stdexcept>

#include "Command.h"

class UnmatchedBracketException : public std::runtime_error {
public:
    explicit UnmatchedBracketException(const std::string& message)
        : std::runtime_error(message) {}
};

class Compiler {
private:
    std::vector<Command> m_commands;
    std::array<int,101>  m_registers{};
    std::size_t          m_ptr;
    std::size_t          m_pc;

    void moveRight() {
        if(m_ptr < 100) ++m_ptr;
        else m_ptr = 0;
    }

    void moveLeft() {
        if (m_ptr > 0) --m_ptr;
        else m_ptr = 100;
    }

    void increment() {
        ++m_registers[m_ptr];
    }
    void decrement() {
        --m_registers[m_ptr];
    }
    void output() const {
        std::cout << static_cast<char>(m_registers[m_ptr]);
    }

    void input() {
        unsigned char c{0};
        std::cin >> c;
        m_registers[m_ptr] = static_cast<int>(c);
    }

    void jumpZ() {
        if (m_registers[m_ptr] == 0) m_pc = m_commands[m_pc].getJump() + 1;
        else                       ++m_pc;
    }

    void jumpNZ() {
        if (m_registers[m_ptr] != 0) m_pc = m_commands[m_pc].getJump();
        else                       ++m_pc;
    }

public:
    explicit Compiler(const std::string_view s): m_commands(s.size()), m_ptr(0),m_pc(0){
        std::stack<int> stk;
        for (int i=0;i<s.size();++i) {
            switch (s[i]) {
                case '>':
                    m_commands[i] = Command(CommandType::MoveRight);
                    break;
                case '<':
                    m_commands[i] = Command(CommandType::MoveLeft);
                    break;
                case '+':
                    m_commands[i] = Command(CommandType::Increment);
                    break;
                case '-':
                    m_commands[i] = Command(CommandType::Decrement);
                    break;
                case '.':
                    m_commands[i] = Command(CommandType::Output);
                    break;
                case ',':
                    m_commands[i] = Command(CommandType::Input);
                    break;
                case '[':
                    stk.push(i);
                    m_commands[i] = Command(CommandType::JumpZ);
                    break;
                case ']':
                    if (!stk.empty()) {
                        m_commands[stk.top()].setJump(i);
                        m_commands[i] = Command(CommandType::JumpNZ,stk.top());
                        stk.pop();
                    }
                    else throw UnmatchedBracketException("Unmatched Closing Bracket ']'");
                    break;
                default:
                    m_commands[i] = Command(CommandType::Invalid);
            }
        }
        if (!stk.empty()) throw UnmatchedBracketException("Unmatched Opening Bracket '['");
    }

    void execute() {
        while (m_pc < m_commands.size()) {
            switch(m_commands[m_pc].getType()){
                case CommandType::MoveRight:
                    moveRight();
                    ++m_pc;
                    break;
                case CommandType::MoveLeft:
                    moveLeft();
                    ++m_pc;
                    break;
                case CommandType::Increment:
                    increment();
                    ++m_pc;
                    break;
                case CommandType::Decrement:
                    decrement();
                    ++m_pc;
                    break;
                case CommandType::Output:
                    output();
                    ++m_pc;
                    break;
                case CommandType::Input:
                    input();
                    ++m_pc;
                    break;
                case CommandType::JumpZ:
                    jumpZ();
                    break;
                case CommandType::JumpNZ:
                    jumpNZ();
                    break;
                case CommandType::Invalid:
                    ++m_pc;
                    break;
            }
        }
    }


};