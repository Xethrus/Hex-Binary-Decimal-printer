//Bytes to hex table
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <bitset>

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        std::cerr << "oops LOL" << std::endl;
        return 1;
    }
    std::ifstream inFile;
    const int BUFFER_SIZE = 100;
    char buffer[BUFFER_SIZE];
    inFile.open(argv[1], std::ios::in | std::ios::binary);
    if (!inFile)
    {
        std::cerr << "Unable to load/open " << argv[1] << std::endl;
        return 1;
    }
    std::string line;
    int counter = 0;
    int iterationSize = 4;
    bool reading = true;
    std::cout << "| Printable           | Hexadecimal | Binary                              | Decimal         |" << std::endl;
    std::cout << "|---------------------+-------------+-------------------------------------+-----------------|" << std::endl;
    while (reading)
    {
        inFile.read(buffer, BUFFER_SIZE);
        if (!inFile)
        {
            reading = false;
        }

        counter++;
        for (int byteCounter = 0; byteCounter < inFile.gcount(); byteCounter += iterationSize)
        {
            std::cout << "|";
            for (int i = 0; i < iterationSize; i++)
            {
                if (byteCounter + i >= inFile.gcount())
                {
                    std::cout << "     ";
                    continue;
                }

                std::cout << std::setw(5) << std::setfill(' ');
                if (buffer[byteCounter + i] == ' ')
                {
                    std::cout << "' '";
                }
                else if (buffer[byteCounter + i] == '\0')
                {
                    std::cout << "\\0";
                }
                else if (buffer[byteCounter + i] == '\n')
                {
                    std::cout << "\\n";
                }
                else if (buffer[byteCounter + i] == '\t')
                {
                    std::cout << "\\t";
                }
                else if (isprint(buffer[byteCounter + i]))
                {
                    std::cout << buffer[byteCounter + i];
                }
                else
                {
                    std::cout << std::setw(0) << " \\x" << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[byteCounter + i];
                }
            }
            std::cout << " |";
            for (int i = 0; i < iterationSize; i++)
            {

                if (byteCounter + i >= inFile.gcount())
                {
                    std::cout << "   ";
                }
                else
                {
                    std::cout << " " << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[byteCounter + i];
                }
            }
            std::cout << " |";
            for (int i = 0; i < iterationSize; i++)
            {
                if (byteCounter + i >= inFile.gcount())
                {
                    std::cout << "         ";
                }
                else
                {
                    std::cout << " " << std::bitset<8>(buffer[byteCounter + i]);
                }
            }
            std::cout << " |";
            for (int i = 0; i < iterationSize; i++)
            {
                if (byteCounter + i >= inFile.gcount())
                {
                    std::cout << "    ";
                }
                else
                {
                    std::cout << " " << std::dec << std::setw(3) << std::setfill(' ') << (int)buffer[byteCounter + i];
                }
            }
            std::cout << " |";
            std::cout << std::endl;
        }
    }
//    std::cout << "bytes: " << inFile.gcount() << "\n";
    return 0;
};
