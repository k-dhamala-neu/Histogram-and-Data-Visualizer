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
        double compMedian(); // Calculates Median
        double compMode(); // Calculates Mode
        double compVar(); // Calculates Variance
        double compStdDev(); // Calculates Standard Deviation
        DataPoint findMax(); // Finds the Maximum Value at a certain point
        DataPoint findMin(); // Finds the Minimum Value at a certain point

};


#endif