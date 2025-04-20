#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
#include <windows.h>

using namespace std;

int levenshteinDistanceWithDoubleInsert(const string& s1, const string& s2) {
    const int replace_cost = 1;
    const int insert_cost = 1;
    const int delete_cost = 1;
    const int double_insert_cost = 1;
    
    const size_t m = s1.length();
    const size_t n = s2.length();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (size_t i = 1; i <= m; ++i) {
        dp[i][0] = dp[i - 1][0] + delete_cost;
    }
    for (size_t j = 1; j <= n; ++j) {
        // проверка на пустую строку
        if (j >= 2) {
            dp[0][j] = min(dp[0][j - 1] + insert_cost,
                          dp[0][j - 2] + double_insert_cost);
        } else {
            dp[0][j] = dp[0][j - 1] + insert_cost;
        }
    }
    
    // визуализацию не завезли(
    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                int cost = min({
                    dp[i - 1][j - 1] + replace_cost,
                    dp[i][j - 1] + insert_cost,
                    dp[i - 1][j] + delete_cost
                });
                
                // Проверка возможности двойной вставки
                if (j >= 2 && s2[j - 1] == s2[j - 2]) {
                    cost = min(cost, dp[i][j - 2] + double_insert_cost);
                }
                
                dp[i][j] = cost;
            }
        }
    }
    
    return dp[m][n];
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string s1, s2;
    cout << "Первая строка: ";
    getline(cin, s1);
    cout << "Вторая строка: ";
    getline(cin, s2);
    
    int distance = levenshteinDistanceWithDoubleInsert(s1, s2);
    
    cout << "Расстояние: " << distance << endl;
    
    return 0;
}