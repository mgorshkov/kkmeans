#include <iostream>

#include "kkmeans.h"

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: cat inputdata | kkmeans <numclusters>" << std::endl;
            return 1;
        }

        int numclusters = std::atoi(argv[1]);
        if (numclusters == 0)
        {
            std::cerr << "Incorrect number of clusters: " << argv[1] << std::endl;
            return 1;
        }

        Kkmeans kkmeans(numclusters, std::cin);
        kkmeans.Run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
