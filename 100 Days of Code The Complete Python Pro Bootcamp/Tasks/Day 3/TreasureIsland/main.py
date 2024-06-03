print("Welcome to Treasure Island.")
print("Your mission is to find the treasure.")
direction = input("You're at a cross road. Where do you want to go? Type \"left\" or \"right\"\n")
if direction == "left":
    action = input("You come to a lake. There is an island in the middle of the lake. Type \"wait\" to wait for a boat. Type \"swim\" to swim across.\n")
    if action == "wait":
        doorColor = input("You arrive at the island unharmed. There is a house with 3 doors. One red, one yellow and one blue. Which colour do you choose?\n")
        if doorColor == "red":
            print("Burned by fire. Game Over.")
        elif doorColor == "blue":
            print("Eaten by beasts. Game Over.")
        elif doorColor == "yellow":
            print("You win!")
        else:
            print("Game Over!")
    else:
       print("Attacked by trout.Game Over.")
else:
    print("Fall into a hole. Game Over.")
