// Brainf - A Brainfuck to C++ transpiler
#include <iostream>
#include <fstream>
#include "Brainf.h"

void showHelp(const char* executable)
{
    std::cout << "Usage:\n";
    std::cout << "  brainf inputFile [outputFile]\n";
    std::cout << "  If outputFile is not specified, output is written to [inputFile].out.cpp\n";
}

auto main(int argc, char** argv) -> int
{
    if (argc < 2)
    {
        showHelp(argv[0]);
        return 1;
    }

    std::string testSource{"++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++."};
    std::ofstream outFile("out.cpp");

    outFile << Brainf::Transpile(testSource);
    outFile.close();
    return 0;
}
