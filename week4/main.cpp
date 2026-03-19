#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int choice;
	auto totalCount = 0; // 使用 auto 推導類型
    //int totalCount(0);
	//int totalCount{ 0 }; // 使用大括號初始化

    vector<string> orderList;

    cout << "===== 歡迎來到 C++ 點餐系統 =====" << endl;

    // 使用 while 迴圈：持續詢問直到使用者選擇結束
    while (true) {
        cout << "\n選單: 1.珍珠奶茶 2.綠茶 3.結束點餐" << endl;
        cout << "請輸入選擇: ";
        cin >> choice;

        // 1. 使用 break 跳出迴圈
        if (choice == 3) break;

        // 2. 使用 switch 處理多個分支
        switch (choice) {
        case 1:
            orderList.push_back("珍珠奶茶");
            totalCount++;
            break;
        case 2:
            orderList.push_back("綠茶");
            totalCount++;
            break;
        default:
            cout << "無效選擇，請重新輸入。" << endl;
            continue; // 跳過本次迴圈剩餘部分
        }
    }

    // 3. 使用 if-else 處理邏輯
    cout << "\n--- 訂單彙整 ---" << endl;
    if (orderList.empty()) {
        cout << "您沒有點任何東西。" << endl;
    }
    else {
        // 使用範圍 for 迴圈 (Range-based for) 遍歷容器
        for (const string& item : orderList) {
            cout << "- " << item << endl;
        }

        // 使用三元運算子 (Week 4)
        string discountMsg = (totalCount >= 5) ? "符合折扣資格！" : "未達折扣門檻。";
        cout << "\n總數: " << totalCount << " 杯，" << discountMsg << endl;
    }

    // 4. 使用傳統 for 迴圈印出感謝語
    for (int i = 0; i < 3; i++) {
        cout << "謝謝惠顧! ";
    }
    cout << endl;


    return 0;
}