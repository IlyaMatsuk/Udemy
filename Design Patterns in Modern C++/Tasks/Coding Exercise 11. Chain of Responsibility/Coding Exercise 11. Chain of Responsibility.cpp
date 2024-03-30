//Chain of Responsibility Coding Exercise
//You are given a game scenario with classes Goblinand GoblinKing.Please implement the following rules :
//
//A goblin has base 1 attack / 1 defense(1 / 1), a goblin king is 3 / 3.
//When the Goblin King is in play, every other goblin gets + 1 Attack.
//Goblins get + 1 to Defense for every other Goblin in play(a GoblinKing is a Goblin!).
//Example :
//
//  Suppose you have 3 ordinary goblins in play.Each one is a 1 / 3 (1 / 1 + 0 / 2 defense bonus).
//  A goblin king comes into play.Now every ordinary goblin is a 2 / 4 (1 / 1 + 0 / 3 defense bonus from each other + 1 / 0 from goblin king)
//  Meanwhile, the goblin king itself is 3 / 6 (3 / 3 + 0 / 3 defense bonus from other goblins)
//  Here is an example of the kind of test that will be run on the system :
//
//Game game;
//Goblin goblin(game);
//game.creatures.push_back(&goblin);
//ASSERT_EQ(1, goblin.get_attack());
//ASSERT_EQ(1, goblin.get_defense());

#include <iostream>
#include <vector>
using namespace std;

class Game;

class StatQuery {
public:
  enum Statistic { attack, defense };
  Statistic statistic;
  int result;

  StatQuery(Statistic stat) : statistic(stat), result(0) {}
};

class Creature {
protected:
  Game& game;
  int base_attack, base_defense;

public:
  Creature(Game& game, int base_attack, int base_defense) : game(game), base_attack(base_attack), base_defense(base_defense) {}
  virtual int get_attack() const = 0;
  virtual int get_defense() const = 0;
  virtual void query(Creature* source, StatQuery& query) = 0;
};

class Game {
public:
  vector<Creature*> creatures;

  void add_creature(Creature* creature) {
    creatures.push_back(creature);
  }

  void handle_query(Creature* source, StatQuery& query) {
    for (Creature* creature : creatures) {
      creature->query(source, query);
    }
  }
};

class Goblin : public Creature {
public:
  Goblin(Game& game, int base_attack, int base_defense) : Creature(game, base_attack, base_defense) {}

  Goblin(Game& game) : Creature(game, 1, 1) {}

  int get_attack() const override {
    StatQuery query(StatQuery::attack);
    game.handle_query(const_cast<Goblin*>(this), query);
    return query.result;
  }

  int get_defense() const override {
    StatQuery query(StatQuery::defense);
    game.handle_query(const_cast<Goblin*>(this), query);
    return query.result;
  }

  void query(Creature* source, StatQuery& query) override {
    if (source == this) {
      switch (query.statistic) {
      case StatQuery::attack:
        query.result += base_attack;
        break;
      case StatQuery::defense:
        query.result += base_defense;
        break;
      }
    }
    else {
      if (query.statistic == StatQuery::defense) {
        query.result += 1;
      }
    }
  }
};

class GoblinKing : public Goblin {
public:
  GoblinKing(Game& game) : Goblin(game, 3, 3) {}

  void query(Creature* source, StatQuery& query) override {
    if (source != this && query.statistic == StatQuery::attack) {
      query.result += 1;
    }
    else {
      Goblin::query(source, query);
    }
  }
};

int main() {
  Game game;
  Goblin goblin(game);
  game.add_creature(&goblin);
  cout << "Goblin Attack: " << goblin.get_attack() << ", Defense: " << goblin.get_defense() << endl;

  Goblin goblin1(game);
  game.add_creature(&goblin1);
  cout << "Goblin Attack: " << goblin.get_attack() << ", Defense: " << goblin.get_defense() << endl;
  cout << "Goblin1 Attack: " << goblin1.get_attack() << ", Defense: " << goblin1.get_defense() << endl;

  Goblin goblin2(game);
  game.add_creature(&goblin2);
  cout << "Goblin Attack: " << goblin.get_attack() << ", Defense: " << goblin.get_defense() << endl;
  cout << "Goblin2 Attack: " << goblin2.get_attack() << ", Defense: " << goblin2.get_defense() << endl;
  cout << "Goblin1 Attack: " << goblin1.get_attack() << ", Defense: " << goblin1.get_defense() << endl;

  GoblinKing goblinKing(game);
  game.add_creature(&goblinKing);
  cout << "GoblinKing Attack: " << goblinKing.get_attack() << ", Defense: " << goblinKing.get_defense() << endl;
  cout << "Goblin Attack: " << goblin.get_attack() << ", Defense: " << goblin.get_defense() << endl;
  cout << "Goblin2 Attack: " << goblin2.get_attack() << ", Defense: " << goblin2.get_defense() << endl;
  cout << "Goblin1 Attack: " << goblin1.get_attack() << ", Defense: " << goblin1.get_defense() << endl;

  return 0;
}
