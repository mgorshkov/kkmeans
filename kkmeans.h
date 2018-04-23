#pragma once

#include <iostream>
#include <dlib/clustering.h>

class Kkmeans
{
public:
    Kkmeans(int aNumClusters, std::istream& aStream);

    void Run();

private:
    using SampleType = dlib::matrix<double, 2, 1>;
    std::vector<SampleType> ReadInput();

    int mNumClusters;
    std::istream& mStream;
};
