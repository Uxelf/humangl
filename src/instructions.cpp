#include <iostream>

void print_instructions(){
    std::cout << std::endl << "\e[93m";
    std::cout << "Instructions:" << std::endl;
    std::cout << "WASD: move" << std::endl;
    std::cout << "Space / Shift: Up / Down" << std::endl;
    std::cout << "Mouse: rotate camera" << std::endl;
    std::cout << "Mouse scroll: change FOV" << std::endl;
    std::cout << "\e[0m" << std::endl;
}