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

void showb(int field, char playerView[50][50]) {
    cout << " " << endl;
    for (int i = 0; i < field; i++) {
        for (int j = 0; j < field; j++) {
            cout << playerView[i][j] << " ";
        }
        cout << endl;
    }
}

void showa(int field, int minesMap[50][50]) {
    cout << " " << endl;
    for (int i = 0; i < field; i++) {
        for (int j = 0; j < field; j++) {
            cout << minesMap[i][j] << " ";
        }
        cout << endl;
    }
}

int lose(int field, int minesMap[50][50]) {
    cout << "Field with mines:" << endl;
    showa(field, minesMap);
    cout << " " << endl;
    cout << "YOU ARE LOSE!\n1.Play again\n2.Exit" << endl;
    int choice;
    while (true) {
        cin >> choice;
        if (choice == 1 || choice == 2) {
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
    if (choice == 1) {
        game();
    }
    if (choice == 2) {
        exit(0);
    }
    return 0;
}

void mines(int field, int minesMap[50][50], int& zero, int& one) {
    zero = 0;
    one = 0;
    for (int i = 0; i < field; i++) {
        for (int j = 0; j < field; j++) {
            minesMap[i][j] = Random(0, 1);
            if (minesMap[i][j] == 0) zero++;
            else one++;
        }
    }
    
}

void stars(int field, char playerView[50][50]) {
    for (int i = 0; i < field; i++) {
        for (int j = 0; j < field; j++) {
            playerView[i][j] = '*';
        }
    }
    for (int i = 0; i < field; i++) {
        for (int j = 0; j < field; j++) {
            cout << playerView[i][j] << " ";
        }
        cout << endl;
    }
}

void change(int field, int choiceX, int choiceY, int minesMap[50][50], char playerView[50][50], int& open) {
    for (int i = 0; i < field; i++) {
        for (int j = 0; j < field; j++) {
            if (i == choiceX - 1 && j == choiceY - 1) {
                if (minesMap[i][j] == 1) {
                    lose(field, minesMap);
                }
                else if (minesMap[i][j] == 0) {
                    open++;
                    int minesArround = 0;
                    if (i > 0 && minesMap[i - 1][j] != 0) minesArround++;
                    if (i < field - 1 && minesMap[i + 1][j] != 0) minesArround++;
                    if (j > 0 && minesMap[i][j - 1] != 0) minesArround++;
                    if (j < field - 1 && minesMap[i][j + 1] != 0) minesArround++;
                    if (i > 0 && j > 0 && minesMap[i - 1][j - 1] != 0) minesArround++;
                    if (i > 0 && j < field - 1 && minesMap[i - 1][j + 1] != 0) minesArround++;
                    if (i < field - 1 && j > 0 && minesMap[i + 1][j - 1] != 0) minesArround++;
                    if (i < field - 1 && j < field - 1 && minesMap[i + 1][j + 1] != 0) minesArround++;
                    playerView[i][j] = minesArround + '0';
                }
            }
        }
    }
}

void win(int zero, int open) {
    if (zero == open) {
        cout << "AAAAAAA YOU ARE WIN!!!!!!!!WELL DONE!!!!!!!!!" << endl;
        exit(0);
    }
}

void examination(int field, int minesMap[50][50], int zero, int one) {
    if (field == zero) {
        mines(field, minesMap, zero, one);
    }
    if (field == one) {
        mines(field, minesMap, zero, one);
    }
}

void game() {
    int field, choiceX, choiceY, zero = 0, open = 0, one = 0;
    while (true) {
        cout << "Enter field size: ";
        cin >> field;
        if (field > 1 && field <= 50) {
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
    char playerView[50][50];
    int minesMap[50][50];
    stars(field, playerView);
    mines(field, minesMap, zero, one);
    examination(field, minesMap, zero, one);
    while (true) {
        cout << " " << endl;
        while (true) {
            cout << "Enter x and y:" << endl;
            cin >> choiceX >> choiceY;
            if (choiceX > 0 && choiceY > 0 && choiceX <= field && choiceY <= field) {
                break;
            }
            else {
                cout << "Incorrect input. Try again" << endl;
            } if (!cin) {
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        change(field, choiceX, choiceY, minesMap, playerView, open);
        cout << " " << endl;
        win(zero, open);
        showb(field, playerView);
    }
}

int main() {
    game();
    return 0;
}
