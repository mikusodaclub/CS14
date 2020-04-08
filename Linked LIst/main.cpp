#include <iostream>
#include <string>
#include "Playlist.h"
using namespace std;
int main() {

    std::string title;
    std::cout << "Enter playlist's title:" << std::endl;
    getline(std::cin, title);
    std::cout << std::endl;
    Playlist lib = Playlist(title);
    lib.printMenu();
    return 0;
}