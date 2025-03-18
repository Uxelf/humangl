#include <iostream>

void print_instructions(){
    std::cout << std::endl << "\e[93m";
    std::cout << "Instructions:" << std::endl;
    std::cout << "Arrows: move" << std::endl;
    std::cout << "\e[0m" << std::endl;
}