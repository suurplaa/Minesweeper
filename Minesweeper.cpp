#include <iostream>
#include <random>
using namespace std;
void game();

int Random(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

void showb(int n, char b[50][50]) {
    cout << " " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << b[i][j] << " ";
        }
        cout << endl;
    }
}

void showa(int n, int a[50][50]) {
    cout << " " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

int lose(int n, int a[50][50]) {
    cout << "Field with mines:" << endl;
    showa(n, a);
    cout << " " << endl;
    cout << "YOU ARE LOSE!\n1.Play again\n2.Exit" << endl;
    int v;
    while (true) {
        cin >> v;
        if (v == 1 || v == 2) {
            break;
        }
        else {
            cout << "Incorrect input. Try again" << endl;
        }
        if (!cin) {
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    if (v == 1) {
        game();
    }
    if (v == 2) {
        exit(0);
    }
    return 0;
}

void mines(int n, int a[50][50], int& z, int r) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = Random(0, 1);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 0) {
                z++;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 1) {
                r++;
            }
        }
    }
}

void stars(int n, char b[50][50]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i][j] = '*';
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << b[i][j] << " ";
        }
        cout << endl;
    }
}

void change(int n, int x, int y, int a[50][50], char b[50][50], int& e) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == x - 1 && j == y - 1) {
                if (a[i][j] == 1) {
                    lose(n, a);
                }
                else if (a[i][j] == 0) {
                    e++;
                    int q = 0;
                    if (i > 0 && a[i - 1][j] != 0) q++;
                    if (i < n - 1 && a[i + 1][j] != 0) q++;
                    if (j > 0 && a[i][j - 1] != 0) q++;
                    if (j < n - 1 && a[i][j + 1] != 0) q++;
                    if (i > 0 && j > 0 && a[i - 1][j - 1] != 0) q++;
                    if (i > 0 && j < n - 1 && a[i - 1][j + 1] != 0) q++;
                    if (i < n - 1 && j > 0 && a[i + 1][j - 1] != 0) q++;
                    if (i < n - 1 && j < n - 1 && a[i + 1][j + 1] != 0) q++;
                    b[i][j] = q + '0';
                }
            }
        }
    }
}

void win(int z, int e) {
    if (z == e) {
        cout << "AAAAAAA YOU ARE WIN!!!!!!!!WELL DONE!!!!!!!!!" << endl;
        exit(0);
    }
}

void examination(int n, int a[50][50], int z, int r) {
    if (n == z) {
        mines(n, a, z, r);
    }
    if (n == r) {
        mines(n, a, z, r);
    }
}

void game() {
    int n, x, y, z = 0, e = 0, r = 0;
    while (true) {
        cout << "Enter field size: ";
        cin >> n;
        if (n > 1 && n <= 50) {
            break;
        }
        else {
            cout << "Incorrect input. Try again" << endl;
        }
        if (!cin) {
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    char b[50][50];
    int a[50][50];
    stars(n, b);
    mines(n, a, z, r);
    examination(n, a, z, r);
    while (true) {
        cout << " " << endl;
        while (true) {
            cout << "Enter x and y:" << endl;
            cin >> x >> y;
            if (x > 0 && y > 0 && x <= n && y <= n) {
                break;
            }
            else {
                cout << "Incorrect input. Try again" << endl;
            } if (!cin) {
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        change(n, x, y, a, b, e);
        cout << " " << endl;
        win(z, e);
        showb(n, b);
    }
}

int main() {
    game();
    return 0;
}