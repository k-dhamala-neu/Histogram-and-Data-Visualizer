#include "StatsCalc.h"
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

Statistics::Statistics(const vector<DataPoint>& inputData) {
    dataset = inputData; // Stores the full dataset
    mean = compMean();   // Calculates and stores mean on construction
}

Statistics::~Statistics() {}

double Statistics::compMean () {
    double sum = 0;
    for (size_t i = 0; i < dataset.size(); i++){
        sum += dataset[i].y;
    }

    return static_cast<double>((sum) /(dataset.size()));
}

double Statistics::compMedian () const {

    vector<double> yVals;
    for (size_t i = 0; i < dataset.size(); i++){
        yVals.push_back(dataset[i].y);
    }

    sort(yVals.begin(), yVals.end());

    if (yVals.size() % 2 == 0){
        double midSum = yVals[((yVals.size() /2) - 1)] + yVals[(yVals.size() /2)];
        return static_cast<double>((midSum) / 2);
    }
    else{
        return yVals[yVals.size() / 2];
    }
}

double Statistics::compMode () const {

    if (dataset.size() == 0){
        cerr << "Error: No values in dataset." << endl;
        return numeric_limits<double>::quiet_NaN(); // NaN return since its a safe return that acts as a way to say N/A
    }

    if (dataset.size() == 1){
        return dataset[0].y;
    }

    vector<double> yVals;
    for (size_t i = 0; i < dataset.size(); i++){
        yVals.push_back(dataset[i].y);
    }

    sort(yVals.begin(), yVals.end());

    int count = 1;
    size_t pos = 0;
    int leadingCount = 0;

    for ( size_t i = 1; i < yVals.size(); i++){
        if(yVals[i] == yVals[i-1]){
            count++;
            if (count > leadingCount){
                leadingCount = count;
                pos = i;
            }
        }
        else{
            count = 1;
        }
    }

    if (leadingCount <= 1){
    return numeric_limits<double>::quiet_NaN();
}

    return yVals[pos];

}

double Statistics::compVar () const{ // Population Variance

    double sum = 0;
    for (size_t i = 0; i < dataset.size(); i++){
        sum += pow((dataset[i].y - mean),2);
    }

    return static_cast<double>((sum) /(dataset.size()));
}


double Statistics::compStdDev () const {
    double var = compVar();

    return pow(var,.5);
}

DataPoint Statistics::findMax () const {

    double yMax = dataset[0].y;
    size_t pos = 0;

    for (size_t i = 1; i < dataset.size(); i++){ // starts at one since yMax set to index 0 already
        if (dataset[i].y > yMax)
        {
            yMax = dataset[i].y;
            pos = i;
        }
    }

    return dataset[pos];

}

DataPoint Statistics::findMin () const {

    double yMin = dataset[0].y;
    size_t pos = 0;

    for (size_t i = 1; i < dataset.size(); i++){ // starts at one since yMin set to index 0 already
        if (dataset[i].y < yMin)
        {
            yMin = dataset[i].y;
            pos = i;
        }
    }

    return dataset[pos];
}