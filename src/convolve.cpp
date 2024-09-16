#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void parsec_roi_begin() 
{

}

void parsec_roi_end() 
{
	
}

struct Result {
	vector< vector<int> > A;
};

Result read(string filename) {
	vector< vector<int> > A;
	Result ab;
	string line;
	ifstream infile;
	infile.open (filename.c_str());

	int i = 0;
	while (getline(infile, line) && !line.empty()) {
		istringstream iss(line);
		A.resize(A.size() + 1);
		int a, j = 0;
		while (iss >> a) {
			A[i].push_back(a);
			j++;
		}
		i++;
	}
	infile.close();
	ab.A = A;
	return ab;
}

// Define the 3x3 Gaussian kernel with integer values
vector<vector<int>> gaussianKernel() {
    return {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };
}

vector<vector<int>> padMatrix(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> padded(rows + 2, vector<int>(cols + 2, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            padded[i + 1][j + 1] = matrix[i][j];
        }
    }
    return padded;
}

vector<vector<int>> convolve(const vector<vector<int>>& matrix) {
    vector<vector<int>> kernel = gaussianKernel();
    vector<vector<int>> padded = padMatrix(matrix);
    int rows = padded.size();
    int cols = padded[0].size();
    vector<vector<int>> result(matrix.size(), vector<int>(matrix[0].size(), 0));

    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            int sum = 0;
            for (int ki = -1; ki <= 1; ++ki) {
                for (int kj = -1; kj <= 1; ++kj) {
                    sum += padded[i + ki][j + kj] * kernel[ki + 1][kj + 1];
                }
            }
            result[i - 1][j - 1] = sum;
        }
    }
    return result;
}

int main (int argc, char* argv[]) {
    srand(time(0));
    string filename;
    if (argc < 3) {
        filename = "2000.in";
    } else {
        filename = argv[2];
    }
    Result result = read(filename);
    parsec_roi_begin();
    vector< vector<int> > C = convolve(result.A);
    parsec_roi_end();
    return 0;
}
