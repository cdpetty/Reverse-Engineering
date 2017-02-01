#include <iostream>
#include <vector>

class Dice {
    private:
        int rolled; 
    public:
        Dice() {}
        void roll();
        int getRolled();
};

class Player {
    private:
        std::vector<int> guesses;
        int score;
    public:
        Player() {
            score = 0; 
        }
        void guess(int a);
        int getLastGuess();
        int getNumGuesses();
        void addWin();
        int getNumWins();
};
