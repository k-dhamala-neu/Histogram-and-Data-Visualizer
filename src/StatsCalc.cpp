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

double Statistics::compMean() {
    double sum = 0;
    for (int i = 0; i < dataset.size(); i++){
        sum += dataset[i].y;
    }

    return (double) sum / dataset.size();
}

double Statistics::compMedian() {

    vector<double> yVals;
    for (int i = 0; i < dataset.size(); i++){
        yVals.push_back(dataset[i].y);
    }

    sort(yVals.begin(), yVals.end());

    if (yVals.size() % 2 == 0){
        double midSum = yVals[((yVals.size() /2) - 1)] + yVals[(yVals.size() /2)];
        return (double) midSum / 2;
    }
    else{
        return yVals[yVals.size() / 2];
    }
}

double Statistics::compMode() {

    if (dataset.size() == 0){
        cerr << "Error: No values in dataset." << endl;
        return 0;
    }

    if (dataset.size() == 1){
        return dataset[0].y;
    }

    vector<double> yVals;
    for (int i = 0; i < dataset.size(); i++){
        yVals.push_back(dataset[i].y);
    }

    sort(yVals.begin(), yVals.end());

    int count = 1;
    int pos = 0;
    int leadingCount = 0;

    for (int i = 1; i < yVals.size(); i++){
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
    cout << "No Mode" << endl;
    return 0;
}

    return yVals[pos];

}

double Statistics::compVar(){ // Population Variance

    double sum = 0;
    for (int i = 0; i < dataset.size(); i++){
        sum += pow((dataset[i].y - mean),2);
    }

    return (double) sum / dataset.size();
}


double Statistics::compStdDev() {
    double var = compVar();

    return pow(var,.5);
}

DataPoint Statistics::findMax() {

    double yMax = dataset[0].y;
    int pos = 0;

    for (int i = 1; i < dataset.size(); i++){ // starts at one since yMax set to index 0 already
        if (dataset[i].y > yMax)
        {
            yMax = dataset[i].y;
            pos = i;
        }
    }

    return dataset[pos];

}

DataPoint Statistics::findMin() {

    double yMin = dataset[0].y;
    int pos = 0;

    for (int i = 1; i < dataset.size(); i++){ // starts at one since yMin set to index 0 already
        if (dataset[i].y < yMin)
        {
            yMin = dataset[i].y;
            pos = i;
        }
    }

    return dataset[pos];
}