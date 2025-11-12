#include <iostream>
#include <windows.h>

class DynamicArray {
protected:
    int* data;
    int size;

public:
    // Конструктор
    DynamicArray(int arrSize) {
        if (arrSize < 0) {
            std::cout << "Ошибка: размер не может быть отрицательным" << std::endl;
            size = 0;
            data = nullptr;
            return;
        }
        size = arrSize;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0; // Инициализируем нулями вместо случайных значений
        }
    }

    // Конструктор копирования
    DynamicArray(const DynamicArray& other) {
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    // Деструктор
    ~DynamicArray() {
        delete[] data;
    }

    // Сеттер
    void setValue(int index, int value) {
        if (0 <= index && index < size) {
            if (-100 <= value && value <= 100) {
                data[index] = value;
            } else {
                std::cout << "Ошибка: значение " << value << " выходит за пределы [-100, 100]" << std::endl;
            }
        } else {
            std::cout << "Ошибка: индекс " << index << " выходит за границы массива" << std::endl;
        }
    }

    // Геттер
    int getValue(int index) {
        if (0 <= index && index < size) {
            return data[index];
        } else {
            std::cout << "Ошибка: индекс " << index << " выходит за границы массива" << std::endl;
            return 0;
        }
    }

    // Функция вывода
    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    // Добавление значения в конец
    void addValue(int value) {
        if (-100 <= value && value <= 100) {
            int* newData = new int[size + 1];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            newData[size] = value;
            delete[] data;
            data = newData;
            size++;
        } else {
            std::cout << "Ошибка: значение " << value << " выходит за пределы [-100, 100]" << std::endl;
        }
    }

    // Операция сложения массивов
    DynamicArray add(const DynamicArray& other) {
        int maxSize = (size > other.size) ? size : other.size;
        DynamicArray result(maxSize);

        for (int i = 0; i < maxSize; i++) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.size) ? other.data[i] : 0;
            result.data[i] = val1 + val2;
        }

        return result;
    }

    // Операция вычитания массивов
    DynamicArray subtract(const DynamicArray& other) {
        int maxSize = (size > other.size) ? size : other.size;
        DynamicArray result(maxSize);

        for (int i = 0; i < maxSize; i++) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.size) ? other.data[i] : 0;
            result.data[i] = val1 - val2;
        }

        return result;
    }

    // Геттер для размера
    int getSize() const {
        return size;
    }
};


class UpdateDynamicArray: public DynamicArray {

public:
    // наследуем конструкторы
    UpdateDynamicArray(int arrSize) : DynamicArray(arrSize) {}

    UpdateDynamicArray(const DynamicArray& other) : DynamicArray(other) {}

    // среднее значение
    double getAverage() {
        if(size == 0) {
            return 0;
        }
        
        int sum = 0;
        for(int i = 0; i < size; i++) {
            sum += data[i];
        }

        return (double)sum / size;
    }

    // сортировка
    void bubbleSort(int* arr, int n) const {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    double getMedian() {
        if(size == 0) {
            return 0;
        }

        UpdateDynamicArray temp(*this);

        temp.bubbleSort(temp.data, temp.size);

        double median;
        if (size % 2 == 0) {
            median = (temp.data[size / 2 - 1] + temp.data[size / 2]) / 2.0; //медиана среднее двух элементов посередине
        } else {
            median = temp.data[size / 2];
        }

        return median;

    }

    int getMax() {
        int maxi = 0;
        for(int i = 0; i < size; i++) {
            if(data[i] > data[maxi]) {
                maxi = i;
            }
        }
        return data[maxi];
    }

    int getMin() {
        int mini = 0;
        for(int i = 0; i < size; i++) {
            if(data[i] < data[mini]) {
                mini = i;
            }
        }
        return data[mini];
    }
    
};


int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    UpdateDynamicArray arr(5);

    arr.setValue(0, 10);
    arr.setValue(1, 5);
    arr.setValue(2, -3);
    arr.setValue(3, 7);
    arr.setValue(4, 2);

    std::cout << "Массив: ";
    arr.print();

    std::cout << "Среднее значение: " << arr.getAverage() << std::endl;
    std::cout << "Медиана: " << arr.getMedian() << std::endl;
    std::cout << "Минимум: " << arr.getMin() << std::endl;
    std::cout << "Максимум: " << arr.getMax() << std::endl;

    return 0;
}