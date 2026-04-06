#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
#include <algorithm>


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
                dp[i][j]= std::max({value.at(A[i-1]) + dp[i-1][j-1], dp[i][j-1], dp[i-1][j]});
            }
            else {
                dp[i][j]= std::max(dp[i][j-1], dp[i-1][j]);
            }
        }
    }


    //backtracking


    if (dp[nA][nB]==0){
        ofstream outputFile;    //if max is 0 there is no solution
        outputFile.open("output.txt");
        outputFile << 0;
        outputFile.close();
        return dp[nA][nB];
    }


    vector<int> cols;
    int col = nA;
    int row = nB;
    string sol= ""; //get solution string
   
    while (col > 0 && row > 0){  //if not 0 then it must have come from diagonal.
        if (A[col-1]==B[row-1] && dp[col][row] == dp[col-1][row-1] + value.at(A[col-1])){
            sol = A[col-1] + sol;
            col = col-1;
            row = row-1;
        }
        else if (dp[col][row] == dp[col-1][row]){
            col=col-1;
        }
        else{
            row = row-1;
        }
    }


    ofstream outputFile;    //print solution to output file
    outputFile.open("output.txt");
    outputFile << dp[nA][nB]<<"\n";
    outputFile << sol;
    outputFile.close();


    return dp[nA][nB];
}

