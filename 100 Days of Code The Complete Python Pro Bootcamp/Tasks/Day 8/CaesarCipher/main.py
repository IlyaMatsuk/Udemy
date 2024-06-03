from art import logo

alphabet = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
            'v', 'w', 'x', 'y', 'z']

print(logo)


def caesar(text, shift, direction):
    msg = ""
    for char in text:
        if char.isalpha():
            alphabet_index = 0
            if direction == "decode":
                alphabet_index = alphabet.index(char) - shift
            elif direction == "encode":
                alphabet_index = (alphabet.index(char) + shift) % len(alphabet)
            msg += alphabet[alphabet_index]
        else:
            msg += char

    print(f"The {direction}d text is {msg}")


run = "yes"
while run == "yes":
    direction = input("Type 'encode' to encrypt, type 'decode' to decrypt:\n")
    text = input("Type your message:\n").lower()
    shift = int(input("Type the shift number:\n"))

    caesar(text, shift, direction)

    run = input("Type 'yes' if you want to go. Otherwise type 'no'.\n")

