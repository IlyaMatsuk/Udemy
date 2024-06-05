MENU = {
    "espresso": {
        "ingredients": {
            "water": 50,
            "coffee": 18,
        },
        "cost": 1.5,
    },
    "latte": {
        "ingredients": {
            "water": 200,
            "milk": 150,
            "coffee": 24,
        },
        "cost": 2.5,
    },
    "cappuccino": {
        "ingredients": {
            "water": 250,
            "milk": 100,
            "coffee": 24,
        },
        "cost": 3.0,
    }
}

resources = {
    "water": 300,
    "milk": 200,
    "coffee": 100,
}

coin_types = {
    "quarters": 0.25,
    "dimes": 0.10,
    "nickles": 0.05,
    "pennies": 0.01
}


def do_report(money, resource):
    print(f"Water: {resource['water']}ml\n"
          f"Milk: {resource['milk']}ml\n"
          f"Coffee: {resource['coffee']}g\n"
          f"Money: ${money}")


def insert_coins():
    money = 0.0
    for key, value in coin_types.items():
        money += float(input(f"How many {key}?: ")) * value
    return money


def is_enough_resources(resource, coffee):
    for ingredient, amount in coffee["ingredients"].items():
        if resource[ingredient] < amount:
            print(f"Sorry there is not enough {ingredient}.")
            return False
    return True


def update_resources(resource, coffee):
    for ingredient, amount in coffee["ingredients"].items():
        resource[ingredient] -= amount

    return resource


def main():
    resource = resources
    money = 0.0
    while True:
        choice = input("What would you like? (espresso/latte/cappuccino): ")
        if choice == "report":
            do_report(money, resource)
        else:
            if choice != "espresso" and choice != "latte" and choice != "cappuccino":
                print(f"Unknown coffee type '{choice}'.")
                continue

            coffee = MENU[choice]
            if not is_enough_resources(resource, coffee):
                continue

            if money < coffee["cost"]:
                print("Please insert coins.")
                money = insert_coins()
                if money < coffee["cost"]:
                    print(f"Sorry that's not enough money. Money refunded.")
                    continue

            resource = update_resources(resource, coffee)
            money = round(money - coffee["cost"], 2)
            print(f"Here is ${money} in change.")
            print("Here is your latter. Enjoy!")


main()
