// Compile: make 
// Execute: ./perceptron.out setosa_v_versicolor.csv
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

int Sign(int x)
{
    int y;
    if(x >= 0)
    {
        y = 1;
    }
    if(x < 0)
    {
        y = -1;
    }
    return y;
}

int main(int argc, char *argv[]) 
{
    vector< vector<double> > data;    
    ifstream file( argv[1] );         

    string line;
    while(getline(file, line)) {
        vector<double> row;
        stringstream iss(line);

        string val;
        while (getline(iss, val, ',')) 
        {
            try {
                double temp = stod(val);
                row.push_back(temp);
            }
            catch (...) {
                cout << "Bad input: " << val << endl;
            }
        }
        data.push_back(row);
    }
    
    // vector< vector<double> > w;
    // Randomly initialize vector w and theta [-1,1]
    double theta; 
    vector<double> w (4);
    theta = ((double) rand() / (RAND_MAX)) * 2 - 1;
    
    for(int i =0; i<4; i++)
    {
        w[i] = (((double) rand() / (RAND_MAX)) * 2 - 1);
    }

    double yd[100];
    double weight[4];
    double X, e, Y;
    double alpha = 0.05;
    double correct, incorrect, total = 0;
    int iter = 1;
   
    for (const auto &row : data) 
    {
        //  0 - Sepal length
        //  1 - Sepal width
        //  2 - Petal length
        //  3 - Petal width
        //  4 - Label
        double label = row.back();
        //std::cout << " Data values: ";
        for (const auto &col : row )
            //std::cout << col << '\t';
        
        //std::cout << std::endl;
        //std::cout << label;

        for(int i = 0; i<100; i++)
        {
                yd[i] = label;
        }
            
        for(int i = 0; i<100; i++)
        {
                X = 0;
                X = w[0]*row[0] + w[1]*row[1] + w[2]*row[2] + w[3]*row[3] - theta;
                Y = Sign(X);
                e = yd[i] - Y;
                for(int j = 0; j<4; j++)
                {
                    weight[j] = w[j] + alpha*row[j]*e;
                }
                theta = theta + alpha*(-1)*e;
        }

        cout << "Iteration " << iter << ": Weights are [" << weight[0] << ", " << weight[1] << ", " 
            << weight[2] << ", " << weight[3] << "], ";
        
        cout << "classification ";
        if(e == 0) { 
            cout << "was CORRECT!" << endl;  
            correct = correct + 1; 
        } 
        else if(e != 0) 
        { 
            cout << "was an ERROR!" << endl; 
            incorrect = incorrect + 1; 
        }
        iter = iter + 1;


        /* ==========  FOR DEBUGGING  ========= */
        //cout << "X: " << X << " = (" <<  w[0] << "*" << row[0] << ") + (" << w[1] << "*" << row[1] 
        //     << ") + (" << w[2] << "*" << row[2] << ") + (" <<  w[3] << "*" << row[3] << ") - " << theta << endl;
        //cout << "Y = " << Y << endl; 
        //cout << "e = " << e << endl;
        //cout << "updated weight: " << weight << " = " << w[0] << " + " << alpha <<
        //    "*" << row[0] << "*" << e << endl;
    }   
    cout << endl;
    cout << "correct: " << correct << endl;
    cout << "errors: " << incorrect << endl;
    total = correct/(correct+incorrect);
    cout << total*100 << "% = " << correct << "/(" << correct << " + " << incorrect << ")" << endl;

}
