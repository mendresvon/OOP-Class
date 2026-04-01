#include <iostream>
#include <algorithm>
using namespace std;

// --- Print 1D array ---
void printArray(int arr[], int size) {
    cout << "Array: [ ";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << " ]" << endl;
}

// --- Linear search: return index, -1 if not found ---
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++)
        if (arr[i] == target) return i;
    return -1;
}

// --- Binary search (array must be sorted): return index, -1 if not found ---
int binarySearch(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if      (arr[mid] == target) return mid;
        else if (arr[mid] <  target) low  = mid + 1;
        else                         high = mid - 1;
    }
    return -1;
}

// --- Sum ---
int sumArray(int arr[], int size) {
    int s = 0;
    for (int i = 0; i < size; i++) s += arr[i];
    return s;
}

// --- Average ---
double averageArray(int arr[], int size) {
    return (double)sumArray(arr, size) / size;
}

// --- Reverse in-place ---
void reverseArray(int arr[], int size) {
    for (int i = 0, j = size - 1; i < j; i++, j--)
        swap(arr[i], arr[j]);
}

// --- Insert element at position (arr must have enough capacity) ---
void insertAt(int arr[], int& size, int pos, int value) {
    for (int i = size; i > pos; i--)
        arr[i] = arr[i - 1];
    arr[pos] = value;
    size++;
}

// --- Delete element at position ---
void deleteAt(int arr[], int& size, int pos) {
    for (int i = pos; i < size - 1; i++)
        arr[i] = arr[i + 1];
    size--;
}

// --- Print 2D array (fixed 3 columns) ---
void print2DArray(int rows, int cols, int arr[][3]) {
    for (int i = 0; i < rows; i++) {
        cout << "  Row " << i << ": [ ";
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j];
            if (j < cols - 1) cout << ", ";
        }
        cout << " ]" << endl;
    }
}

// ============================================================
int main() {
    cout << "========================================" << endl;
    cout << "     C++ Array Operations Demo          " << endl;
    cout << "========================================" << endl;

    // --- 1. Basic statistics ---
    int arr[] = {64, 25, 12, 22, 11, 90, 45, 33};
    int size   = sizeof(arr) / sizeof(arr[0]);

    cout << "\n[1] Original array & statistics" << endl;
    printArray(arr, size);
    cout << "  Sum    : " << sumArray(arr, size)     << endl;
    cout << "  Average: " << averageArray(arr, size) << endl;
    cout << "  Max    : " << *max_element(arr, arr + size) << endl;
    cout << "  Min    : " << *min_element(arr, arr + size) << endl;

    // --- 2. Linear search ---
    cout << "\n[2] Linear search" << endl;
    int target = 22;
    int idx = linearSearch(arr, size, target);
    if (idx != -1)
        cout << "  Found " << target << " at index [" << idx << "]" << endl;
    else
        cout << "  " << target << " not found" << endl;

    // --- 3. Reverse ---
    cout << "\n[3] Reverse array" << endl;
    reverseArray(arr, size);
    printArray(arr, size);

    // --- 4. Sort ascending / descending ---
    cout << "\n[4] Sorting" << endl;
    sort(arr, arr + size);
    cout << "  Ascending : ";
    printArray(arr, size);

    sort(arr, arr + size, greater<int>());
    cout << "  Descending: ";
    printArray(arr, size);

    // --- 5. Binary search (requires sorted array) ---
    cout << "\n[5] Binary search (after ascending sort)" << endl;
    sort(arr, arr + size);
    printArray(arr, size);
    int bsTarget = 45;
    int bsIdx = binarySearch(arr, size, bsTarget);
    if (bsIdx != -1)
        cout << "  Binary search found " << bsTarget << " at index [" << bsIdx << "]" << endl;
    else
        cout << "  Binary search: " << bsTarget << " not found" << endl;

    // --- 6. Insert element ---
    cout << "\n[6] Insert element" << endl;
    int dynArr[20] = {10, 20, 30, 40, 50};
    int dynSize = 5;
    cout << "  Before insert: ";
    printArray(dynArr, dynSize);
    insertAt(dynArr, dynSize, 2, 99);
    cout << "  After insert 99 at index 2: ";
    printArray(dynArr, dynSize);

    // --- 7. Delete element ---
    cout << "\n[7] Delete element" << endl;
    deleteAt(dynArr, dynSize, 2);
    cout << "  After delete index 2: ";
    printArray(dynArr, dynSize);

    // --- 8. 2D array & matrix transpose ---
    cout << "\n[8] 2D array & transpose" << endl;
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    cout << "  Original matrix:" << endl;
    print2DArray(3, 3, matrix);

    int diagSum = 0;
    for (int i = 0; i < 3; i++) diagSum += matrix[i][i];
    cout << "  Main diagonal sum: " << diagSum << endl;

    for (int i = 0; i < 3; i++)
        for (int j = i + 1; j < 3; j++)
            swap(matrix[i][j], matrix[j][i]);
    cout << "  Transposed matrix:" << endl;
    print2DArray(3, 3, matrix);

    cout << "\n========================================" << endl;
    cout << "            Program End                 " << endl;
    cout << "========================================" << endl;
    return 0;
}
