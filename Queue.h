#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>

// Максимальный размер очереди для демонстрации на основе массива
const int MAX_SIZE = 100;

// =========================================================
//                  ЗАДАНИЕ 1: Шаблонный класс "Черга" (Queue)
// =========================================================

/**
 * @brief Шаблонный класс очереди на основе массива (FIFO).
 * Вся реализация находится здесь, так как это шаблонный класс.
 * @tparam T Тип данных элементов очереди.
 */
template <typename T>
class Queue {
private:
    T arr[MAX_SIZE];
    int frontIndex; // Индекс начала очереди
    int rearIndex;  // Индекс конца очереди (место для следующего элемента)
    int count;      // Текущее количество элементов

public:
    // Конструктор
    Queue() : frontIndex(0), rearIndex(0), count(0) {}

    /**
     * @brief Проверяет, пуста ли очередь.
     */
    bool isEmpty() const {
        return count == 0;
    }

    /**
     * @brief Возвращает первый элемент очереди без его удаления.
     */
    T first() const {
        if (isEmpty()) {
            throw std::out_of_range("Очередь пуста. Невозможно получить первый элемент.");
        }
        return arr[frontIndex];
    }

    /**
     * @brief Добавляет элемент в конец очереди.
     */
    void push(const T& value) {
        if (count == MAX_SIZE) {
            throw std::out_of_range("Очередь полна. Невозможно добавить элемент.");
        }
        arr[rearIndex] = value;
        rearIndex = (rearIndex + 1) % MAX_SIZE; // Циклический буфер
        count++;
    }

    /**
     * @brief Удаляет элемент из начала очереди.
     */
    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Очередь пуста. Невозможно удалить элемент.");
        }
        frontIndex = (frontIndex + 1) % MAX_SIZE; // Сдвигаем начало очереди
        count--;
    }

    /**
     * @brief Отображает содержимое очереди.
     */
    void show() const {
        if (isEmpty()) {
            std::cout << "(Очередь пуста)" << std::endl;
            return;
        }

        std::cout << "Содержимое очереди (Front -> Rear): ";
        int current = frontIndex;
        for (int i = 0; i < count; ++i) {
            std::cout << arr[current] << (i < count - 1 ? ", " : "");
            current = (current + 1) % MAX_SIZE;
        }
        std::cout << std::endl;
    }

    /**
     * @brief Возвращает текущее количество элементов в очереди.
     */
    int size() const {
        return count;
    }
    
    /**
     * @brief Доступ к элементу по индексу.
     */
    T& operator[](int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Индекс вне границ очереди.");
        }
        return arr[(frontIndex + index) % MAX_SIZE];
    }
};

// =========================================================
//                ЗАДАНИЕ 2: Класс Ингредиент
// =========================================================

/**
 * @brief Класс Ингредиент для задачи Мультикухня.
 */
class Ingredient {
public:
    std::string name;
    int cookingTimeSeconds;

    // Конструктор
    Ingredient(const std::string& n, int t) : name(n), cookingTimeSeconds(t) {}

    // Для удобного вывода
    friend std::ostream& operator<<(std::ostream& os, const Ingredient& ing) {
        return os << ing.name << " (" << ing.cookingTimeSeconds << " сек)";
    }

    /**
     * @brief Перегрузка оператора меньше (<) для приоритетной очереди.
     * Элемент с МЕНЬШИМ временем считается "большим" для приоритетной очереди,
     * чтобы обеспечить MIN-кучу (наименьшее время сверху).
     */
    bool operator<(const Ingredient& other) const {
        return cookingTimeSeconds > other.cookingTimeSeconds;
    }
};