#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int levenshteinDistance(const string& s1, const string& s2) {
    const size_t m = s1.length();
    const size_t n = s2.length();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (size_t i = 1; i <= m; ++i) {
        dp[i][0] = i;
    }
    for (size_t j = 1; j <= n; ++j) {
        dp[0][j] = j;
    }
    
    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min({
                    dp[i - 1][j - 1] + 1,
                    dp[i][j - 1] + 1,
                    dp[i - 1][j] + 1
                });
            }
        }
    }
    
    return dp[m][n];
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    
    cout << levenshteinDistance(s1, s2) << endl;
    
    return 0;
}