#pragma once

#include <iostream>

class Kkmeans
{
public:
    Kkmeans(std::istream& aStream);

    void Run();

private:
    std::istream& mStream;
};
