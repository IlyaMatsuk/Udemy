from replit import clear
from art import logo

print(logo)
print("Welcome to the secret auction program.")

continueExecution = True
bids = {}
while continueExecution:
    name = input("What is your name?: ")
    bid = int(input("What is your bid?: "))
    bids[name] = bid

    run = input("Are there any other bidders? Type 'yes' or 'no'.").lower()
    if run == "yes":
        clear()
    else:
        continueExecution = False

winner = ""
max_bid = 0
for key in bids:
    if bids[key] > max_bid:
        max_bid = bids[key]
        winner = key

if winner != "":
    print(f"The winner is {winner} with a bid of ${max_bid}.")
else:
    print("No winner.")