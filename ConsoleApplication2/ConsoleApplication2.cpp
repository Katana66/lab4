#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <string>
#include <locale.h>
// Базовый класс "Средство передвижения"
class Vehicle {
public:
    virtual ~Vehicle() = default; // Виртуальный деструктор
    virtual void info() const = 0; // Чисто виртуальная функция
};

// Класс "Велосипед"
class Bicycle : public Vehicle {
public:
    void info() const override {
        std::cout << "Это велосипед." << std::endl;
    }
};

// Класс "Автомобиль"
class Car : public Vehicle {
public:
    void info() const override {
        std::cout << "Это автомобиль." << std::endl;
    }
};

// Класс "Грузовик"
class Truck : public Vehicle {
public:
    void info() const override {
        std::cout << "Это грузовик." << std::endl;
    }
};

// Шаблонный класс для хранения массива указателей на объекты произвольного класса
template<typename T>
class ArrayStorage {
private:
    std::vector<std::shared_ptr<T>> storage;

public:
    void add(std::shared_ptr<T> item) {
        storage.push_back(item);
    }

    // Перегрузка оператора []
    std::shared_ptr<T>& operator[](size_t index) {
        if (index >= storage.size()) {
            throw std::range_error("Индекс выходит за пределы диапазона");
        }
        return storage[index];
    }

    size_t size() const {
        return storage.size();
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    try {
        ArrayStorage<Vehicle> vehicles; // Хранилище средств передвижения

        // Добавление объектов в хранилище
        vehicles.add(std::make_shared<Bicycle>());
        vehicles.add(std::make_shared<Car>());
        vehicles.add(std::make_shared<Truck>());

        // Вывод информации о каждом объекте
        for (size_t i = 0; i < vehicles.size(); ++i) {
            vehicles[i]->info();
        }

        // Пример обращения к несуществующему индексу
        vehicles[3]->info(); // Это вызовет исключение

    }
    catch (const std::range_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0; // Все ресурсы будут освобождены автоматически
}
