#include <iostream>
#include <string>
#include <map>
#include <vector>

int main(){
    int k = 3;
    std::string A = "aaacb";
    std::string B = "caab";

    int nA = A.size();
    int nB = B.size();
    
    std::map<char, int> value;
    value.insert({'a', 2});
    value.insert({'b', 4});
    value.insert({'c', 5});

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

    std::cout<<dp[nA][nB]<<std::endl;
    return dp[nA][nB];
}