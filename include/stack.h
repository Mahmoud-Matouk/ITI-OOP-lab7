#ifndef STACK_H
#define STACK_H
#include "dynamicUsers.h"

class Stack {
public:
    Stack() {
        this->sizeArray = 10;
        this->top = -1;
        this->items = new Users*[sizeArray]{nullptr};
    }

    Stack(int sizeArray) {
        this->sizeArray = sizeArray;
        this->top = -1;
        this->items = new Users*[sizeArray]{nullptr};
    }

    Stack(Stack & s) {
        this->items = new Users*[s.sizeArray]{nullptr};
        this->sizeArray = s.sizeArray;
        this->top = s.top;
        for (int i = 0; i <= top; i++) {
            this->items[i] = new Users(*s.items[i]);
        }
    }

    ~Stack() {
        for (int i = 0; i <= top; i++) {
            delete items[i];
        }
        delete[] items;
    }

    bool push(Users* user) {
        if (top >= sizeArray - 1) return false;
        top++;
        items[top] = user;
        return true;
    }

    bool pop(Users** data) {
        if (top == -1) return false;
        *data = items[top];
        items[top] = nullptr;
        top--;
        return true;
    }

    bool isFull()  { return top >= sizeArray - 1; }
    bool isEmpty() { return top == -1; }
    int  getTop()  { return top; }

    Users* getItem(int index) {
        if (index < 0 || index > top) return nullptr;
        return items[index];
    }

    Stack & operator=(const Stack s) {
        for (int i = 0; i <= top; i++) {
            delete items[i];
        }
        delete[] this->items;

        items = new Users*[s.sizeArray]{nullptr};
        this->sizeArray = s.sizeArray;
        this->top = s.top;
        for (int i = 0; i <= top; i++) {
            this->items[i] = new Users(*s.items[i]);
        }
        return *this;
    }

private:
    int top;
    int sizeArray;
    Users** items;
};

#endif
