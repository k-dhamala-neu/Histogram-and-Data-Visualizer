#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <vector>
#include <string>
#include "Dataset.h"

struct binRanges
{
    double lowEnd;
    double highEnd;
};

class Histogram {
    private:
        std::vector<DataPoint> data;  // Dataset passed in from Dataset class
        double range; // Range of values stored in dataset
        int binNum; // Number of bins in histogram
        double binSize; // Size of each bin in the histogram

    public:
        Histogram(const std::vector<DataPoint>& inputData); // Constructor takes dataset
        ~Histogram(); 

        // Functions
        double getMin() const; // Gets minimum value of the dependent variable (y)
        double getMax() const; // Gets maximum value of the dependent variable (y)
        double getRange() const; // Gets the range of the dataset
        void setBinNums(int nums); // Sets the number of bins for the histogram
        int getBinNums() const; // Gets the number of bins for the histogram
        void setBinSize(double size); // Sets the value each bin holds
        double getBinSize() const; // Gets the value each bin holds
        const std::vector<binRanges> getBinRanges () const; // Gets the bin ranges for each bin
        const std::vector<int> getFrequency() const; // Gets the Frequency of each bin
        void genHist(); // Generates a text-based histogram
        bool exportHist(const std::string& fileName); // Shows the histogram as an image file

};


#endif