//Template Method Coding Exercise
//Imagine a typical collectible card game which has cards representing creatures.Each creature has two values : Attack and Health.Creatures can fight each other, dealing their Attack damage, thereby reducing their opponent's health.
//
//The class CardGame implements the logic for two creatures fighting one another.However, the exact mechanics of how damage is dealt is different :
//
//TemporaryCardDamage: In some games(e.g., Magic: the Gathering), unless the creature has been killed, its health returns to the original value at the end of combat.
//PermanentCardDamage : In other games(e.g., Hearthstone), health damage persists.
//You are asked to implement classes TemporaryCardDamageGameand PermanentCardDamageGame  that would allow us to simulate combat between creatures.
//
//Some examples :
//
//With temporary damage, creatures 1 / 2 and 1 / 3 can never kill one another.With permanent damage, second creature will win after 2 rounds of combat.
//With either temporary or permanent damage, two 2 / 2 creatures kill one another.

#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
#include <functional>
using namespace std;

struct Creature
{
  int attack, health, baseHealth;
  Creature(int attack, int health) : attack(attack), health(health), baseHealth(health) {}
};

struct CardGame
{
  vector<Creature> creatures;
  function<void()> OnCombatEnds;
  CardGame(const vector<Creature>& creatures) : creatures(creatures) {}

  // return the index of the creature that won (is a live)
  // example:
  // - creature1 alive, creature2 dead, return creature1
  // - creature1 dead, creature2 alive, return creature2
  // - no clear winner: return -1
  int combat(int creature1, int creature2)
  {
    const int n = static_cast<int>(creatures.size());
    if (creature1<0 || creature1>n - 1 || creature2<0 || creature2>n - 1) return -2;

    hit(creatures[creature1], creatures[creature2]);
    hit(creatures[creature2], creatures[creature1]);

    if (OnCombatEnds) OnCombatEnds();

    const int h1 = creatures[creature1].health;
    const int h2 = creatures[creature2].health;

    if (h1 > 0 && h2 <= 0) return creature1;
    if (h2 > 0 && h1 <= 0) return creature2;

    return -1;
  }

  virtual void hit(Creature& attacker, Creature& other)
  {
    other.health -= attacker.attack;
  }


};

struct TemporaryCardDamageGame : CardGame
{

  TemporaryCardDamageGame(const vector<Creature>& _creatures) : CardGame(_creatures)
  {
    OnCombatEnds = [this]()
    {
      for (auto& creature : creatures) if (creature.health > 0) creature.health = creature.baseHealth;
    };
  }
};

struct PermanentCardDamageGame : CardGame
{
  PermanentCardDamageGame(const vector<Creature>& creatures) : CardGame(creatures) {}

};

int main()
{
    std::cout << "Hello World!\n";
}