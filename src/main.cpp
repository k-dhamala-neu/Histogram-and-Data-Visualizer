#include <iostream>
#include "Dataset.h"
#include "Histogram.h"
#include "StatsCalc.h"
using namespace std;



int Menu() {
    cout << "Menu:" << endl;
    cout << "1. Load File" << endl;
    cout << "2. Display Statistics" << endl;
    cout << "3. Generate Histogram" << endl;
    cout << "4. Export Histogram" << endl;
    cout << "5. Exit" << endl;

    int choice;
    cin >> choice;

    return choice;
}










void displayStats(Statistics& stats) {

    cout << "\n--- Statistics ---" << endl;
    cout << "Menu:" << endl;
    cout << " Mean: " << stats.compMean() << endl;
    cout << "Median: " << stats.compMedian() << endl;
    cout << "Mode: " << stats.compMode() << endl;
    cout << "Std Dev: " << stats.compStdDev() << endl;
    cout << "Variance: " << stats.compVar() << endl;
    cout << "Max: (" << stats.findMax().x << ", " << stats.findMax().y << ")" << endl;
    cout << "Min: (" << stats.findMin().x << ", " << stats.findMin().y << ")" << endl;
}








int main() {

    // Load Dataset
    Dataset ds;
    bool fileLoaded = false;

    while(true){ // Loop until file is successfully loaded
        int choice = Menu();

        if (choice == 1){
            if (ds.loadFile("tests/test.csv")){
                fileLoaded = true; // file loads successfully
               cout << "File loaded successfully. Data size:" << ds.getSize() << endl;
            }
        }
        else if (choice == 2){
            if (!fileLoaded){
                cout << "Please load a file first." << endl; // Won't run stats without dataset loaded
            }
            else{
                Statistics stats(ds.getData());
                displayStats(stats);
            }
        }
        else if (choice == 3){
            if (!fileLoaded){
                cout << "Please load a file first." << endl;
            }
            else{
                Histogram hist(ds.getData()); // Creates histogram object with dataset
                hist.setBinNums(5); // Default 10 bins
                hist.genHist();
            }
        }
        else if (choice == 4){
            if (!fileLoaded){
                cout << "Please load a file first." << endl;
            }
            else{
                Histogram hist(ds.getData()); // Creates histogram object with dataset
                hist.setBinNums(5); // Default 10 bins
                hist.exportHist("histogram.csv");
                cout << "Histogram exported." << endl;
            }
        }
        else if (choice == 5){ //Exit
            cout << "Thank you for using the program." << endl;
            break;
        }
        else{
            cout << "Invalid choice. Please try again." << endl;
        }
    } 

    return 0;
}

   /*if (!ds.loadFile("tests/test.csv")){
        return -1; // Exit if file fails to load
    }

    cout << endl;
    cout << "Data size: " << ds.getSize() << endl;

    // Statistics
    Statistics stats(ds.getData());

    displayStats(stats);
    
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

    hist.exportHist("histogram.csv");*/

    