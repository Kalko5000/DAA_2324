#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate a random integer within a specified range
int generateRandom(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Function to generate a TSP file
void generateTSPFile(string filename, int numNodes, int minDistance, int maxDistance) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to create file." << endl;
        return;
    }

    file << numNodes << endl;

    srand(time(0)); // Seed for random number generation

    // Generating distances between nodes (upper triangular matrix)
    for (char i = 'A'; i < 'A' + numNodes; ++i) {
        for (char j = i + 1; j < 'A' + numNodes; ++j) {
            int distance = generateRandom(minDistance, maxDistance);
            file << i << " " << j << " " << distance << endl;
        }
    }

    file.close();
    cout << "File '" << filename << "' generated successfully." << endl;
}

int main() {
  // Generate TSP files with specified parameters
  generateTSPFile("../grafos/3_nodos.txt", 3, 5, 50);
  return 0;
}