#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>
#include <string>

using namespace std;
using namespace std::chrono;

const int SO_PHAN_TU = 1000000;

void heapify(vector<double>& a, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
        largest = left;
    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

//Thuật toán HeapSort
void heapSort(vector<double>& a) {
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

// Hàm sinh bộ dữ liệu thử nghiệm
vector<vector<double>> taoBoDuLieu() {
    vector<vector<double>> datasets(10, vector<double>(SO_PHAN_TU));
    mt19937_64 rng(1337);
    uniform_real_distribution<double> dist(-1e6, 1e6);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < SO_PHAN_TU; j++) {
            datasets[i][j] = dist(rng);
        }
    }
    sort(datasets[0].begin(), datasets[0].end());
    sort(datasets[1].begin(), datasets[1].end(), greater<double>());
    return datasets;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "Dang khoi tao bo du lieu 10 day (1.000.000 phan tu/day)...\n";
    vector<vector<double>> datasets = taoBoDuLieu();

    string tenDay[10] = {
        "Day 1 (Tang dan)", "Day 2 (Giam dan)", "Day 3 (Ngau nhien)",
        "Day 4 (Ngau nhien)", "Day 5 (Ngau nhien)", "Day 6 (Ngau nhien)",
        "Day 7 (Ngau nhien)", "Day 8 (Ngau nhien)", "Day 9 (Ngau nhien)", "Day 10 (Ngau nhien)"
    };

    cout << left << setw(22) << "Ten Day" << setw(20) << "HeapSort (ms)" << "\n";
    cout << string(42, '-') << "\n";

    double tongThoiGianNgauNhien = 0;

    for (int i = 0; i < 10; i++) {
        vector<double> temp = datasets[i];

        auto start = high_resolution_clock::now();
        heapSort(temp);
        auto end = high_resolution_clock::now();

        double thoiGian = duration<double, milli>(end - start).count();
        if (i >= 2) tongThoiGianNgauNhien += thoiGian;

        cout << left << setw(22) << tenDay[i]
            << fixed << setprecision(2) << setw(20) << thoiGian << "\n";
    }

    cout << string(42, '-') << "\n";
    cout << left << setw(22) << "Trung binh (3-10)"
        << fixed << setprecision(2) << setw(20) << (tongThoiGianNgauNhien / 8.0) << "\n";

    return 0;
}