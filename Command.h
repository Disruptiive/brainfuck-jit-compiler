#pragma once
#include <cstddef>

enum class CommandType {
    MoveRight,
    MoveLeft,
    Increment,
    Decrement,
    Output,
    Input,
    JumpZ,
    JumpNZ,
    Invalid,
};

class Command {
private:
    CommandType m_type{CommandType::Invalid};
    std::size_t m_jump{0};
    int         m_input{0};
public:
    Command() = default;
    explicit Command(const CommandType type) : m_type(type)
    {}
    Command(const CommandType type,const int amount) : m_type(type) {
        if (type == CommandType::Input) {
            m_input = amount;
        }
        else if (type == CommandType::JumpZ || type == CommandType::JumpNZ) {
            m_jump = static_cast<std::size_t>(amount);
        }
    }

    Command(const CommandType type,const std::size_t amount) : m_type(type) {
        if (type == CommandType::JumpZ || type == CommandType::JumpNZ) {
            m_jump = amount;
        }
        else if (type == CommandType::Input) {
            m_input = static_cast<int>(amount);
        }
    }
    void setJump(std::size_t j) {
        m_jump = j;
    }

    [[nodiscard]] std::size_t getJump() const {
        return m_jump;
    }

    [[nodiscard]] CommandType getType() const {
        return m_type;
    }
};