#include "task.h"
#include <limits>
#include <cstdlib>
#include <ctime>
#include <fstream>

void showMenu() {
    std::cout << "\n╔═════════════════════════════════════════╗\n";
    std::cout << "║  ПРОВЕРКА СКОБОЧНОЙ ПОСЛЕДОВАТЕЛЬНОСТИ  ║\n";
    std::cout << "╠═════════════════════════════════════════╣\n";
    std::cout << "║  1. Ввести последовательность скобок    ║\n";
    std::cout << "║  2. Проверить последнюю введенную       ║\n";
    std::cout << "║  3. Примеры                             ║\n";
    std::cout << "║  4. Правила                             ║\n";
    std::cout << "║  0. Выход                               ║\n";
    std::cout << "╚═════════════════════════════════════════╝\n";
    std::cout << "Выберите пункт (0-4): ";
}

void showInputMenu() {
    std::cout << "\n═══════════════════════════════════════════\n";
    std::cout << "            ВЫБЕРИТЕ СПОСОБ ВВОДА\n";
    std::cout << "═══════════════════════════════════════════\n";
    std::cout << "  1. Ввод с клавиатуры\n";
    std::cout << "  2. Случайная последовательность\n";
    std::cout << "  3. Чтение из файла\n";
    std::cout << "  0. Назад\n";
    std::cout << "═══════════════════════════════════════════\n";
    std::cout << "Выберите пункт (0-3): ";
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void waitForEnter() {
    std::cout << "\nНажмите Enter чтобы продолжить...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void showRules() {
    std::cout << "\n═══════════════════════════════════════════\n";
    std::cout << "                  ПРАВИЛА\n";
    std::cout << "═══════════════════════════════════════════\n\n";
    std::cout << "Последовательность считается корректной, если:\n";
    std::cout << "  • Каждая открывающая скобка имеет соответствующую закрывающую\n";
    std::cout << "  • Скобки закрываются в правильном порядке\n\n";
    std::cout << "Допустимые символы: ( ) [ ] { } и пробелы\n";
    std::cout << "═══════════════════════════════════════════\n";
}

void showExamples() {
    BracketChecker checker;
    
    std::cout << "\n═══════════════════════════════════════════\n";
    std::cout << "                  ПРИМЕРЫ\n";
    std::cout << "═══════════════════════════════════════════\n\n";
    
    std::cout << "1. ПРАВИЛЬНО:\n";
    checker.printResult("{ [ ( ) ] }");
    
    std::cout << "\n2. НЕПРАВИЛЬНО:\n";
    checker.printResult("([)]");

    std::cout << "\n3. НЕДОПУСТИМЫЕ СИМВОЛЫ:\n";
    checker.printResult("abc");
}

std::string generateRandomSequence() {
    srand(time(nullptr));
    int length = rand() % 20 + 5;
    std::string brackets = "()[]{}";
    std::string result = "";
    
    for (int i = 0; i < length; i++) {
        result += brackets[rand() % 6];
    }
    return result;
}

std::string readFromFile() {
    std::string filename;
    std::string sequence = "";
    std::ifstream file;
    
    std::cout << "Введите имя файла: ";
    std::cin >> filename;
    
    file.open(filename.c_str());
    if (!file.is_open()) {
        std::cout << "\n✗ Ошибка: не удалось открыть файл!\n";
        return "";
    }
    
    std::getline(file, sequence);
    file.close();
    
    if (sequence.empty()) {
        std::cout << "\n✗ Ошибка: файл пуст!\n";
        return "";
    }
    
    std::cout << "\n✓ Последовательность загружена из файла\n";
    return sequence;
}

int main() {
    BracketChecker checker;
    std::string currentSequence = "";
    int choice;
    int inputChoice;
    
    do {
        clearScreen();
        showMenu();
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите число от 0 до 4!\n";
            waitForEnter();
            continue;
        }
        
        switch (choice) {
            case 1: {
                do {
                    clearScreen();
                    showInputMenu();
                    std::cin >> inputChoice;
                    
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Ошибка: введите число от 0 до 3!\n";
                        waitForEnter();
                        continue;
                    }
                    
                    switch (inputChoice) {
                        case 1: {
                            clearScreen();
                            std::cout << "\n═══════════════════════════════════════════\n";
                            std::cout << "             ВВОД С КЛАВИАТУРЫ\n";
                            std::cout << "═══════════════════════════════════════════\n";
                            std::cout << "Введите последовательность (разрешены только скобки ()[]{} и пробелы): ";
                            
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::getline(std::cin, currentSequence);
                            
                            std::cout << "\n✓ Последовательность сохранена!\n";
                            waitForEnter();
                            break;
                        }
                        case 2: {
                            clearScreen();
                            std::cout << "\n═══════════════════════════════════════════\n";
                            std::cout << "          СЛУЧАЙНАЯ ПОСЛЕДОВАТЕЛЬНОСТЬ\n";
                            std::cout << "═══════════════════════════════════════════\n";
                            
                            currentSequence = generateRandomSequence();
                            std::cout << "\nСгенерирована последовательность: \"" << currentSequence << "\"\n";
                            std::cout << "\n✓ Последовательность сохранена!\n";
                            waitForEnter();
                            break;
                        }
                        case 3: {
                            clearScreen();
                            std::cout << "\n═══════════════════════════════════════════\n";
                            std::cout << "             ЧТЕНИЕ ИЗ ФАЙЛА\n";
                            std::cout << "═══════════════════════════════════════════\n";
                            
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            currentSequence = readFromFile();
                            if (!currentSequence.empty()) {
                                std::cout << "\nЗагружена последовательность: \"" << currentSequence << "\"\n";
                                std::cout << "\n✓ Последовательность сохранена!\n";
                            }
                            waitForEnter();
                            break;
                        }
                        case 0: {
                            break;
                        }
                        default: {
                            std::cout << "\n✗ Неверный выбор! Введите число от 0 до 3.\n";
                            waitForEnter();
                            break;
                        }
                    }
                } while (inputChoice != 0);
                break;
            }
            case 2: {
                clearScreen();
                std::cout << "\n═══════════════════════════════════════════\n";
                std::cout << "             ПРОВЕРКА ПОСЛЕДОВАТЕЛЬНОСТИ\n";
                std::cout << "═══════════════════════════════════════════\n";
                if (currentSequence.empty()) {
                    std::cout << "\n✗ Ошибка: сначала введите последовательность (пункт 1)!\n";
                } else {
                    checker.printResult(currentSequence);
                }
                waitForEnter();
                break;
            }
            case 3: {
                clearScreen();
                showExamples();
                waitForEnter();
                break;
            }
            case 4: {
                clearScreen();
                showRules();
                waitForEnter();
                break;
            }
            case 0: {
                clearScreen();
                std::cout << "\n═══════════════════════════════════════════\n";
                std::cout << "                  ДО СВИДАНИЯ!\n";
                std::cout << "═══════════════════════════════════════════\n\n";
                break;
            }
            default: {
                std::cout << "\n✗ Неверный выбор! Введите число от 0 до 4.\n";
                waitForEnter();
                break;
            }
        }
        
    } while (choice != 0);
    
    return 0;
}