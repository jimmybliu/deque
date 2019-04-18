#ifndef DEQUE_H
#define DEQUE_H

#include <cstddef>
#include <vector>
#include <iostream>
#include <memory>
#include <stdexcept>
template<typename T>
class Deque {
public:
    //
    // @@@ The class's public API below should not be modified @@@
    //

    // Constructor
    Deque();
    // Destructor
    ~Deque() = default;


    //
    // Capacity
    //

    // Return true if empty, false otherwise
    // Complexity: O(1)
    bool Empty () const noexcept;
    // Return number of items in deque
    // Complexity: O(1)
    size_t Size () const noexcept;
    // Resize internal data structure to fit precisely the number of items and
    // free unused memory
    // Complexity: O(N)
    void ShrinkToFit();


    //
    // Element access
    //

    // Return item at pos @pos
    // Complexity: O(1)
    T& operator[](size_t pos);
    // Return item at front of deque
    // Complexity: O(1)
    T& Front();
    // Return item at back of deque
    // Complexity: O(1)
    T& Back();


    //
    // Modifiers
    //

    // Clear contents of deque (make it empty)
    // Complexity: O(1)
    void Clear(void) noexcept;
    // Push item @value at front of deque
    // Complexity: O(1) amortized
    void PushFront(const T &value);
    // Push item @value at back of deque
    // Complexity: O(1) amortized
    void PushBack(const T &value);
    // Remove item at front of deque
    // Complexity: O(1) amortized
    void PopFront();
    // Remove item at back of deque
    void PopBack();
    // Complexity: O(1) amortized

private:
    //
    // @@@ The class's internal members below can be modified @@@
    //

    // Private member variables
    // ...To be completed...
    int cap = 3;
    std::unique_ptr<T[]> arr;
    int curSize = 0;
    int head;
    int tail;
    // Private constants
    // ...To be completed (if any)...

    // Private methods
    // ...To be completed (if any)...
    void resize(int newCap);
};

//
// Your implementation of the class should be located below
//

template<typename T>
Deque<T>::Deque() : arr(std::unique_ptr<T[]>(new T[cap])) {
    head = -1;
    tail = 0;

}

template<typename T>
bool Deque<T>::Empty() const noexcept {
    if (curSize==0){
        return true;
    }
    else{
        return false;
    }
}

template<typename T>
size_t Deque<T>::Size() const noexcept {
    return curSize;
}

template<typename T>
void Deque<T>::resize(int newCap) {
    std::unique_ptr<T[]> newArr(new T[newCap]);
    if (head <= tail){
        for (int i=head, j=0; i<=tail; i++){
            newArr[j] = arr[i];
            j++;
        }
    }
    else if(head>tail){
        int j = 0;
        for (int i=head; i<cap; i++){
            newArr[j] = arr[i];
            j++;
        }
        for (int i=0; i<=tail; i++){
            newArr[j] = arr[i];
            j++;
        }
    }

    std::swap(arr, newArr);
    head = 0;
    tail = curSize-1;
    cap = newCap;

}

template<typename T>
void Deque<T>::ShrinkToFit() {
    if (curSize<cap){
        resize(curSize);
    }
}

template<typename T>
T &Deque<T>::operator[](size_t pos) {
    if (pos >= curSize){
        throw std::out_of_range("Position out of range");
    }
    return arr[(unsigned(head) + (pos)) % cap];
}

template<typename T>
void Deque<T>::Clear(void) noexcept {
    std::unique_ptr<T[]> newArr(new T[1]);
    std::swap(arr, newArr);
    head = -1;
    tail = 0;
    curSize = 0;
}

template<typename T>
T &Deque<T>::Front() {
    if (Empty()){
        throw std::underflow_error("Underflow");
    }
    return arr[head];
}

template<typename T>
T &Deque<T>::Back() {
    if (Empty()){
        throw std::underflow_error("Underflow");
    }
    return arr[tail];
}

template<typename T>
void Deque<T>::PushFront(const T &value){
    if (curSize==cap-1){
        resize(2*curSize);
    }
    if (head == -1){
        head = 0;
        tail = 0;
    }
    else if(head == 0){
        head = cap-1;
    }
    else{
        head -= 1;
    }
    arr[head] = value;
    curSize++;
}

template<typename T>
void Deque<T>::PushBack(const T &value) {
    if (curSize==cap){
        resize(2*curSize);
    }
    if (head == -1){
        head = 0;
        tail = 0;
    }
    else if((tail) == cap-1){
        tail = 0;
    }
    else{
        tail += 1;
    }
    arr[tail] = value;
    curSize++;
}

template<typename T>
void Deque<T>::PopFront() {
    if (Empty()){
        throw std::underflow_error("Underflow");
    }
    if (head == tail){
        head = -1;
        tail = 0;
    }
    else{
        if ((head) == cap-1){
            head = 0;
        }
        else{
            head += 1;
        }
    }
    curSize--;

}

template<typename T>
void Deque<T>::PopBack() {
    if (Empty()){
        throw std::underflow_error("Underflow");
    }
    if (head == tail){
        head = -1;
        tail = -1;
    }
    else{
        if (tail == 0){
            tail = cap-1;
        }
        else{
            tail -= 1;
        }
    }
    curSize--;
}

// ...To be completed...

#endif  // DEQUE_H