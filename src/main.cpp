#include <iostream>
#include "Dataset.h"
#include "Histogram.h"
#include "StatsCalc.h"
using namespace std;

int main() {

    // Load Dataset
    Dataset ds;
   if (!ds.loadFile("tests/test.csv")){
        return -1; // Exit if file fails to load
    }

    cout << endl;
    cout << "Data size: " << ds.getSize() << endl;

    // Statistics
    Statistics stats(ds.getData());
    cout << "\n--- Statistics ---" << endl;
    cout << "Mean: " << stats.compMean() << endl;
    cout << "Median: " << stats.compMedian() << endl;
    cout << "Mode: " << stats.compMode() << endl;
    cout << "Std Dev: " << stats.compStdDev() << endl;
    cout << "Variance: " << stats.compVar() << endl;
    cout << "Max: (" << stats.findMax().x << ", " << stats.findMax().y << ")" << endl;
    cout << "Min: (" << stats.findMin().x << ", " << stats.findMin().y << ")" << endl;

    // Histogram
    Histogram hist(ds.getData());
    hist.setBinNums(5); // Default 10 bins
    hist.genHist();

    vector<binRanges> ranges = hist.getBinRanges();
    vector<int> freqs = hist.getFrequency();

    cout << "\nBin Ranges and Frequencies:" << endl;
    for (int i = 0; i < hist.getBinNums(); i++){
        cout << "Bin " << i+1 << ": [" << ranges[i].lowEnd << " - " << ranges[i].highEnd << "] Freq: " << freqs[i] << endl;
    }

    cout << "Bin size: " << hist.getBinSize() << endl;
    cout << "Bin nums: " << hist.getBinNums() << endl;

    hist.exportHist("histogram.csv");

    return 0;
}