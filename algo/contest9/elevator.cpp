#include <iostream>
#include <vector>

using namespace std;

int findNumberOfDifferentFloors(int n, int a, int b, int c) {
    vector<bool> floors(n + 1, false);
    int count = 0;

    floors[1] = true;

    for (int i = 1; i < n + 1; i++) {
        if (floors[i]) {
            if (i + a < n + 1)
                floors[i + a] = true;

            if (i + b < n + 1)
                floors[i + b] = true;

            if (i + c < n + 1)
                floors[i + c] = true;

            count++;
        }
    }

    return count;
}

int main() {
    int n;
    int a, b, c;

    cin >> n >> a >> b >> c;

    cout << findNumberOfDifferentFloors(n, a, b, c);

    return 0;
}