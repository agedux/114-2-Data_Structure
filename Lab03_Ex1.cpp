#include <vector>
using namespace std;

class Solution {
public:
    int findLucky(vector<int>& arr) {
        int count[501] = {0}; // 計數陣列 stepCount +2

        // 統計陣列裡每個數字出現的次數
        for (int num : arr) {
            count[num]++; // stepCount+2
        }

        // 從陣列後面開始檢查，第一找到的必為最大(省去找所有符合數字中最大的)
        // stepCount +1
        for (int i = 500; i > 0; i--) {
            // stepCount +1

            // 判斷整數值是否等於i(出現次數)
            // stepCount +2
            if (count[i] == i) {
                return count[i]; //回傳 stepCount +1
            }
            // stepCount +1
        }
        // stepCount +1

        // stepCount +1
        return -1; // 都沒有就回傳-1
    }
};

/*
Total operations:
2 + 2 * n + 1 + 4*500 + 2 = 2n + 2005
*/