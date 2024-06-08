import turtle as tm
import colorgram
import random


def get_rgb_image_colors(image, number_of_colors):
    rgb_colors = []
    for color in colorgram.extract(image, number_of_colors):
        rgb_colors.append((color.rgb.r, color.rgb.g, color.rgb.b))

    return rgb_colors


tm.colormode(255)
screen = tm.Screen()
t = tm.Turtle()
colors = get_rgb_image_colors("download.jpg", 30)
t.speed("fastest")
t.penup()
t.hideturtle()
t.setheading(225)
t.forward(300)
t.setheading(0)
number_of_dots = 100

for dot_count in range(1, number_of_dots + 1):
    t.dot(20, random.choice(colors))
    t.forward(50)

    if dot_count % 10 == 0:
        t.setheading(90)
        t.forward(50)
        t.setheading(180)
        t.forward(500)
        t.setheading(0)

screen.exitonclick()
