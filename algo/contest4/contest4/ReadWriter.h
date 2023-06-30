#include <iostream>
#include <random>
#include <functional>
#include <chrono>
#include <algorithm>
#include <iterator>
#include <fstream>

std::mt19937 mt(1729);
std::fstream fin;
std::fstream fout;

union U {
    unsigned int a; // occupies 4 bytes
    unsigned char b[4]; // occupies 4 bytes
};

//Соединяет два отсортированных подмассива
void merge(int* arr, int left, int mid, int right) {
    int leftArr[mid - left + 1];
    int rightArr[right - mid];

    for (int i = 0; i < mid - left + 1; i++) {
        leftArr[i] = arr[left + i];
    }

    for (int j = 0; j < right - mid; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = 0;

    while (i < mid - left + 1 && j < right - mid) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        }
        else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < mid - left + 1) {
        arr[k++] = leftArr[i++];
    }

    while (j < right - mid) {
        arr[k++] = rightArr[j++];
    }
}

void recursiveMergeSort(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        recursiveMergeSort(arr, left, mid);
        recursiveMergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

//Сортировка слиянием
void mergeSort(int* arr, int size) {
    return recursiveMergeSort(arr, 0, size - 1);
}

//Сортировка выбором
void selectionSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;

        for (int j = i + 1; j < size; j++)
            if (arr[j] < arr[min_index])
                min_index = j;

        if (min_index != i) {
            std::swap(arr[i], arr[min_index]);
        }
    }
}

//Сортировка пузырьком
int bubbleSort(int* arr, int size) {
    int i = 0;
    int count = 0;

    while (i < size - 1) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                count++;
            }
        }

        i++;
    }

    return count;
}

//Сортировка пузырьком с условием Айверсона 1
int bubbleSortWithCondition(int* arr, int size) {
    bool sorted = false;
    int i = 0;
    int count = 0;

    while (i < size - 1 && !sorted) {
        //если не сделано ни одной перестановки, то массив отсортирован
        sorted = true;

        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                count++;
                sorted = false;
            }
        }

        i++;
    }

    return count;
}

//Сортировка подсчётом, переделанная под union
void radixCountingSort(int* numbers, int size, int i) {
    int max = 0;
    U* A = new U[size];

    for (int j = 0; j < size; j++) {
        A[j].a = numbers[j];

        if (A[j].b[i] > max)
            max = A[j].b[i];
    }

    int k = max + 1;

    //Вспомогательный массив
    int* C = new int[k];

    for (int j = 0; j < k; j++)
        C[j] = 0;

    for (int j = 0; j < size; j++)
        C[A[j].b[i]]++;

    for (int j = 1; j < k; j++)
        C[j] += C[j - 1];

    for (int j = size - 1; j >= 0; j--) {
        numbers[C[A[j].b[i]] - 1] = A[j].a;
        C[A[j].b[i]]--;
    }

    delete[] A;
    delete[] C;
}

//Цифровая сортировка
void radixSort(int* numbers, int size) {
    for (int i = 0; i < 3; i++)
        radixCountingSort(numbers, size, i);
}

//Сортировка подсчётом
void countingSort(int* numbers, int size) {
    int max = numbers[0];
    int* B = new int[size];

    for (int i = 0; i < size; i++)
        if (numbers[i] > max)
            max = numbers[i];

    int k = max + 1;

    //Вспомогательный массив
    int* C = new int[k];

    for (int i = 0; i < k; i++)
        C[i] = 0;

    for (int i = 0; i < size; i++)
        C[numbers[i]]++;

    for (int i = 1; i < k; i++)
        C[i] += C[i - 1];

    for (int i = size - 1; i >= 0; i--) {
        B[C[numbers[i]] - 1] = numbers[i];
        C[numbers[i]]--;
    }

    for (int i = 0; i < size; i++)
        numbers[i] = B[i];

    delete[] B;
    delete[] C;
}

void heapify(int* arr, int heapSize, int i) {
    int largest = i;

    if (2 * i + 1 < heapSize && arr[2 * i + 1] > arr[i])
        largest = 2 * i + 1;

    if (2 * i + 2 < heapSize && arr[2 * i + 2] > arr[largest])
        largest = 2 * i + 2;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, heapSize, largest);
    }
}

void buildHeap(int* arr, int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);
}

//Пирамидальная сортировка
void heapSort(int* arr, int size) {
    buildHeap(arr, size);

    for (int i = size - 1; i >= 1; i--) {
        std::swap(arr[0], arr[i]);
        size--;
        heapify(arr, size, 0);
    }
}

void recursiveQuickSort(int* arr, int size, int left, int right) {
    int i = left;
    int j = right;
    int pivot = arr[(i + j) / 2];

    while (i <= j) {
        while (arr[i] < pivot)
            i++;

        while (arr[j] > pivot)
            j--;

        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (j > left)
        recursiveQuickSort(arr, size, left, j);

    if (i < right)
        recursiveQuickSort(arr, size, i, right);
}

//Быстрая сортировка
void quickSort(int* arr, int size) {
    return recursiveQuickSort(arr, size, 0, size - 1);
}

//Generates arrays with 4100 elements
void fillArrayWithRandomNumbers(int* arr, int len, int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);

    for (int i = 0; i < len; i++) {
        int num = dist(mt);
        arr[i] = num;
    }
}

void fillAlmostSortedArray(int* arr, int size) {
    std::uniform_int_distribution<int> dist(0, 5);
    arr[0] = dist(mt);

    for (int i = 1; i < size; i++) {
        arr[i] = arr[i - 1] + dist(mt);
    }

    std::uniform_int_distribution<int> indexDist(0, size);

    do {
        std::swap(arr[indexDist(mt)], arr[indexDist(mt)]);
        size -= 1000;
    } while (size > 0);
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;
}

void fillReferenceArray(int* arr, int i) {
    switch (i) {
    case 0:
        fillArrayWithRandomNumbers(arr, 4100, 0, 5);
        break;
    case 1:
        fillArrayWithRandomNumbers(arr, 4100, 0, 4000);
        break;
    case 2:
        fillAlmostSortedArray(arr, 4100);
        break;
    case 3:
        for (int j = 1; j <= 4100; j++) {
            arr[4100 - j] = j;
        }
        break;
    default:
        break;
    }
}

long long getAverageTime(std::function<void(int*, int)>& func, int* arr, int size) {
    long long sum = 0;
    int copy[size];

    //printArray(arr, size);

    for (int i = 0; i < 12; i++) {
        std::copy(arr, arr + size, copy);

        if (i < 2) {
            func(copy, size);
            continue;
        }

        auto start = std::chrono::high_resolution_clock::now();
        func(copy, size);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;

        sum += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    }

    //printArray(copy, size);

    std::cout << sum << std::endl;

    return sum / 10;
}

void compare(std::vector<std::function<void(int*, int)>>& funcs) {
    for (int i = 0; i < 4; i++) {
        int arr[4100];
        fillReferenceArray(arr, i);

        for (auto& func : funcs) {
            for (int j = 50; j <= 300; j += 50) {
                //fout << j << ";";
                //std::cout << "size: " << j << std::endl;
                auto average = getAverageTime(func, arr, j);
                //std::cout << "time elapsed: " << average << std::endl << std::endl;
                fout << average << ";";
            }

            for (int j = 1100; j <= 4100; j += 1000) {
                //std::cout << "size: " << j << std::endl;
                auto average = getAverageTime(func, arr, j);
                //std::cout << "time elapsed: " << average << std::endl << std::endl;
                fout << average << ";";
            }

            fout << std::endl;
        }
    }
}

int main() {
    fout.open("Measurements.csv", std::fstream::out);

    std::vector<std::function<void(int*, int)>> funcs = {
            selectionSort, bubbleSort, bubbleSortWithCondition, countingSort,
            radixSort, quickSort, heapSort, mergeSort
    };

    if (fout.is_open()) {
        compare(funcs);
        fout.close();
    }
    else {
        std::cout << "Cannot open file." << std::endl;
        return -1;
    }
}
