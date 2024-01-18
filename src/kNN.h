// kNN.h
#ifndef KNN_H
#define KNN_H

#include "KD_Tree.h"
#include "kNN_Data.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


class KNN {

private:


public:
    KD_Tree tree;
    int k; // Number of neighbors for kNN
    double split_threshold; // Threshold for the kd_tree

    KNN(int k, double threshold);
    void train(Dataset& data); // Need to initialize the tree here 
    int predict(const Point& queryPoint);

    double maxVariance(std::vector<double> &variances, int& feature_number);
};

#endif // KNN_H