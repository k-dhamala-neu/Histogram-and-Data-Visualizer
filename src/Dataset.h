#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <string>


struct DataPoint { // Works like a class but all data members are public by default
    // Using to arrange data in the vector as (x,y) instead of individual values; Ex. Data = {(x1,y1), (x2,y2), (x3,y3), ...}
    double x; // Used to define x variable in dataset
    double y; // Used to define y variable in dataset
};

class Dataset {
    private:
        std::vector<DataPoint> data; // Stores all numeric values
        std::string filePath; // Path of loaded input file
        int dataSize; // Count of valid values stored

    public:
        Dataset();
        ~Dataset(); 

        // Functions
        bool loadFile(const std::string& fPath); // Opens file and reads values into data by referencing the existing file path
        const std::vector<DataPoint>& getData() const; // Returns the full dataset by referencing the existing dataset
        int getSize() const; // Returns number of valid values
        void clearData(); // Resets and empties the dataset

};


#endif 