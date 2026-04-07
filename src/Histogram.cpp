#include "Histogram.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;


Histogram::Histogram() : range(0.0), binNum(0), binSize(0.0) {}

Histogram::Histogram(const vector<DataPoint>& inputData) : range(0.0), binNum(0), binSize(0.0) {
    data = inputData; // Stores the full dataset
    range = getRange(); // Calculates and stores range on construction
}

Histogram::~Histogram() {}

double Histogram::getMin() const { // Find minimum y value
    double yMin = data[0].y; // From data = {(x1,y1), (x2,y2), ..., (xn,yn)}, takes the first element at the 0 index (which is (x1,y1)) and uses .y to pull the y1 val

    for (size_t i = 1; i < data.size(); i++){ // starts at one since yMin set to index 0 already
        if (data[i].y < yMin){
            yMin = data[i].y;
        }
    }

    return yMin;
}

double Histogram::getMax() const { 
    double yMax = data[0].y;

    for (size_t i = 1; i < data.size(); i++){ // starts at one since yMax set to index 0 already
        if (data[i].y > yMax)
        {
            yMax = data[i].y;
        }
    }

    return yMax;
}

double Histogram::getRange() const { // Calculates range from y values only; x is indep. variable (usually time)
    return getMax() - getMin();
}

void Histogram::setBinNums(size_t nums) {
    binNum = nums;
    if(binNum > 10){ // Max of 10 bins for directly set bins
        binNum = 10;
        cout << "Over Max Bin Size. Setting to Max Number of Bins (10)." << endl;
    }
    else if(binNum < 1){
        binNum = 1;
        cout << "Cannot Have less than 1 Number of Bins. Setting Number of Bins to 1." << endl;
    }
    binSize = range / binNum; // setting a specific num of bins makes bin size dependent on it
}

void Histogram::setBinSize(double size) {
    binSize = size;
    if (binSize <= 0){
        binSize = 1;
        cout << "Cannot have a Bin Size less than or equal to 0. Setting Bin Size to 1." << endl;
    }

    binNum = (size_t)ceil(range / binSize); // num of bins now dependent; value rounded up to nearest int with ceil
    if (binNum > 50){ // Max of 50 bins
        binNum = 50;
        binSize = range / binNum;
        cout << "Bin Size too small. Adjusting to max of 50 bins." << endl;
    }   // Number of bins capped at 50 when set via bin size for data flexibility
        // Direct bin number input is capped at 10 for display readability
}

size_t Histogram::getBinNums() const {
    return binNum;
}

double Histogram::getBinSize() const {
    return binSize;
}

const vector<binRanges> Histogram::getBinRanges() const {

     //Finding Min as the starting point for the bin ranges
    double min = getMin();

    binRanges r;

    r.lowEnd = min;
    r.highEnd = min + binSize;
    

   vector <binRanges> binPointRanges; // Used to store each bin Value range

   binPointRanges.push_back(r); // Adds the first bin range to the vector

    for (size_t i = 1; i < binNum; i++){
        r.lowEnd = r.highEnd; // Sets the new bin to have a lower end of the previous higher end
        r.highEnd = r.highEnd + binSize;
        binPointRanges.push_back(r); // Adds new bin range to the vector
    }
    return binPointRanges;
}

const vector<int> Histogram::getFrequency() const {

    double min = getMin();
    double max = getMax();
    double epsilon = 1e-9;

    vector<binRanges> binPointRanges = getBinRanges();

    vector<int> frequency; // Used to store the amount of each y datapoint in each bin
    int currFreq; // Current Frequency which will reset each bin
    bool carryOver = false; // for Edge case that value is the bin's high/low end

    for (size_t i = 0; i < binPointRanges.size(); i++){

        if (carryOver){
            currFreq = 1;
        }
        else{
            currFreq = 0;
        }
        carryOver = false;

        for (size_t j = 0; j < data.size(); j++){
            if (data[j].y > binPointRanges[i].lowEnd && data[j].y < binPointRanges[i].highEnd) {
                currFreq++;
            } else if (abs(data[j].y - binPointRanges[i].lowEnd) < epsilon && abs(binPointRanges[i].lowEnd - min) < epsilon) {
                currFreq++; // include minimum value in first bin
            } else if (abs(data[j].y - binPointRanges[i].highEnd) < epsilon && abs(binPointRanges[i].highEnd - max) < epsilon) {
                currFreq++; // include maximum value in last bin
            } else if (data[j].y == binPointRanges[i].highEnd && binPointRanges[i].highEnd != max) {
                carryOver = true;
            }
        }

        frequency.push_back(currFreq);
    }

    return frequency;
}

void Histogram::genHist(){ //Text based histogram in console with the y values
    if (binNum == 0){
        cerr << "Error: Number of bins not set" << endl;
        return; // Exits out of method
    }

    vector<binRanges> ranges = getBinRanges();
    vector<int> frequency = getFrequency();

    size_t maxFreq = 0;

    for (size_t i = 0; i < frequency.size(); i++){
         if (maxFreq < (size_t)frequency[i]){
            maxFreq = frequency[i];
         }
    }


    cout << "Histogram \n" << endl;

    for (size_t i = maxFreq; i > 0; i--){
        for (size_t j = 0; j < binNum; j++){
            if (frequency[j] >= (int)i){
                cout << "   x    ";
            }
            else {
                cout << "        ";
            }
        
        }
        cout << endl;
    }

    for (size_t i = 0; i < binNum; i++){
        cout << "Bin " << i + 1 << "   ";
    }

    cout << endl;

}


bool Histogram::exportHist(const string& fileName){
    if (binNum == 0){
        cerr << "Error: Number of bins not set" << endl;
        return false;
    }

    vector<binRanges> ranges = getBinRanges();
    vector<int> freqs = getFrequency();

    // Write data to csv
    ofstream dataFile("images/" + fileName);
    if (!dataFile.is_open()){
        cerr << "Error: Could not open file " << fileName << endl;
        return false;
    }

    dataFile << "lowEnd,highEnd,frequency" << endl;
    for (size_t i = 0; i < binNum; i++){
        dataFile << ranges[i].lowEnd << "," << ranges[i].highEnd << "," << freqs[i] << endl;
    }
    dataFile.close();

    // Write gnuplot script
    ofstream gpFile("images/plotHistogram.gp");
    if (!gpFile.is_open()){
        cerr << "Error: Could not create gnuplot script" << endl;
        return false;
    }

    gpFile << "set terminal png" << endl;
    gpFile << "set output 'images/histogram.png'" << endl;
    gpFile << "set title 'Histogram'" << endl;
    gpFile << "set xlabel 'Value'" << endl;
    gpFile << "set ylabel 'Frequency'" << endl;
    gpFile << "set datafile separator ','" << endl;
    gpFile << "set boxwidth " << binSize << " absolute" << endl;
    gpFile << "set style fill solid border -1" << endl;
    gpFile << "unset autoscale" << endl;
    gpFile << "set yrange [0:" << *max_element(freqs.begin(), freqs.end()) + 1 << "] noreverse" << endl; //makes element returns iterator of the max element (the index/position); needs dereferencing with * to get the value
    gpFile << "set xrange [" << ranges[0].lowEnd - binSize << ":" << ranges[binNum-1].highEnd + binSize << "]" << endl;
    
    if(binNum > 5){ //Rotates the bin ranges that are displayed so numbers dont overlap
        gpFile << "set xtics rotate by -45" << endl;
        gpFile << "set bmargin 5" << endl;
    }
    gpFile << "set xtics (";
    for(size_t i = 0; i < binNum; i++){
        double center = ranges[i].lowEnd + binSize/2;
        gpFile << "'" << ranges[i].lowEnd << "-" << ranges[i].highEnd << "' " << center;
        if(i < binNum - 1) gpFile << ", ";
    }
    gpFile << ")" << endl;
    gpFile << "plot 'images/" << fileName << "' skip 1 using (($1+$2)/2):3 with boxes notitle" << endl;
    gpFile.close();

    system("gnuplot images/plotHistogram.gp");

    return true;
}

bool Histogram::exportLinePlot(const string& fileName){

    // Write data to csv
    ofstream dataFile("images/" + fileName);
    if (!dataFile.is_open()){
        cerr << "Error: Could not open file " << fileName << endl;
        return false;
    }

    dataFile << "x,y" << endl;
    for (size_t i = 0; i < data.size(); i++){
        dataFile << data[i].x << "," << data[i].y << endl;
    }
    dataFile.close();

    // Write gnuplot script
    ofstream gpFile("images/plotLinePlot.gp");
    if (!gpFile.is_open()){
        cerr << "Error: Could not create gnuplot script" << endl;
        return false;
    }

    gpFile << "set terminal png" << endl;
    gpFile << "set output 'images/lineplot.png'" << endl;
    gpFile << "set title 'Line Plot'" << endl;
    gpFile << "set xlabel 'X'" << endl;
    gpFile << "set ylabel 'Y'" << endl;
    gpFile << "set datafile separator ','" << endl;
    gpFile << "set grid" << endl;

    //Setting Bounds for the plot
    double xMin = data[0].x; 
    double xMax = data[0].x;
    double yMin = data[0].y;
    double yMax = data[0].y;

    for (size_t i = 1; i < data.size(); i++){
        //Min for both x & y
        if (data[i].x < xMin) xMin = data[i].x;
        if (data[i].y < yMin) yMin = data[i].y;

        //Max for both x & y
        if (data[i].x > xMax) xMax = data[i].x;
        if (data[i].y > yMax) yMax = data[i].y;
    }
 
    gpFile << "unset autoscale" << endl; //overriding defaulted bounds

    gpFile << "set xrange [" << xMin << ":" << xMax << "]" << endl;

    if (yMin < 1e-6){ //Y values are very small
        gpFile << "set logscale y" << endl;
        gpFile << "set yrange [" << max(yMin, 1e-300) << ":" << yMax << "]" << endl; // Max compares both values and returns the higher one; prevents logscaling of 0 which is undef.
        } else {
            gpFile << "set yrange [" << yMin << ":" << yMax << "]" << endl;
        }


    gpFile << "plot 'images/" << fileName << "' skip 1 using 1:2 with lines notitle" << endl;
    gpFile.close();

    system("gnuplot images/plotLinePlot.gp");

    return true;
}
