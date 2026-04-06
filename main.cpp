#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


int main(){


    std::ifstream file("input.txt");
    std::string line;


    getline(file, line);    //getting first line, int k
    istringstream l1(line);
    int k;
    l1 >> k;


    std::map<char, int> value;
    for (int i=0; i< k; i++){   //for k lines, make map with {letter, value}
        getline(file, line);
        istringstream iss(line);


        char letter;
        int val;
        iss >> letter >> val;
        value.insert({letter, val});
    }


    std::string A;
    std::string B;


    getline(file, A);   //next 2 lines are strings A and B
    getline(file, B);


    file.close();




    int nA = A.size();
    int nB = B.size();


    std::vector<std::vector<int>> dp(A.size() + 1, std::vector<int>(B.size() + 1));


    for (int j = 0; j < B.size()+1;j++){
        dp[0][j]=0;
    }
    for (int i = 0; i < A.size()+1;i++){
        dp[i][0]=0;
    }


    for (int i = 1; i < A.size()+1; i++){
        for (int j = 1; j < B.size()+1; j++){
            if (A[i-1]==B[j-1]){
                dp[i][j] = value.at(A[i-1]) + std::max(dp[i-1][j-1], dp[i][j-1]);
            }
            else {
                dp[i][j]=dp[i][j-1];
            }
        }
    }


    //get largest val in top line
    int max = 0;
    for (int i = 0; i< nA; i++){
        if (dp[i][nB] > max){
            max = dp[i][nB];
        }
    }


    //backtracking


    if (max==0){
        ofstream outputFile;    //if max is 0 there is no solution
        outputFile.open("output.txt");
        outputFile << 0;
        outputFile.close();
        return dp[nA][nB];
    }


    vector<int> cols;
    int col = nA;
    int row = nB;
    int col_start;


    while (col != 0){
        if (dp[col][row] == 0){
            col = col-1;
        }
    }
    col_start=col;
    cols.push_back(col_start);
   




    ofstream outputFile;    //print solution to output file
    outputFile.open("output.txt");
    outputFile << dp[nA][nB];
    outputFile.close();
    cout<<max<<endl;
    return dp[nA][nB];
}

