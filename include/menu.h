#ifndef MENU_H
#define MENU_H
#include "console.h"
#include "dynamicUsers.h"
#include "stack.h"

void displayMainMenu(int spaceX, int spaceY, int selectedIndex, Color color) {
    string options[4] = {"1.Add User", "2. Remove User", "3. Display Users", "4. Exit"};
    printAt(spaceX, spaceY, "=== Users Stack Application ===");
    for (int i = 1; i <= 4; i++) {
        printAt(spaceX, spaceY + i * 2, options[i - 1], selectedIndex == i, color);
    }
}

void displayPushMenu(int spaceX, int spaceY, Stack &stack) {
    clearScreen();

    if (stack.isFull()) {
        printAt(spaceX, spaceY, "Error: Stack is full! Cannot add more users.", true, Color::Red);
        printAt(spaceX, spaceY + 2, "Press any key to return...", true, Color::White);
        getArrowKey();
        return;
    }

    Users* tempUser = new Users();
    char input[MAX_SIZE]{};
    int lineStep{};

    printAt(spaceX, spaceY, "=== Add New User ===");
    lineStep += 2;

    do {
        printAt(spaceX, spaceY + lineStep, "Enter name:");
        goToXY(spaceX, spaceY + lineStep + 1);
        if (!isEscPressed(input, MAX_SIZE)) {
            delete tempUser;
            return;
        }
        if (!tempUser->setName(input)) {
            printAt(spaceX * 3, spaceY + lineStep + 2, "Invalid name (no numbers allowed)!", true, Color::Red);
        }
        lineStep += 2;
    } while (tempUser->getName()[0] == '\0');

    do {
        printAt(spaceX, spaceY + lineStep, "Enter Password:");
        goToXY(spaceX, spaceY + lineStep + 1);
        if (!isEscPressed(input, MAX_SIZE)) {
            delete tempUser;
            return;
        }
        if (!tempUser->setPassword(input)) {
            printAt(spaceX * 3, spaceY + lineStep + 2, "Invalid password (must be 7-99 characters)!", true, Color::Red);
        }
        lineStep += 2;
    } while (!tempUser->isPasswordSet());

    do {
        printAt(spaceX, spaceY + lineStep, "Enter email:");
        goToXY(spaceX, spaceY + lineStep + 1);
        if (!isEscPressed(input, MAX_SIZE)) {
            delete tempUser;
            return;
        }
        if (!tempUser->setEmail(input)) {
            printAt(spaceX * 3, spaceY + lineStep + 2, "Invalid email format (needs @ and domain)!", true, Color::Red);
        }
        lineStep += 2;
    } while (tempUser->getEmail()[0] == '\0');

    int age = 0;
    do {
        printAt(spaceX, spaceY + lineStep, "Enter age: ");
        goToXY(spaceX, spaceY + lineStep + 1);
        if (!isEscPressed(input, MAX_SIZE)) {
            delete tempUser;
            return;
        }
        age = atoi(input);
        if (!tempUser->setAge(age)) {
            printAt(spaceX * 3, spaceY + lineStep + 2, "Invalid age (must be 1-100)!", true, Color::Red);
            lineStep += 2;
        } else {
            lineStep += 3;
            break;
        }
    } while (tempUser->getAge() == 0);

    if (stack.push(tempUser)) {
        printAt(spaceX, spaceY + lineStep, "User pushed to stack successfully!", true, Color::Green);
    } else {
        printAt(spaceX, spaceY + lineStep, "Error: Stack is full! User not added.", true, Color::Red);
        delete tempUser;
    }

    printAt(spaceX, spaceY + lineStep + 2, "Press any key to return...", true, Color::White);
    getArrowKey();
}

void displayRemoveMenu(int spaceX, int spaceY, Stack &stack) {
    clearScreen();
    Users* data = nullptr;

    printAt(spaceX, spaceY, "=== Remove User from Stack ===");

    if (stack.pop(&data)) {
        printAt(spaceX, spaceY + 2, "Removed user successfully!", true, Color::Green);
        printAt(spaceX, spaceY + 4, string("Name:  ") + data->getName());
        printAt(spaceX, spaceY + 5, string("Email: ") + data->getEmail());
        printAt(spaceX, spaceY + 6, string("Age:   ") + to_string(data->getAge()));
        delete data;
    } else {
        printAt(spaceX, spaceY + 2, "Error: Stack is empty! Nothing to remove.", true, Color::Red);
    }

    printAt(spaceX, spaceY + 8, "Press any key to return...", true, Color::White);
    getArrowKey();
}

void displayStackMenu(int spaceX, int spaceY, Stack &stack) {
    clearScreen();
    printAt(spaceX, spaceY, "=== Stack Contents ===");

    if (stack.isEmpty()) {
        printAt(spaceX, spaceY + 2, "Stack is empty!", true, Color::Red);
        printAt(spaceX, spaceY + 4, "Press any key to return...", true, Color::White);
        getArrowKey();
        return;
    }

    int currentY = spaceY + 2;
    for (int i = stack.getTop(); i >= 0; i--) {
        Users* u = stack.getItem(i);
        if (u != nullptr) {
            printAt(spaceX, currentY, "User #" + to_string(i + 1) + ":");
            printAt(spaceX + 12, currentY, string("Name: ") + u->getName());
            printAt(spaceX + 38, currentY, string("Email: ") + u->getEmail());
            printAt(spaceX + 68, currentY, string("Age: ") + to_string(u->getAge()));
            currentY += 2;
        }
    }

    printAt(spaceX, currentY + 2, "Press any key to return...", true, Color::White);
    getArrowKey();
}

void initMenu(int spaceX, int spaceY, Stack &stack) {
    int selectedIndex{1};
    while (true) {
        clearScreen();
        displayMainMenu(spaceX, spaceY, selectedIndex, Color::Red);

        char key = getArrowKey();
        if (key == 'A' && selectedIndex > 1) {
            selectedIndex--;
        } else if (key == 'B' && selectedIndex < 4) {
            selectedIndex++;
        } else if (key == 'H') {
            selectedIndex = 1;
        } else if (key == 'F') {
            selectedIndex = 4;
        } else if (key == '\n' || key == '\r') {
            switch (selectedIndex) {
                case 1:
                    displayPushMenu(spaceX, spaceY, stack);
                    break;
                case 2:
                    displayRemoveMenu(spaceX, spaceY, stack);
                    break;
                case 3:
                    displayStackMenu(spaceX, spaceY, stack);
                    break;
                case 4:
                    return;
            }
        }
    }
}

#endif