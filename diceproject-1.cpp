#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h> 

struct Player {
    std::string name;
    int roll;
    std::string result;
};

#define RED_TEXT "\033[1;31m"   // Red
#define GREEN_TEXT "\033[1;32m" // Green
#define RESET_TEXT "\033[0m"      // Reset to default

Player getPlayer(int playerNumber) {
    Player player;
    std::cout << "Enter Player " << playerNumber << "'s Name: ";
    std::cin >> player.name;
    player.roll = std::rand() % 20 + 1;
    player.result = (player.roll == 1) ? RED_TEXT "Critical Failure" RESET_TEXT : (player.roll == 20) ? GREEN_TEXT "Critical Success" RESET_TEXT : "";
    return player;
}

void printPlayer(const Player& player) {
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE); // Get the console output handle

    if (player.result.find("Critical Failure") != std::string::npos) {
        SetConsoleTextAttribute(screen, 12); // text color to bright red 
    } else if (player.result.find("Critical Success") != std::string::npos) {
        SetConsoleTextAttribute(screen, 10); // text color to bright green 
    }

    std::cout << player.name << ": " << player.roll << " " << player.result << RESET_TEXT << std::endl;

    // Restore normal text color
    SetConsoleTextAttribute(screen, 7);
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    Player player1 = getPlayer(1);
    Player player2 = getPlayer(2);
    
    std::cout << "Rolls:" << std::endl;
    printPlayer(player1);
    printPlayer(player2);
    
    if (player1.roll > player2.roll) {
        std::cout << "The winner is " << player1.name << std::endl;
    } else if (player2.roll > player1.roll) {
        std::cout << "The winner is " << player2.name << std::endl;
    } else {
        std::cout << "The players are evenly matched!" << std::endl;
    }
    
    return 0;
}
