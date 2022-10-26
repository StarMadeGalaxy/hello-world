# Find the most popular letter


string_to_find_1 = "......HeLlo......"
string_to_find_2 = "String ssss ttAAds TTTTTTT"
string_to_find_3 = "!@#$%^&*(*&^%$#@@#$%^&*DFGBQQQQQQQQqqqrrrrrrrr"
string_to_find_4 = "!@#$%^&*543234%^&*%$#@345677^%$#@#$%^&"
string_to_find_5 = "....пррррривет..."
string_to_find_6 = "....Tschüüüüüüüss!..."


def most_popular_letter(sentence):
    letters = {}                                    # Create dict to store letters and their amount
    sentence_lower = sentence.lower()               # Make all of the characters lowercase (A = a)
    for character in sentence_lower:
        if character.isalpha():                     # Check whether a character is a letter or not
            if character in letters.keys():         # Check whether a character exists in dict or not
                letters[character] += 1             # Increment if a letter is already in dict
            else:
                letters[character] = 1              # A letter encountered => current amount = 1
    if not letters:                                 # If letters is empty => there's no most popular letter
        print("There's no popular letter in", sentence)
        return None
    else:                                           # If there are several most popular letters
        max_amount = max(letters.values())          # Find max value in dict and output values with key
        for letter, amount in letters.items():
            if amount == max_amount:
                print("The most popular letter in '{}' is '{}'".format(sentence_lower, letter))


most_popular_letter(string_to_find_1)
most_popular_letter(string_to_find_2)
most_popular_letter(string_to_find_3)
most_popular_letter(string_to_find_4)
most_popular_letter(string_to_find_5)
most_popular_letter(string_to_find_6)
