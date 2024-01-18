#include "kNN.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

// Constructor implementation
KNN::KNN(int neighbors, double threshold) : k(neighbors), split_threshold(threshold) {
}

// Train function implementation
void KNN::train(Dataset& data) {
    // standardize the data
    // build the KD_Tree

    std::vector<double> sum_all_vector(data.points[0].features.size(), 0);

    for (const auto& vec : data.points) {
        for (int i = 0; i < vec.features.size(); ++i) {
            sum_all_vector[i] += vec.features[i];
        }
    }

    std::vector<double> mean_values(sum_all_vector.size(), 0);

    // Print the means for each feature
    for (int i = 0; i < sum_all_vector.size(); ++i) {
        mean_values[i] = sum_all_vector[i] / data.points.size();
        std::cout << "Mean for Feature " << i + 1 << ": " << mean_values[i] << std::endl;
    }
    std::vector<double> variance(mean_values.size(), 0);
    std::vector<double> standard_deviation(mean_values.size(), 0);

    // Calculate standard deviation
    for (int i = 0; i < mean_values.size(); ++i) {
        for (const auto& vec : data.points) {
            variance[i] += (pow(vec.features[i] - mean_values[i], 2))/ data.points.size();
        }

        standard_deviation[i] = sqrt(variance[i] );
        std::cout << "Standard Deviation for Feature " << i + 1 << ": " << standard_deviation[i] << std::endl;
    }


    // Standardize features
    for (auto& vec : data.points) {
        for (int i = 0; i < vec.features.size(); ++i) {
            vec.features[i] = (vec.features[i] - mean_values[i]) / standard_deviation[i];
        }
    }
    int feature_number;
    split_threshold = maxVariance(variance, feature_number);
    cout<<"max variance: "<<to_string(split_threshold)<<endl;


}

// Predict function implementation
int KNN::predict(const Point& queryPoint) {
    // returns if the given queryPoint is habitable (1) or not (0)
}

// Additional methods or helper functions can be added as needed

double KNN::maxVariance (vector<double> &variances, int& feature_number) {
    double maxVariance = std::numeric_limits<double>::lowest(); // Initialize to a very small value
    for (int i = 0; i < variances.size(); ++i) {
        if (maxVariance < variances[i]) {
            maxVariance = variances[i];
            feature_number = i;
        }
    } return maxVariance;
}