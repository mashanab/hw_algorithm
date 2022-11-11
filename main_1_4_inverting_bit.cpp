#include <iostream>

using namespace std;

int main() {
    int n;
    int k;
    cin >> n >> k;
    n = n ^ (1 << k);
    cout << n << endl;
    return 0;
}