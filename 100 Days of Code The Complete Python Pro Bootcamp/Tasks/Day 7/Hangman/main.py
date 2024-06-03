import random
from replit import clear
from hangman_art import logo, stages
from hangman_words import word_list

print(logo)
chosen_word = random.choice(word_list)

display = ["_"] * len(chosen_word)
curr_stage = len(stages) - 1
while "_" in display and curr_stage > 0:
    guess = input("Guess a letter: ").lower()
    clear()
    for index in range(len(chosen_word)):
        if chosen_word[index] == guess:
            display[index] = chosen_word[index]

    if guess not in chosen_word:
        print(f"You guessed {guess}, that's not in the word. You lose a life.")
        curr_stage -= 1

    print(display)
    print(stages[curr_stage])

if "_" in display:
    print(f"You lose! The word was '{chosen_word}'")
else:
    print("You win!")
