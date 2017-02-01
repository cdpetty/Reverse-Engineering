#include <iostream>
#include <vector>

class Dice {
    private:
        int rolled; 
    public:
        Dice() {}
        void __attribute__( (__stdcall__)) roll();
        int __attribute__( (__stdcall__)) getRolled();
};

class Player {
    private:
        std::vector<int> guesses;
        int score;
    public:
        Player() {
            score = 0; 
        }
        void __attribute__( (__stdcall__)) guess(int a);
        int __attribute__( (__stdcall__)) getLastGuess();
        int __attribute__( (__stdcall__)) getNumGuesses();
        void __attribute__( (__stdcall__)) addWin();
        int __attribute__( (__stdcall__)) getNumWins();
};
