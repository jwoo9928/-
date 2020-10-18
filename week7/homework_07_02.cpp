#include <iostream>

bool funcA() {
    int c;
    std::cin >> c;
    if (c < 10) //Let's assume this is exception
        return false;
    return true;
}
int main() {
    bool a;
    try {
        if (a = !funcA()) throw a;
    }
    catch (bool exception) {
        std::cout << "Exception : Invalid Input!!" << std::endl;
    }
    return 0;
}
