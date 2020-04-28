#ifndef VECTOR_H
#define VECTOR_H

template<typename T>        
class Vector {              
    T* arr;
    int numberOfElements;
    int capacity;

    void resize() {
        T* newArr = new T[2 * capacity];

        for (int i = 0; i < numberOfElements; i++) {
            newArr[i] = arr[i];
        }
        
        capacity *= 2;
        delete[] arr;
        arr = newArr;
    }

public:
    bool hasElement(const T& element) const {
        for (int i = 0; i < numberOfElements; i++) {
            if (arr[i] == element) {
                return true;
            }
        }
        return false;
    }

    Vector() {
        numberOfElements = 0;
        capacity = 8;
        arr = new T[capacity];
    }

    Vector(const Vector<T>& other) {
        numberOfElements = other.numberOfElements;
        capacity = other.capacity;
        arr = new T[capacity];

        for (int i = 0; i < numberOfElements; i++) {
            arr[i] = other.arr[i];
        }
    }

    Vector& operator=(const Vector<T>& other) {
        if (this != &other) {
            delete[] arr;

            numberOfElements = other.numberOfElements;
            capacity = other.capacity;
            arr = new T[capacity];

            for (int i = 0; i < numberOfElements; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    ~Vector() {
        delete[] arr;
    }

    void addElement(const T& element) {
        if (capacity == numberOfElements) {
            resize();
        }
        arr[numberOfElements] = element;
        numberOfElements++;
    }

    int getNumberOfElements() const {
        return numberOfElements;
    }

    T& operator[](int i) {
        return arr[i];
    }

    T operator[](int i) const {
        return arr[i];
    }

    void removeAt(int i) {
        for (int k = i + 1; k < numberOfElements; k++) {
            arr[k - 1] = arr[k];
        }
        numberOfElements--;
    }

    void removeValue(const T& value) {
        for (int i = 0; i < numberOfElements; i++) {
            if (arr[i] == value) {
                removeAt(i);
                i--;
            }
        }
    }

    void removeDuplicates() {
        for (int i = 0; i < numberOfElements; i++) {
            for (int k = i + 1; k < numberOfElements; k++) {
                if (arr[i] == arr[k]) {
                    removeAt(k);
                    k--;
                }
            }
        }
    }
};

#endif