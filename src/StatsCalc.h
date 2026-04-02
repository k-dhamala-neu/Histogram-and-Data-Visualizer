#ifndef STATSCALC_H
#define STATSCALC_H

#include <vector>
#include "Dataset.h"

class Statistics {
    private:
        std::vector<DataPoint> dataset;
        double mean;

    public:
        Statistics(const std::vector<DataPoint>& inputData);
        ~Statistics(); 

        // Functions
        double compMean(); // Calculates Mean
        double compMedian() const; // Calculates Median
        double compMode() const; // Calculates Mode
        double compVar() const; // Calculates Variance
        double compStdDev() const; // Calculates Standard Deviation
        DataPoint findMax() const; // Finds the Maximum Value at a certain point
        DataPoint findMin() const; // Finds the Minimum Value at a certain point

};


#endif