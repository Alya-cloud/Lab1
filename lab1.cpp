#include <iostream>
#include <vector>
#include <chrono>
#include <numeric> 
#include <algorithm>
#include <random>

// Quick sort with randomized pivot selection
template<typename T>
int partition(std::vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

template<typename T>
void quicksort(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

template<typename T>
void quickSort(std::vector<T>& arr) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(arr.begin(), arr.end(), gen);
    quicksort(arr, 0, arr.size() - 1);
}

// Merge sort
template<typename T>
void merge(std::vector<T>& arr, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    std::vector<T> left(n1), right(n2);

    for (int i = 0; i < n1; ++i)
        left[i] = arr[low + i];
    for (int j = 0; j < n2; ++j)
        right[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            ++i;
        }
        else {
            arr[k] = right[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = left[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = right[j];
        ++j;
        ++k;
    }
}

template<typename T>
void mergeSort(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

// Counting sort
template<typename T>
void countingSort(std::vector<T>& arr) {
    T max = *std::max_element(arr.begin(), arr.end());
    std::vector<int> count(max + 1, 0);
    std::vector<T> output(arr.size());

    for (T elem : arr) {
        ++count[elem];
    }

    for (int i = 1; i <= max; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = arr.size() - 1; i >= 0; --i) {
        output[count[arr[i]] - 1] = arr[i];
        --count[arr[i]];
    }

    arr = output;
}

int main() {
    std::vector<int> sizes = { 10, 1000, 1000000 }; 
    for (int size : sizes) {
        std::vector<int> arr(size);
        std::iota(arr.begin(), arr.end(), 0); // Filling the array with consecutive integers

        // Measure time for Quick sort
        auto start = std::chrono::high_resolution_clock::now();
        quickSort(arr);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> quickSortTime = end - start;

        std::shuffle(arr.begin(), arr.end(), std::mt19937(std::random_device()()));

        // Measure time for Merge sort
        start = std::chrono::high_resolution_clock::now();
        mergeSort(arr, 0, arr.size() - 1);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> mergeSortTime = end - start;

        std::shuffle(arr.begin(), arr.end(), std::mt19937(std::random_device()()));

        // Measure time for Counting sort
        start = std::chrono::high_resolution_clock::now();
        countingSort(arr);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> countingSortTime = end - start;

        std::cout << "Array size: " << size << std::endl;
        std::cout << "Quick sort time: " << quickSortTime.count() << " seconds" << std::endl;
        std::cout << "Merge sort time: " << mergeSortTime.count() << " seconds" << std::endl;
        std::cout << "Counting sort time: " << countingSortTime.count() << " seconds" << std::endl;
        std::cout << std::endl;
    }
    return 0;
}