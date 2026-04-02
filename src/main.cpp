#include <iostream>
#include "Dataset.h"
#include "Histogram.h"
#include "StatsCalc.h"
using namespace std;



int Menu() {
    cout << "\n--- Main Menu ---" << endl;
    cout << "1. Load File" << endl;
    cout << "2. Display Statistics" << endl;
    cout << "3. Generate Histogram" << endl;
    cout << "4. Export Histogram" << endl;
    cout << "5. Run Test Case" << endl;
    cout << "6. Exit" << endl;

    string input;
    int choice;

    while(true){
        cout << endl;
        cout << "Enter choice: ";
        cin >> input;

        // Check all characters are digits by taking a string then reading it
        bool isValid = true;
        for (size_t i = 0; i < input.size(); i++){
            if (!isdigit(input[i])){ // works on doubles b/c '.'
                isValid = false;
                break;
            }
        }

        if (!isValid){
            cout << "Invalid input. Please enter a whole number." << endl;
        }
        else{
            choice = stoi(input); // string to int
            if (choice < 1 or choice > 6){
                cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
            }
            else{
                return choice;
            }
        }
    }
}



void displayStats(Statistics& stats) {

    cout << "\n--- Statistics ---" << endl;
    cout << " Mean: " << stats.compMean() << endl;
    cout << "Median: " << stats.compMedian() << endl;
    cout << "Mode: " << stats.compMode() << endl;
    cout << "Std Dev: " << stats.compStdDev() << endl;
    cout << "Variance: " << stats.compVar() << endl;
    cout << "Max: (" << stats.findMax().x << ", " << stats.findMax().y << ")" << endl;
    cout << "Min: (" << stats.findMin().x << ", " << stats.findMin().y << ")" << endl;
}

void testCase(Dataset &ds){
    if (!ds.loadFile("tests/test.csv")){
        return; // Exit if file fails to load
    }

    cout << endl;
    cout << "Data size: " << ds.getSize() << endl;

    // Statistics
    Statistics stats(ds.getData());

    displayStats(stats);
    
    // Histogram
    Histogram hist(ds.getData());
    hist.setBinNums(5); // 5 bins
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
}



int main() {

    // Load Dataset
    Dataset ds;
    bool fileLoaded = false;

    // Chosen filepath
    string chosenfPath;

    while(true){ // Loop until file is successfully loaded
        int choice = Menu();

        switch (choice)
        {
        case 1:

            cout << "What is the filepath for your chosen csv/txt file?" << endl;
            cin >> chosenfPath;

            if (ds.loadFile(chosenfPath) or ds.loadFile(chosenfPath + ".txt") or ds.loadFile(chosenfPath + ".csv")){
                fileLoaded = true; // file loads successfully
                cout << "File loaded successfully. Data size:" << ds.getSize() << endl;
            }
            else{
                cout << "File was unable to be loaded." << endl;
            }
            break;
        
        case 2:

            if (!fileLoaded){
                cout << "Please load a file first." << endl; // Won't run stats without dataset loaded
            }
            else{
                Statistics stats(ds.getData());
                displayStats(stats);
            }
            break;

        case 3:

            if (!fileLoaded){
                cout << "Please load a file first." << endl;
            }
            else{
                Histogram hist(ds.getData()); // Creates histogram object with dataset
                hist.setBinNums(5); // 5 bins
                hist.genHist();
            }
            break;

        case 4:

            if (!fileLoaded){
                cout << "Please load a file first." << endl;
            }
            else{
                Histogram hist(ds.getData()); // Creates histogram object with dataset
                hist.setBinNums(5); // 5 bins
                hist.exportHist("histogram.csv");
                cout << "Histogram exported." << endl;
            }
            break;
            
        case 5:
            cout << "Running test case with tests/test.csv.." << endl;
            testCase(ds);
            ds.clearData();
            fileLoaded = false;
            cout << "Data cleared. Please load a new file for continued usage." << endl;
            break;

        case 6:

            cout << "Thank you for using the program." << endl;
            return 0;

        default:

            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}

   

    