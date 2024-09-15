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

vector<vector<int>> convolve(vector<vector<int>> A)
{
    // Gaussian filter
    vector<vector<int>> filter = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}};
    int n = A.size();

    for (int i = 0; i < n; i++)
    {
        A[i].insert(A[i].begin(), 0);
        A[i].insert(A[i].end(), 0);
    }
    vector<int> temp(n+2, 0);
    A.insert(A.begin(), temp);
    A.insert(A.end(), temp);

    vector<vector<int>> res(n * n, vector<int> (n,0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // res[i][j]

            // 00 01 02  x-1, y-1    x-1,y     x-1,y+1
            // 10 11 12  x,y-1      x, y       x, y+1
            // 20 21 22  x+1, y-1    x+1,y     x+1, y+1
            int sum = 0;
            sum += A[i - 1][j - 1]  * filter[0][0];
            sum += A[i - 1][j]      * filter[0][1];
            sum += A[i - 1][j + 1]  * filter[0][2];
            sum += A[i][j - 1]      * filter[1][0];
            sum += A[i][j]          * filter[1][1];
            sum += A[i][j + 1]      * filter[1][2];
            sum += A[i + 1][j - 1]  * filter[2][0];
            sum += A[i + 1][j]      * filter[2][1];
            sum += A[i + 1][j + 1]  * filter[2][2];
            sum = sum / 16;
            res[i - 1][j - 1] = (int)sum;
        }
    }
    return res;
}

void printMatrix(vector< vector<int> > matrix) {
	vector< vector<int> >::iterator it;
	vector<int>::iterator inner;
	for (it=matrix.begin(); it != matrix.end(); it++) {
		for (inner = it->begin(); inner != it->end(); inner++) {
			cout << *inner;
			if(inner+1 != it->end()) {
				cout << "\t";
			}
		}
		cout << endl;
	}
}

int main (int argc, char* argv[]) {
	srand(time(0));
	string filename;
	if (argc < 3) {
		filename = "2000.in";
	} else {
		filename = argv[2];
	}
	Result result = read (filename);
    parsec_roi_begin();
	vector< vector<int> > C = convolve(result.A);
    parsec_roi_end();
	//printMatrix(C);
	return 0;
}
