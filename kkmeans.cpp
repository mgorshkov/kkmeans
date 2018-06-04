#include <iostream>
#include <vector>
#include <string>

#include <dlib/image_transforms.h>
#include <dlib/image_saver/save_png.h>

#include "kkmeans.h"

Kkmeans::Kkmeans(int aNumClusters, std::istream& aStream)
    : mNumClusters(aNumClusters)
    , mStream(aStream)
{
}

static std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    auto stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

std::vector<Kkmeans::SampleType> Kkmeans::ReadInput()
{
    std::vector<SampleType> samples;
    std::string line;
    while (std::getline(mStream, line))
    {
        auto splitted = split(line, ';');
        SampleType sample;
        sample(0) = std::atof(splitted[0].c_str());
        sample(1) = std::atof(splitted[1].c_str());
        samples.push_back(sample);
    }
    return samples;
}

void Kkmeans::OutputSamplesWithClusters(std::vector<SampleType> aSamples, std::vector<unsigned long> aAssignments)
{
    for (std::size_t index = 0; index < aSamples.size(); ++index)
    {
        unsigned long cluster = aAssignments[index];
        // 86.11;55.33;5\n
        std::cout << std::fixed << std::setprecision(2)
                  << aSamples[index](0) << ";"
                  << aSamples[index](1) << ";"
                  << std::setprecision(0)
                  << cluster << std::endl;
    }
}

void Kkmeans::VisualizeSamplesWithClusters(std::vector<SampleType> aSamples, std::vector<unsigned long> aAssignments)
{
    double minX = aSamples[0](0);
    double maxX = aSamples[0](0);
    double minY = aSamples[0](1);
    double maxY = aSamples[0](1);
    for (std::size_t index = 1; index < aSamples.size(); ++index)
    {
        if (aSamples[index](0) < minX)
            minX = aSamples[index](0);
        if (aSamples[index](1) < minY)
            minY = aSamples[index](1);
        if (aSamples[index](0) > maxX)
            maxX = aSamples[index](0);
        if (aSamples[index](1) > maxY)
            maxY = aSamples[index](1);
    }

    dlib::array2d<dlib::rgb_pixel> img(1000, 1000);
    for (std::size_t index = 0; index < aSamples.size(); ++index)
    {
        unsigned long cluster = aAssignments[index];
        unsigned long x = (aSamples[index](0) - minX) / (maxX - minX) * 1000;
        unsigned long y = (aSamples[index](1) - minY) / (maxY - minY) * 1000;
        dlib::rectangle rect(x, y, x + 1, y + 1);
        dlib::rgb_pixel color = dlib::colormap_jet(cluster, 0, mNumClusters);
        dlib::draw_rectangle(img, rect, color, 2);
    }
    dlib::save_png(img, "bubble.png");
}

void Kkmeans::Run()
{
    using RbfKernel = dlib::radial_basis_kernel<SampleType>;

    using SampleVector = std::vector<SampleType>;
    RbfKernel kernel(0.01);

    dlib::kcentroid<RbfKernel> kc(kernel, 1, 15);
    dlib::kkmeans<RbfKernel> test(kc);
    test.set_number_of_centers(mNumClusters);

    SampleVector samples = ReadInput();

    SampleVector initialCenters;

    dlib::pick_initial_centers(mNumClusters, initialCenters, samples, kernel);

    std::vector<unsigned long> assignments = spectral_cluster(kernel, samples, mNumClusters);

    OutputSamplesWithClusters(samples, assignments);
    VisualizeSamplesWithClusters(samples, assignments);
}
