#include <iostream>

#include "kkmeans.h"

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 4)
        {
            std::cerr << "Usage: kkmeans < input_data" << std::endl;
            return 1;
        }

        Kkmeans kkmeans(std::cin);
        kkmeans.Run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
