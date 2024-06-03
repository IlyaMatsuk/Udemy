import random
import sys

choice = int(input("What do you choose? Type 0 for Rock, 1 for Paper or 2 for Scissors.\n"))
if choice >= 3 or choice < 0:
    print("Invalid input. Possible values from 0 to 2.")
    sys.exit(1)

rock = '''
    _______
---'   ____)
      (_____)
      (_____)
      (____)
---.__(___)
'''

paper = '''
    _______
---'   ____)____
          ______)
          _______)
         _______)
---.__________)
'''

scissors = '''
    _______
---'   ____)____
          ______)
       __________)
      (____)
---.__(___)
'''

output = [rock, paper, scissors]

computer_choice = random.randint(0, 2)
print(output[choice])
print("\nComputer chose:\n" + output[computer_choice])

if choice == 0:
    if computer_choice == 0:
        print("It's a draw")
    elif computer_choice == 1:
        print("You lose")
    else:
        print("You win")
elif choice == 1:
    if computer_choice == 0:
        print("You win")
    elif computer_choice == 1:
        print("It's a draw")
    else:
        print("You lose")
else:
    if computer_choice == 0:
        print("You lose")
    elif computer_choice == 1:
        print("You win")
    else:
        print("It's a draw")
