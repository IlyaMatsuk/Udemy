import random
from art import logo, vs
from game_data import data


def check_input(choice):
    if choice != 'A' and choice != 'B':
        raise RuntimeError("Invalid input. Must be 'A' or 'B'.")

current_score = 0
while True:
    print(logo)
    if current_score > 0:
        print(f"You're right! Current score: {current_score}")

    a = random.choice(data)
    b = random.choice(data)
    while a == b:
        b = random.choice(data)

    print("Compare A: {}, {}, from {}.".format(a["name"], a["description"], a["country"]))
    print("Against B: {}, {}, from {}.".format(b["name"], b["description"], b["country"]))
    print(vs)
    answer = input("Who has more followers? Type 'A' or 'B': ")
    print(answer)
    check_input(answer)
    if a["follower_count"] > b["follower_count"] and answer == 'A':
        current_score += 1
    elif b["follower_count"] > a["follower_count"] and answer == 'B':
        current_score += 1
    else:
        print(f"Sorry, that's wrong. Final score: {current_score}")
        break
