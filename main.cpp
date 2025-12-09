#include "Queue.h"
#include <iostream>
#include <vector>
#include <limits>
#include <clocale>
#ifdef _WIN32
#include <windows.h>
#endif


// номер 1

void task1() {
    std::cout << "===== номер 1 =====" << std::endl;

    Queue<std::string> stringQueue;

    std::vector<std::string> initialStrings = {"one", "two", "three", "four", "five", "six"};
    for (const auto& str : initialStrings) {
        stringQueue.push(str);
        std::cout << "Добавлено: \"" << str << "\"" << std::endl;
    }

    std::cout << "\n--- Очередь после добавления 6 элементов ---" << std::endl;
    stringQueue.show();

    std::cout << "\nУдаляем 2 элемента:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        if (!stringQueue.isEmpty()) {
            std::cout << "Удалено: \"" << stringQueue.first() << "\"" << std::endl;
            stringQueue.pop();
        }
    }

    stringQueue.push("seven");
    std::cout << "\nДобавлено: \"seven\"" << std::endl;

    std::cout << "\n--- Очередь после удаления и добавления \"seven\" ---" << std::endl;
    stringQueue.show();

    int countFT = 0;
    for (int i = 0; i < stringQueue.size(); ++i) {
        const std::string& str = stringQueue[i];
        if (!str.empty() && (str[0] == 'f' || str[0] == 't')) {
            countFT++;
            std::cout << "  - Найдена строка, начинающаяся с 'f' или 't': \"" << str << "\"" << std::endl;
        }
    }

    std::cout << "\nКоличество строк, начинающихся с 'f' или 't': " << countFT << std::endl;
}


// номер 2

void task2() {
    std::cout << "\n\n===== номер 2 =====" << std::endl;

    std::priority_queue<Ingredient> ingredientQueue;

    int choice;
    do {
        std::cout << "\nEnter what you want to do:" << std::endl;
        std::cout << "1 - Add ingredient" << std::endl;
        std::cout << "2 - Cook a dish" << std::endl;
        std::cout << "0 - Exit" << std::endl;
        std::cout << "Your choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Некорректный ввод. Попробуйте еще раз." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
            continue;
        }

        switch (choice) {
            case 1: {
                std::string name;
                int time;
                std::cout << "\nEnter name of ingredient: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, name);

                std::cout << "Enter time of cooking(seconds): ";
                if (!(std::cin >> time) || time < 0) {
                    std::cout << "Некорректное время приготовления. Ингредиент не добавлен." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }

                ingredientQueue.push(Ingredient(name, time));
                std::cout << "Ингредиент \"" << name << "\" добавлен в очередь." << std::endl;
                break;
            }
            case 2: {
                if (ingredientQueue.empty()) {
                    std::cout << "\nОчередь ингредиентов пуста. Добавьте ингредиенты сначала." << std::endl;
                } else {
                    std::cout << "\n--- Начинаем приготовление блюда ---" << std::endl;
                    int totalTime = 0;
                    
                    while (!ingredientQueue.empty()) {
                        Ingredient nextIngredient = ingredientQueue.top();
                        ingredientQueue.pop();

                        std::cout << "Готовим: " << nextIngredient << std::endl;
                        
                        std::cout << "  [Симуляция: ожидание " << nextIngredient.cookingTimeSeconds << " сек... Готово!]" << std::endl;
                        totalTime += nextIngredient.cookingTimeSeconds;
                    }
                    std::cout << "--- Приготовление завершено! Общее время: " << totalTime << " секунд. ---" << std::endl;
                }
                break;
            }
            case 0: {
                std::cout << "\nВыход из программы Мультикухня." << std::endl;
                break;
            }
            default: {
                std::cout << "\nНеизвестный выбор. Попробуйте 1, 2 или 0." << std::endl;
                break;
            }
        }
    } while (choice != 0);
}


int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    if (setlocale(LC_ALL, "uk_UA.UTF-8") == nullptr) {
        setlocale(LC_ALL, "C.UTF-8"); 
    }
    std::locale::global(std::locale(""));


    // номер 1
    task1();

    // номер 2
    task2();

    return 0;
}