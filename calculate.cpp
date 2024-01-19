#include <iostream>
#include <cmath>

using namespace std;

// Абстрактный класс для операций
class Operation {
public:
    // Чисто виртуальная функция для выполнения операции
    virtual double calculate(double operand1, double operand2) const = 0;
    // Виртуальный деструктор для правильного удаления объектов производных классов
    virtual ~Operation() = default;
};

// Класс для сложения
class Addition : public Operation {
public:
    // Переопределение виртуальной функции
    double calculate(double operand1, double operand2) const override {
        return operand1 + operand2;
    }
};

// Класс для вычитания
class Subtraction : public Operation {
public:
    double calculate(double operand1, double operand2) const override {
        return operand1 - operand2;
    }
};

// Класс для умножения
class Multiplication : public Operation {
public:
    double calculate(double operand1, double operand2) const override {
        return operand1 * operand2;
    }
};

// Класс для деления
class Division : public Operation {
public:
    double calculate(double operand1, double operand2) const override {
        // Проверка деления на ноль
        if (operand2 != 0) {
            return operand1 / operand2;
        } else {
            // Вывод сообщения об ошибке
            cerr << "Ошибка: деление на ноль!\n";
            return 0.0; // Можно выбрать другое значение по умолчанию
        }
    }
};

// Класс для возведения в степень
class Power : public Operation {
public:
    double calculate(double operand1, double operand2) const override {
        return std::pow(operand1, operand2);
    }
};

// Класс для текстового калькулятора
class TextCalculator {
private:
    Operation* operation; // Текущая операция

public:
    // Конструктор, принимающий указатель на операцию
    TextCalculator(Operation* op) : operation(op) {}

    // Выполнение операции через текущую операцию
    double performOperation(double operand1, double operand2) const {
        return operation->calculate(operand1, operand2);
    }
};

// Класс с функциями-членами
class CalculatorFunctions {
public:
    // Функция сложения
    static void add(double operand1, double operand2) {
        cout << "Сложение: " << operand1 + operand2 << std::endl;
        }

    // Функция вычитания
    static void subtract(double operand1, double operand2) {
        cout << "Вычитание: " << operand1 - operand2 << std::endl;
    }

    // Функция умножения
    static void multiply(double operand1, double operand2) {
        cout << "Умножение: " << operand1 * operand2 << std::endl;
    }

    // Функция деления
    static void divide(double operand1, double operand2) {
        if (operand2 != 0) {
            cout << "Деление: " << operand1 / operand2 << std::endl;
        } else {
            cerr << "Ошибка: деление на ноль!\n";
        }
    }

    // Функция возведения в степень
    static void power(double operand1, double operand2) {
        cout << "Возведение в степень: " << std::pow(operand1, operand2) << std::endl;
    }
};

// Прототип функции
double getDoubleInput(const std::string& prompt);
void Print_Result(int choice,double operand1, double operand2,  CalculatorFunctions& calculatorFunctions);


int main() {
    bool exitProgram = false;
    // Запрос числовых значений от пользователя
        double operand1 = getDoubleInput("Введите значение operand1: ");
        double operand2 = getDoubleInput("Введите значение operand2: ");

    do {
        

        // Пример использования калькулятора
        Addition addition;
        Subtraction subtraction;
        Multiplication multiplication;
        Division division;
        Power power;

        // Создание объектов TextCalculator с разными операциями
        TextCalculator calculatorAddition(&addition);
        TextCalculator calculatorSubtraction(&subtraction);
        TextCalculator calculatorMultiplication(&multiplication);
        TextCalculator calculatorDivision(&division);
        TextCalculator calculatorPower(&power);

        // Выбор функции-члена на основе ввода
        int choice;
        std::cout << "Выберите операцию:\n"
                     " 1 - Сложение\n"
                     " 2 - Вычитание\n"
                     " 3 - Умножение\n"
                     " 4 - Деление\n"
                     " 5 - Возведение в степень (operand1 в степени operand'a2)\n"
                     " 0 - Завершить программу\n"
                     " 9 - Ввод новых значений\n"
                     "Ваш выбор: ";
        std::cin >> choice;
        std::cout << endl;

        if (choice == 0) {
            // Пользователь выбрал завершение программы
            exitProgram = true;
        }
        else if(choice == 9)
        {
            // Повторный запрос числовых значений от пользователя
            operand1 = getDoubleInput("Введите значение operand1: ");
            operand2 = getDoubleInput("Введите значение operand2: ");
        }
        else {
            // Создание объекта CalculatorFunctions
            CalculatorFunctions calculatorFunctions;

            // Вывод результата
            Print_Result(choice, operand1, operand2, calculatorFunctions);
        }

    } while (!exitProgram);

    return 0;
}

// Функция для вывода выбранного типа математического действия
void Print_Result(int choice,double operand1, double operand2,  CalculatorFunctions& calculatorFunctions)
{
    switch (choice) {
        case 1:
            calculatorFunctions.add(operand1, operand2);
            cout << "\n";
            break;
        case 2:
            calculatorFunctions.subtract(operand1, operand2);
            cout << "\n";
            break;
        case 3:
            calculatorFunctions.multiply(operand1, operand2);
            cout << "\n";
            break;
        case 4:
            calculatorFunctions.divide(operand1, operand2);
            cout << "\n";
            break;
        case 5:
            calculatorFunctions.power(operand1, operand2);
            cout << "\n";
            break;
        default:
            cerr << "Некорректный ввод.\n";
            break;
    }
}

// Определение функции getDoubleInput
double getDoubleInput(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            // Проверка, что ввод - число
            break;
        } else {
            cin.clear(); // Сброс ошибки ввода
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            cout << "Ошибка! Введите корректное число.\n";
        }
    }
    return value;
}