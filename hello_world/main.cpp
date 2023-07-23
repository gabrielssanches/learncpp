#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "Hello World!\n";

    std::cout << "got " << argc << " arguments:\n";
    for (int i = 0; i < argc; i++) {
        std::cout << "arg[" << i << "]: " << argv[i] <<  "\n";
    }
    return 0;
}
