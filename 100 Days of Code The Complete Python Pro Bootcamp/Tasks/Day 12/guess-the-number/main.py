import random


def play_game():
    print("Welcome to the Number Guessing Game!")
    print("I'm thinking of a number between 1 and 100")
    difficulty = input("Choose a difficulty. Type 'easy' or 'hard': ").lower()
    number_of_attempts = 0
    number_to_guess = random.randint(1, 100)
    if difficulty == "hard":
        number_of_attempts = 5
    else:
        number_of_attempts = 10

    print(f"You have {number_of_attempts} attempts remaining to guess the number.")
    for _ in range(number_of_attempts):
        number = int(input("Make a guess: "))
        if number > number_to_guess:
            print("Too high.")
        elif number < number_to_guess:
            print("Too low.")
        else:
            print(f"You got it! The answer was {number_to_guess}.")
            break


play_game()
