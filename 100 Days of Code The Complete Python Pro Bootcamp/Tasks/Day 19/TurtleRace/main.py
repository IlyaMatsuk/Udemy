from turtle import Turtle, Screen
import random


class RaceTurtle:
    def __init__(self, color, x, y):
        self.turtle = Turtle(shape="turtle")
        self.turtle.up()
        self.turtle.color(color)
        self.turtle.goto(x, y)


screen = Screen()
screen.setup(500, 400)
user_bet = screen.textinput(title="Make your bet", prompt="Which will win the race? Enter a color: ")
colors = ["red", "orange", "yellow", "green", "blue", "purple"]

turtles = []
x = -230
y = -100
for color in colors:
    turtles.append(RaceTurtle(color, x, y))
    y += 50

is_race_on = False
if user_bet:
    is_race_on = True

while is_race_on:
    for t in turtles:
        if t.turtle.xcor() > 230:
            is_race_on = False
            winning_color = t.turtle.pencolor()
            if winning_color == user_bet:
                print(f"You've won! The {winning_color} turtle is the winner!")
            else:
                print(f"You've lost! The {winning_color} turtle is the winner!")

        rand_distance = random.randint(0, 10)
        t.turtle.forward(rand_distance)

screen.exitonclick()
