#include <iostream>

using namespace std;

long long getMinCost(int numberOfRooms, int *a, int *b, int index) {
    long long price = a[index];

    for (int i = 0; i < index; i++) {
        price += min(b[i], a[i]);
    }

    for (int i = index + 1; i < numberOfRooms; i++) {
        price += min(b[i - 1], a[i]);
    }

    return price;
}

int main() {
    int numberOfRooms;
    cin >> numberOfRooms;

    int *a = new int[numberOfRooms];
    int *b = new int[numberOfRooms - 1];

    for (int i = 0; i < numberOfRooms; i++)
        cin >> a[i];

    for (int i = 0; i < numberOfRooms - 1; i++)
        cin >> b[i];

    long long res = min(getMinCost(numberOfRooms, a, b, 0), getMinCost(numberOfRooms, a, b, numberOfRooms - 1));

    cout << res;

    return 0;
}