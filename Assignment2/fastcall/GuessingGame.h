#include <iostream>
#include <vector>

class Dice {
    private:
        int rolled; 
    public:
        Dice() {}
        void __fastcall roll();
        int __fastcall getRolled();
};

class Player {
    private:
        std::vector<int> guesses;
        int score;
    public:
        Player() {
            score = 0; 
        }
        void __fastcall guess(int a);
        int __fastcall getLastGuess();
        int __fastcall getNumGuesses();
        void __fastcall addWin();
        int __fastcall getNumWins();
};
