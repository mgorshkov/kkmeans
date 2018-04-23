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

void Kkmeans::Run()
{
    typedef dlib::radial_basis_kernel<SampleType> kernel_type;
    dlib::kcentroid<kernel_type> kc(kernel_type(0.1),0.01, 8);

    dlib::kkmeans<kernel_type> test(kc);

    std::vector<SampleType> samples = ReadInput();

    std::vector<SampleType> initial_centers;

    test.set_number_of_centers(mNumClusters);

    pick_initial_centers(mNumClusters, initial_centers, samples, test.get_kernel());

    test.train(samples,initial_centers);

    std::vector<unsigned long> assignments = spectral_cluster(kernel_type(0.1), samples, mNumClusters);

    double minX = samples[0](0);
    double maxX = samples[0](0);
    double minY = samples[0](1);
    double maxY = samples[0](1);
    for (std::size_t index = 1; index < samples.size(); ++index)
    {
        if (samples[index](0) < minX)
            minX = samples[index](0);
        if (samples[index](1) < minY)
            minY = samples[index](1);
        if (samples[index](0) > maxX)
            maxX = samples[index](0);
        if (samples[index](1) > maxY)
            maxY = samples[index](1);
    }

    dlib::array2d<dlib::rgb_pixel> img(1000, 1000);
    for (std::size_t index = 0; index < samples.size(); ++index)
    {
        unsigned long cluster = assignments[index];
        unsigned long x = (samples[index](0) - minX) / (maxX - minX) * 1000;
        unsigned long y = (samples[index](1) - minY) / (maxY - minY) * 1000;
        dlib::rectangle rect(x, y, x + 1, y + 1);
        dlib::rgb_pixel color = dlib::colormap_jet(cluster, 0, mNumClusters);
        dlib::draw_rectangle(img, rect, color, 2);
    }
    dlib::save_png(img, "bubble.png");
}
