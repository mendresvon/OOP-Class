#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int choice;
	auto totalCount = 0; // letting auto figure out the type
	//int totalCount(0);
	//int totalCount{ 0 }; // using curly braces to start at zero

    vector<string> orderList;

    cout << "===== 歡迎來到 C++ 點餐系統 =====" << endl;

    // keep looping until they decide to stop
    while (true) {
        cout << "\n選單: 1.珍珠奶茶 2.綠茶 3.結束點餐" << endl;
        cout << "請輸入選擇: ";
        cin >> choice;

        // if they pick 3, we're done here
        if (choice == 3) break;

        // check what they chose
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
            continue; // skip the rest and try again
        }
    }

    // time to see what they ordered
    cout << "\n--- 訂單彙整 ---" << endl;
    if (orderList.empty()) {
        cout << "您沒有點任何東西。" << endl;
    }
    else {
        // go through the whole list and print each item
        for (const string& item : orderList) {
            cout << "- " << item << endl;
        }

        // quick check to see if they get a discount
        string discountMsg = (totalCount >= 5) ? "符合折扣資格！" : "未達折扣門檻。";
        cout << "\n總數: " << totalCount << " 杯，" << discountMsg << endl;
    }

    // say thanks a few times using a classic loop
    for (int i = 0; i < 3; i++) {
        cout << "謝謝惠顧! ";
    }
    cout << endl;


    return 0;
}