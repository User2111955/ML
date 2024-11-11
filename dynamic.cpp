#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int knapsack(int W, const vector<int>& wt, const vector<int>& val, int n) {
    // Create a 2D dp array initialized to 0
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Build the dp matrix
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (wt[i - 1] <= w) {
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Display dp matrix
    cout << "DP Matrix:" << endl;
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            cout << dp[i][w] << " ";
        }
        cout << endl;
    }

    // Trace back to find the selected items
    vector<int> selectedItems;
    int w = W;
    for (int i = n; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) { // Item i was included
            selectedItems.push_back(i - 1); // Store index of the selected item
            w -= wt[i - 1]; // Reduce the weight
        }
    }

    // Display selected items
    cout << "Selected items (in reverse order of selection):" << endl;
    cout << "Item\tWeight\tValue" << endl;
    for (int i = selectedItems.size() - 1; i >= 0; i--) {
        int item = selectedItems[i];
        cout << item + 1 << "\t" << wt[item] << "\t" << val[item] << endl;
    }

    return dp[n][W];
}

int main() {
    int n, W;
    
    cout << "Enter the number of objects: ";
    cin >> n;

    vector<int> val(n), wt(n);  // Define val and wt vectors of size n

    for (int i = 0; i < n; i++) {
        cout << "Enter value of object " << i + 1 << ": ";
        cin >> val[i];
    }

    for (int i = 0; i < n; i++) {
        cout << "Enter weight of object " << i + 1 << ": ";
        cin >> wt[i];
    }

    cout << "Enter the capacity of knapsack: ";
    cin >> W;

    int maxProfit = knapsack(W, wt, val, n);
    cout << "Maximum Profit is: " << maxProfit << endl;

    return 0;
}
