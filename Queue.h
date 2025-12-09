#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>

const int MAX_SIZE = 100;

// номер 1


template <typename T>
class Queue {
private:
    T arr[MAX_SIZE];
    int frontIndex;
    int rearIndex;  
    int count;     

public:
    Queue() : frontIndex(0), rearIndex(0), count(0) {}

    bool isEmpty() const {
        return count == 0;
    }

    T first() const {
        if (isEmpty()) {
            throw std::out_of_range("Очередь пуста. Невозможно получить первый элемент.");
        }
        return arr[frontIndex];
    }


    void push(const T& value) {
        if (count == MAX_SIZE) {
            throw std::out_of_range("Очередь полна. Невозможно добавить элемент.");
        }
        arr[rearIndex] = value;
        rearIndex = (rearIndex + 1) % MAX_SIZE; 
        count++;
    }


    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Очередь пуста. Невозможно удалить элемент.");
        }
        frontIndex = (frontIndex + 1) % MAX_SIZE; // Сдвигаем начало очереди
        count--;
    }


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


    int size() const {
        return count;
    }
    
    T& operator[](int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Индекс вне границ очереди.");
        }
        return arr[(frontIndex + index) % MAX_SIZE];
    }
};

// номер 2

class Ingredient {
public:
    std::string name;
    int cookingTimeSeconds;

    Ingredient(const std::string& n, int t) : name(n), cookingTimeSeconds(t) {}

    friend std::ostream& operator<<(std::ostream& os, const Ingredient& ing) {
        return os << ing.name << " (" << ing.cookingTimeSeconds << " сек)";
    }

    bool operator<(const Ingredient& other) const {
        return cookingTimeSeconds > other.cookingTimeSeconds;
    }
};