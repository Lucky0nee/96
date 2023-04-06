#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> matrix;
typedef std::vector<int> vector;

void printMartix(matrix _matrix) {
    for (int i = 0; i < _matrix.size(); i++) {
        for (int j = 0; j < _matrix[i].size(); j++) {
            std::cout << _matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void printVector(vector _vector) {
    for (int i = 0; i < _vector.size(); i++) {
        std::cout << _vector[i] << " ";
    }
}

int minimumValueInAllMatrix(matrix _matrix, vector needForAmmunition, vector stocksInWarehouses, int &MinimumIndexX, int &MinimumIndexY) {
    int MinimumNumber = INT_MAX;

    for (int i = 0; i < _matrix.size(); i++) {
        for (int j = 0; j < _matrix[i].size(); j++) {
            if (_matrix[i][j] < MinimumNumber) {
                if (_matrix[i][j] != INT_MAX) {
                    if (needForAmmunition[j] != 0) {
                        if (stocksInWarehouses[i] != 0) {
                            MinimumNumber = _matrix[i][j];
                            MinimumIndexX = j;
                            MinimumIndexY = i;
                        }
                    }
                }
            }
        }
    }
    if (MinimumNumber == INT_MAX)
        return -1;

    return MinimumNumber;
}

bool endCalc(vector _vector) {
    for (int i = 0; i < _vector.size(); i++) {
        if (_vector[i] != 0) {
            return false;
        }
    }
    return true;
}

int calcBestPrice(matrix _matrix, vector& needForAmmunition, vector& stocksInWarehouses) {
    again:
    int sum = 0;
    int x, y;
    for (int i = 0; i < _matrix.size() + 1; i++) {
        for (int j = 0; j < _matrix[j].size(); j++) {
        loop:
            int number = minimumValueInAllMatrix(_matrix, needForAmmunition, stocksInWarehouses, x, y);

            if (number == -1) {
                break;
            }

            int tempVariable1 = stocksInWarehouses[y];
            int tempVariable2 = needForAmmunition[x];

            stocksInWarehouses[y] -= needForAmmunition[x];

            if (stocksInWarehouses[y] < 0) {
                needForAmmunition[x] -= tempVariable1;
                sum += number * (tempVariable2 - needForAmmunition[x]);
                stocksInWarehouses[y] = 0;
            }
            else {
                sum += number * needForAmmunition[x];
                needForAmmunition[x] = 0;
            }

            if (needForAmmunition[x] == 0) {
                break;
            }
            else {
                _matrix[y][x] = INT_MAX;
                goto loop;
            }
        }
    }

    if (!endCalc(needForAmmunition)) {
        if (minimumValueInAllMatrix(_matrix, needForAmmunition, stocksInWarehouses, x, y) == -1) {
            std::cout << "\n\nStocks are not enough, only part was exported\n";
        }
        else
        {
            goto again;
        }
    }

    return sum;
}

int main() {
    srand(time(NULL));
    matrix transportationCost /* = { {5, 6, 2, 9, 3}, {4, 7, 1, 8, 4}, {6, 8, 7, 3, 9}, {8, 5, 8, 6, 7} } */;
    vector needForAmmunition /*= { 100, 150, 50, 200, 250 }*/;
    vector stocksInWarehouses /*= {1000, 10, 500, 200}*/;

    int batteries /*= 5*/;
    int warehouse /*= 4*/;

    std::cout << "Specify the required number of batteries ammunition" << "\n" << "->";
    std::cin >> batteries;

    std::cout << "Specify the number of storage where they can be obtained" << "\n" << "->";
    std::cin >> warehouse;

    vector tempVariable;

    for (int y = 0; y < warehouse; y++) {
        transportationCost.push_back(tempVariable);
        for (int x = 0; x < batteries; x++) {
            transportationCost[y].push_back(rand() % 9 + 1);
        }
    }

    for (int y = 0; y < batteries; y++) {
        needForAmmunition.push_back((rand() % 80 + 1) * 10);
    }

    for (int y = 0; y < warehouse; y++) {
        stocksInWarehouses.push_back((rand() % 100 + 1) * 10);
    }

    printMartix(transportationCost);
    std::cout << "\nNeed for ammunition: ";
    printVector(needForAmmunition);
    std::cout << "\nStocks in warehouses: ";
    printVector(stocksInWarehouses);

    int result = calcBestPrice(transportationCost, needForAmmunition, stocksInWarehouses);

    std::cout << "\nNeed for ammunition: ";
    printVector(needForAmmunition);
    std::cout << "\nStocks in warehouses: ";
    printVector(stocksInWarehouses);

    std::cout << "\n" << "Transportation cost = " << result;

    return EXIT_SUCCESS;
}

/*
Сформуйте простір імен, який міститиме такі поля: 
три числових поля, два вектори чисел, три матриці чисел.

Задайте з клавіатури кількість батарей, які потребують
снарядів і кількість складів, де їх можна отримати.

Після цього сформуйте вектори потреб і запасів відповідних
розмірів, виведіть їх на екран.

І порівняйте їх між собою.

Залежно від цього завдання матиме варіанти розв’язку.
Потім сформуйте матрицю цін перевезення однієї штуки з
кожного складу до кожної батареї і виведіть її на екран.

При бажанні усі значення можна задати випадковим чином.

Приклад даних можна знайти за адресою.

Вам потрібно визначити і вивести на екран для кожної батареї
кількість снарядів, які можна завезти з того чи іншого складу
таким чином, щоб вартість перевезення була мінімальна.
Це буде матриця перевезень.

Наприклад:
100 0 40 0 250
0 0 10 0 0
0 0 0 200 0
0 150 0 0 0

Потім перемножте матрицю перевезень на матрицю цін і
отримайте матрицю вартостей і виведіть на екран.

Наприклад:
500 0 80 0 750
0 0 10 0 0
0 0 0 600 0
0 750 0 0 0

Потім знайдіть суму всіх її значень і виведіть її на екран.
*/
