#include <iostream>
#include <string>

using namespace std;

// 1. 使用指標 (Call by Address)
// 優點：可以傳入 nullptr，邏輯較彈性
// 缺點：語法較繁瑣，需要用 * 取值
void swapByPointer(int* a, int* b) {
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    if (a == nullptr || b == nullptr) return; // 安全檢查
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 2. 使用參考 (Call by Reference)
// 優點：語法簡潔，像一般變數一樣使用，且保證不為空（安全）
// 建議：C++ 開發優先使用此方式
void swapByReference(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 10;
    int y = 20;

    cout << "x = " << x << ", y = " << y << endl;
    cout << "&x = " << &x << endl;
    cout << "&y = " << &y << endl;

    // --- 使用指標交換 ---
    // 必須使用 & 取出 x 和 y 的地址傳進去
    swapByPointer(&x, &y);
    cout << "指標交換後: x = " << x << ", y = " << y << endl;

    // --- 使用參考交換 ---
    // 直接傳入變數名稱即可，語法最自然
    swapByReference(x, y);
    cout << "參考交換後 (換回來): x = " << x << ", y = " << y << endl;

    return 0;
}