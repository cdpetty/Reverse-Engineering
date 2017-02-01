#include "GuessingGame.h"
#include <iostream>
#include <random>

using namespace std;

void __attribute__( (__cdecl__ )) Dice::roll(){
    random_device rd;

    default_random_engine engine(rd());
    uniform_int_distribution<int> uniform_dist(1, 100);

    rolled = uniform_dist(engine);
}

int __attribute__( (__cdecl__ )) Dice::getRolled(){
    return rolled;
}

void __attribute__( (__cdecl__ )) Player::guess(int a){
    guesses.push_back(a);
}

int __attribute__( (__cdecl__ )) Player::getLastGuess(){
    if (guesses.size() == 0){
        return -1;
    } else {
        return guesses[guesses.size() - 1];
    }
}

int __attribute__( (__cdecl__ )) Player::getNumGuesses(){
    return guesses.size();    
}

void __attribute__( (__cdecl__ )) Player::addWin(){
    score++;
}

int __attribute__( (__cdecl__ )) Player::getNumWins(){
    return score;
}

int main() {

    int guess;
    string cont = "y";

    Dice d;
    Player p;

    cout << "Let's play a game!" << endl;
    cout << "Type '-1' at any time to quit" << endl;
    cout << "I will think of a number 1-100. Try to guess it." << endl;

    d.roll();
    cout << "Hint the number is: " << d.getRolled() << endl;

    while (cont == "y"){

        if (p.getNumWins() >= 1){
            cout << "\n\nLet's play a game!" << endl;
            cout << "Type '-1' at any time to quit" << endl;
            cout << "I will think of a number 1-100. Try to guess it." << endl;
            d.roll();
            cout << "Hint the number is: " << d.getRolled() << endl;
        }

        while (guess != -1)
        {

            cout << "What is your guess: ";
            cin >> guess;

            p.guess(guess);

            cout << endl;

            if (p.getLastGuess() == d.getRolled()) {
                cout << "You guessed it!" << endl;
                cout << "It only took you " << p.getNumGuesses() << " guesses!"<< endl;
                p.addWin();
                break;
            } else if (p.getLastGuess() < d.getRolled()) {
                cout << "Nope! Higher!" << endl;;
            } else if (p.getLastGuess() > d.getRolled()) {
                cout << "Nope! Lower!" << endl;
            }
        }
        cout << "You have won " << p.getNumWins() << " times!" << endl;
        cout << "Type 'y' to play again or 'n' to quit: " << endl;
        cin >> cont;

    }

    return 0;
}
