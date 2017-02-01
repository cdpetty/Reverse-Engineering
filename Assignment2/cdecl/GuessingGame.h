#include <iostream>
#include <vector>

class Dice {
    private:
        int rolled; 
    public:
        Dice() {}
        void __attribute__( (__cdecl__ )) roll();
        int __attribute__( (__cdecl__ )) getRolled();
};

class Player {
    private:
        std::vector<int> guesses;
        int score;
    public:
        Player() {
            score = 0; 
        }
        void __attribute__( (__cdecl__ )) guess(int a);
        int __attribute__( (__cdecl__ )) getLastGuess();
        int __attribute__( (__cdecl__ )) getNumGuesses();
        void __attribute__( (__cdecl__ )) addWin();
        int __attribute__( (__cdecl__ )) getNumWins();
};
