// Part One: Bytes to hex table
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <bitset>
#include <climits>

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        std::cerr << "input or output file needed" << std::endl;
        return 1;
    }
    std::ifstream inFile;
    std::ofstream outFile;
    const int BUFFER_SIZE = 100;
    unsigned char buffer[BUFFER_SIZE];
    inFile.open(argv[1], std::ios::in | std::ios::binary);
    outFile.open(argv[2]);
    if (!inFile)
    {
        std::cerr << "Unable to load/open " << argv[1] << std::endl;
        return 1;
    }
    if (!outFile)
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
    outFile << "| Printable           | Hexadecimal | Binary                              | Decimal         |" << std::endl;
    outFile << "|---------------------+-------------+-------------------------------------+-----------------|" << std::endl;
    while (reading)
    {
       
        inFile.read(reinterpret_cast<char*>(buffer), BUFFER_SIZE);
        if (!inFile)
        {
            reading = false;
        }

        counter++;
        for (int byteCounter = 0; byteCounter < inFile.gcount(); byteCounter += iterationSize)
        {
            std::cout << "|";
            outFile << "|";
            for (int i = 0; i < iterationSize; i++)
            {
                if (byteCounter + i >= inFile.gcount())
                {
                    std::cout << "     ";
                    outFile << "     ";
                    continue;
                }

                std::cout << std::setw(5) << std::setfill(' ');
                outFile << std::setw(5) << std::setfill(' ');
                if (buffer[byteCounter + i] == ' ')
                {
                    std::cout << "' '";
                    outFile << "' '";
                }
                else if (buffer[byteCounter + i] == '\0')
                {
                    std::cout << "\\0";
                    outFile << "\\0";
                }
                else if (buffer[byteCounter + i] == '\n')
                {
                    std::cout << "\\n";
                    outFile << "\\n";
                }
                else if (buffer[byteCounter + i] == '\t')
                {
                    std::cout << "\\t";
                    outFile << "\\t";
                }
                else if (isprint(buffer[byteCounter + i]))
                {
                    std::cout << buffer[byteCounter + i];
                    outFile << buffer[byteCounter + i];
                }
                else
                {
                    std::cout << std::setw(0) << " \\x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(buffer[byteCounter + i]);
                    outFile << std::setw(0) << " \\x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(buffer[byteCounter + i]);
                }
            }
            std::cout << " |";
            outFile << " |";
            for (int i = 0; i < iterationSize; i++)
            {

                if (byteCounter + i >= inFile.gcount())
                {
                    std::cout << "   ";
                    outFile << "   ";
                }
                else
                {
                    std::cout << " " << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(buffer[byteCounter + i]);
                    outFile << " " << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(buffer[byteCounter + i]);
                }
            }
            std::cout << " |";
            outFile << " |";
            for (int i = 0; i < iterationSize; i++)
            {
                if (byteCounter + i >= inFile.gcount())
                {
                    std::cout << "         ";
                    outFile << "         ";
                }
                else
                {
                    std::cout << " " << std::bitset<8>(buffer[byteCounter + i]);
                    outFile << " " << std::bitset<8>(buffer[byteCounter + i]);
                }
            }
            std::cout << " |";
            outFile << " |";
            for (int i = 0; i < iterationSize; i++)
            {
                if (byteCounter + i >= inFile.gcount())
                {
                    std::cout << "    ";
                    outFile << "    ";
                }
                else
                {
                    std::cout << " " << std::dec << std::setw(3) << std::setfill(' ') << static_cast<unsigned int>(buffer[byteCounter + i]);
                    outFile << " " << std::dec << std::setw(3) << std::setfill(' ') << static_cast<unsigned int>(buffer[byteCounter + i]);
                }
            }
            std::cout << " |";
            outFile << " |";
            std::cout << std::endl;
            outFile << std::endl;
        }
    }
    return 0;
};
