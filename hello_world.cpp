#include <iostream>
#include <string_view>
#include "Compiler.h"

int main() {
    constexpr std::string_view string_v{
        "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++."
    };
    Compiler c(string_v);
    c.execute();
}
