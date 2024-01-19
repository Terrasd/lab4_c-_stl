#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <limits>

using namespace std;

struct Vector {
    int number;
    double x1, y1, x2, y2;
};

class VectorProcessor {
public:
    VectorProcessor() {}

    void readVectorsFromFile(const string& fileName) {
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "Error: Couldn't open input file." << endl;
            return;
        }

        Vector vec;
        char dummy;
        while (file >> vec.number >> dummy >> vec.x1 >> dummy >> vec.y1 >> dummy >> vec.x2 >> dummy >> vec.y2) {
            vectors.push_back(vec);
        }

        file.close();
    }

    double calculateVectorLength(const Vector& vec) const {
        return sqrt(pow((vec.x2 - vec.x1), 2) + pow((vec.y2 - vec.y1), 2));
    }

    // Метод для нахождения минимального и максимального векторов по длине
    pair<Vector, Vector> findMinMaxVectors() const {
        if (vectors.empty()) {
            return { Vector(), Vector() };
        }

        Vector minVector = vectors.front();
        Vector maxVector = vectors.front();

        for (const auto& vec : vectors) {
            if (calculateVectorLength(vec) < calculateVectorLength(minVector)) {
                minVector = vec;
            }

            if (calculateVectorLength(vec) > calculateVectorLength(maxVector)) {
                maxVector = vec;
            }
        }

        return { minVector, maxVector };
    }

    void printVectors() const {
        for (const auto& vec : vectors) {
            cout << "Vector " << vec.number << ": (" << vec.x1 << ", " << vec.y1 << ") to (" << vec.x2 << ", " << vec.y2 << "), Length: " << calculateVectorLength(vec) << endl;
        }
    }

    void writeResultsToFile(const string& fileName) const {
        auto minMaxVectors = findMinMaxVectors();

        ofstream file(fileName);
        if (!file.is_open()) {
            cerr << "Error: Couldn't open output file." << endl;
            return;
        }

        file << "Minimum vector: " << minMaxVectors.first.number << ", Length: " << calculateVectorLength(minMaxVectors.first) << endl;
        file << "Maximum vector: " << minMaxVectors.second.number << ", Length: " << calculateVectorLength(minMaxVectors.second) << endl;

        file.close();

        cout << "Results saved to " << fileName << endl;
    }

private:
    vector<Vector> vectors;
};

int main() {
    VectorProcessor vectorProcessor;
    vectorProcessor.readVectorsFromFile("vectors.txt");

    cout << "Vectors read from file:" << endl;
    vectorProcessor.printVectors();

    vectorProcessor.writeResultsToFile("output.txt");

    return 0;
}