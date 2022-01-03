#include <algorithm>
#include "Brainf.h"

namespace Brainf
{
    auto Repeat(std::string inString, int times) -> std::string
    {
        std::string outString{""};

        for (int i{0}; i < times; ++i)
        {
            outString.append(inString);
        }

        return outString;
    }

    auto Transpile(std::string source) -> std::string
    {
        auto loop_start_count{std::count(source.begin(), source.end(), '[')};
        auto loop_end_count{std::count(source.begin(), source.end(), ']')};

        if (loop_start_count != loop_end_count)
        {
            std::cout << "Error: bracket number mismatch!\n";
            return "";
        }

        std::string output{"#include <cstdio>\n"
                           "#include <algorithm>\n\n"
                           "auto main(int argc, char** argv) -> int\n"
                           "{\n"
                           "    char cells[30000];\n"
                           "    int pos{0};\n\n"};

        int indentSize{1};
        std::string indent{"    "};

        for (auto &token : source)
        {
            switch (token)
            {
                case '>':
                    output.append(Repeat(indent, indentSize));
                    output.append("pos = std::min(pos + 1, 29999);\n");
                    break;
                    
                case '<':
                    output.append(Repeat(indent, indentSize));
                    output.append("pos = std::max(pos - 1, 0);\n");
                    break;
                    
                case '+':
                    output.append(Repeat(indent, indentSize));
                    output.append("cells[pos] = std::min(cells[pos] + 1, 255);\n");
                    break;
                    
                case '-':
                    output.append(Repeat(indent, indentSize));
                    output.append("cells[pos] = std::max(cells[pos] - 1, 0);\n");
                    break;
                
                case '.':
                    output.append(Repeat(indent, indentSize));
                    output.append("std::putchar(cells[pos]);\n");
                    break;
                
                case ',':
                    output.append(Repeat(indent, indentSize));
                    output.append("cells[pos] = std::getchar();\n");
                    break;
                
                case '[':
                    output.append(Repeat(indent, indentSize));
                    output.append("while (cells[pos])\n");
                    output.append(Repeat(indent, indentSize));
                    output.append("{\n");
                    ++indentSize;
                    break;
                
                case ']':
                    output.append(Repeat(indent, indentSize));
                    output.append("}\n");
                    --indentSize;
                    break;

            }
        }

        output.append("\n    return 0;\n}\n");

        return output;
    }
}
