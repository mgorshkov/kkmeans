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
    void OutputSamplesWithClusters(std::vector<SampleType> aSamples, std::vector<unsigned long> aAssignments);
    void VisualizeSamplesWithClusters(std::vector<SampleType> aSamples, std::vector<unsigned long> aAssignments);

    int mNumClusters;
    std::istream& mStream;
};
