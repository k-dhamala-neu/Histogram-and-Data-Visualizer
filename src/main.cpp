#include <iostream>
#include <cmath>
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
    cout << "6. Change Bin Size" << endl;
    cout << "7. Change Number of Bins" << endl;
    cout << "8. Export Line Graph" << endl;
    cout << "9. Exit" << endl;

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
            cout << "Invalid input. Please enter a whole number between 1 and 9." << endl;
        }
        else{
            choice = stoi(input); // string to int
            if (choice < 1 or choice > 9){
                cout << "Invalid choice. Please enter a number between 1 and 9." << endl;
            }
            else{
                return choice;
            }
        }
    }
}


void displayStats(Statistics& stats) {

    cout << "\n--- Statistics ---" << endl;
    cout << "Mean: " << stats.compMean() << endl;
    cout << "Median: " << stats.compMedian() << endl;
    double mode = stats.compMode();
    if (isnan(mode)){ // if there is no value for mode
        cout <<  "Mode: No Mode" << endl;
    }
    else{
        cout << "Mode: " << mode << endl;
    }
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
    for (size_t i = 0; i < hist.getBinNums(); i++){
        cout << "Bin " << i+1 << ": [" << ranges[i].lowEnd << " - " << ranges[i].highEnd << "] Freq: " << freqs[i] << endl;
    }

    cout << "Bin size: " << hist.getBinSize() << endl;
    cout << "Bin nums: " << hist.getBinNums() << endl;

    hist.exportHist("histogram.csv");
}



int main() {

    // Load blank Dataset
    Dataset ds;
    bool fileLoaded = false;

    // Load Blank Histogram
    Histogram hist;

    // Chosen filepath
    string chosenfPath;

    while(true){ // Loop until file is successfully loaded
        int choice = Menu();

        switch (choice)
        {
        case 1: // Load file

            ds.clearData(); // clear previous data before loading new file

            cout << "What is the filepath for your chosen csv/txt file?" << endl;
            cin.ignore(); // prevents storing newline (empty line)
            getline(cin, chosenfPath); //reads chosen path (can include spaces)

            if (ds.loadFile(chosenfPath) or ds.loadFile(chosenfPath + ".txt") or ds.loadFile(chosenfPath + ".csv")){
                fileLoaded = true; // file loads successfully
                cout << "File loaded successfully! Data size: " << ds.getSize() << endl;
                hist = Histogram(ds.getData());
                hist.setBinNums(5); // defaulting to 5 bins
            }
            else{
                cout << "File was unable to be loaded." << endl;
            }
            break;
        
        case 2: // Statistics

            if (!fileLoaded){
                cout << "Please load a file first." << endl; // Won't run stats without dataset loaded
            }
            else{
                Statistics stats(ds.getData());
                displayStats(stats);
            }
            break;

        case 3: // Generate Histogram

            if (!fileLoaded){
                cout << "Please load a file first." << endl;
            }
            else{
                hist.genHist();
            }
            break;

        case 4: // Export Histogram

            if (!fileLoaded){
                cout << "Please load a file first." << endl;
            }
            else{
                hist.exportHist("histogram.csv");
                cout << "Histogram exported." << endl;
            }
            break;
            
        case 5: // Test Case
            ds.clearData();
            cout << "Running test case with tests/test.csv.." << endl;
            testCase(ds);
            ds.clearData();
            fileLoaded = false;
            cout << "Data cleared. Please load a new file for continued usage." << endl;
            break;

        case 6:  // New Bin Size
            if (!fileLoaded){
                cout << "Please load a file first." << endl;
            } else {
                string input;
                double newSize;
                bool isValid = true;

                cout << "Enter new bin size: ";
                cin >> input;

                // Check all characters are digits or a single decimal point
                int dotCount = 0;
                for (size_t i = 0; i < input.size(); i++){
                    if (input[i] == '.'){
                        dotCount++;
                        if (dotCount > 1){  // prevents accepting inputs with more than 1 '.'; keeps doubles but excludes strings
                            isValid = false; 
                            break; 
                        }
                    } else if (!isdigit(input[i])){
                        isValid = false;
                        break;
                    }
                }

                if (!isValid or input.empty()){
                    cout << "Invalid input. Please enter a positive number." << endl;
                } else {
                    newSize = stod(input); //string to double
                    hist.setBinSize(newSize);
                    cout << "Successful! New Bin Size: " << hist.getBinSize() << endl;
                }
            }
            break;

        case 7:  // New Number of Bins
            if (!fileLoaded){
                cout << "Please load a file first." << endl;
            } else {
                string input;
                bool isValid = true;

                cout << "Enter number of bins: ";
                cin >> input;

                for (size_t i = 0; i < input.size(); i++){
                    if (!isdigit(input[i])){
                        isValid = false;
                        break;
                    }
                }

                if (!isValid or input.empty()){
                    cout << "Invalid input. Please enter a whole number." << endl;
                } else {
                    size_t newBins = stoi(input); //string to integer
                    hist.setBinNums(newBins);
                    cout << "Successful! New number of bins: " << hist.getBinNums() << endl;
                }
            }
            break;
        
        case 8: // Exporting Lineplot
            if (!fileLoaded){
                cout << "Please load a file first." << endl;
            } else {
                hist.exportLinePlot("lineplot.csv");
                cout << "Line plot exported to images/lineplot.png" << endl;
            }
            break;
        
        case 9: // Exit Program
            cout << "Thank you for using the program." << endl;
            return 0;

        default:

            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}

   

    