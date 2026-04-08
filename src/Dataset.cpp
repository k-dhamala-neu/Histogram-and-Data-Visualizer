#include "Dataset.h" 
#include <fstream> 
#include <sstream> 
#include <iostream>
using namespace std;



Dataset::Dataset() : filePath(""), dataSize(0) {} // Constructor defaults each Dataset to no path and 0 size

Dataset::~Dataset() {} // Destructor

bool Dataset::loadFile(const std::string& fPath) {
    filePath = fPath;
    
    std::ifstream file(fPath); // Opens file at given path and reads only

    if (!file.is_open()) { // Checks if file successfully opened; if not shows an error message
        cerr << "Error: Could not open file " << fPath << endl;
        return false; // Exits out of function and shows loading the file failed
    }

    // Checks file extension to determine delimiter
    // Delimiter is a parameter in file I/O that means to stop reading/writing at this certain point

    // find_last_of('.') finds the last '.' in the path, substr grabs everything from that point; essentially grabs the file type to store the data accordingly

    char delimiter; // Stops reading data at a given point so if the line is 3.3,2.2; delimiter is ',' and the line is read as 3.3 and next line is 2.2

    bool isCSV = fPath.substr(fPath.find_last_of('.')) == ".csv"; // True if csv file
    bool isTXT = fPath.substr(fPath.find_last_of('.')) == ".txt"; // True if txt file

    if (isCSV) {
        delimiter = ','; // csv files are comma separated; 3.3,2.2
    } else if (isTXT) {
        delimiter = ' '; // txt files are space separated; 3.3 2.2
    } else {
        cerr << "Error: Unsupported file type" << endl;
        return false; // Returns false if file type is not supported
    }

    string line;
    getline(file, line); // Only reads the first line (Column Headers) and doesnt store it
    //if first line is 'Time (t)', 'Distance (m)' then those lines wont get stored in the data vector; ensures only datapoints in the vector

    bool extraDataMsg = false; // If there is more data than just x,y

    while (getline(file, line)) { // Reads file one line at a time until end of file
        
        stringstream fullLine(line); // Treats the current line as a string and reads from it
        string xVal, yVal;     // Strings to store the two values from the line

        getline(fullLine, xVal, delimiter); // Reads the full line until delimiter, stores in xVal
        getline(fullLine, yVal, delimiter); // Continues reading the line after the delimiter, stores remainder in yVal then moves to next line

        // After reading xVal and yVal check if more data exists
        string remaining;
        getline(fullLine, remaining, '\n');
        if (!remaining.empty() and extraDataMsg == false){
            cerr << "Warning: Extra columns detected, only x and y values will be used." << endl;
            extraDataMsg = true; // only print once, not for every row
        }


        // Remove trailing \r if present (Windows line endings)
        if (!yVal.empty() && yVal.back() == '\r'){
        yVal.pop_back();

        }

        try {
            DataPoint point;
            point.x = stod(xVal);
            point.y = stod(yVal);
            data.push_back(point);
            dataSize++;
        } catch (const out_of_range& e) {
            cerr << "Warning: Value out of range at line " << dataSize + 1 << ", skipping." << endl;
        } catch (const invalid_argument& e) {
            cerr << "Warning: Incomplete or invalid data at line " << dataSize + 1 << ", skipping." << endl;
        }
        
    }

    file.close(); // Closes the file after reading

    if (dataSize == 0){
        cerr << "File has no data." << endl;
        return false;
    }

    return true;  // Returns true to signal success
}

const vector<DataPoint>& Dataset::getData() const { //Returns a reference to the dataset
    //first const means the returned data cant be modified, second const means the method cant modify the dataset object itself
    return data; // Can simply return data since it has vector properties
}

int Dataset::getSize() const { //Returns the amount of data points
    return dataSize;
}

void Dataset::clearData() { //clears data and resets data members to inital constructor defaults
    data.clear();
    dataSize = 0;
    filePath = "";
}

