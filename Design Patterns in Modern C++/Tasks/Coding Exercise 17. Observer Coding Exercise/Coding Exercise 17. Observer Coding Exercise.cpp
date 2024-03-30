//Imagine a game where one or more rats can attack a player.Each individual rat has an attack  value of 1. 
// However, rats attack as a swarm, so each rat's attack  value is equal to the total number of rats in play.
//
//Given that a rat enters play through the constructor and leaves play(dies) via its destructor, 
//please implement the Gameand Rat  classes so that, at any point in the game, the attack  value of a rat is always consistent.

#include <iostream>
#include <vector>
using namespace std;

struct IRat {
  virtual void notify() const = 0;
};

struct Game
{
  vector<IRat*> rats;

  void notify_rats() const {
    for (const auto rat : rats) {
      rat->notify();
    }
  }
};

struct Rat : IRat
{
  Game& game;
  mutable int attack = 1;

  Rat(Game& game) : game(game), attack(game.rats.size() + 1) {
    game.rats.push_back(this); // Add the rat to the game
    game.notify_rats(); // Notify all rats about the new rat
  }

  ~Rat() {
    attack = game.rats.size() - 1; // Update the attack value before rat dies
    game.rats.erase(remove(game.rats.begin(), game.rats.end(), this), game.rats.end()); // Remove the rat from the game
    game.notify_rats(); // Notify all rats about the removed rat
  }

  void notify() const override {
    attack = game.rats.size(); // Update the attack value whenever a rat is notified
  }
};


int main()
{
    std::cout << "Hello World!\n";
}