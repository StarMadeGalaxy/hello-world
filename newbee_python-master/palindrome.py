def is_palindrome(word):
    if len(word) <= 1:
        return True
    if word[0] == word[-1]:
        temp_word = word[1:-1]
        return is_palindrome(temp_word)
    else:
        return False


words = ["mama", 'racecar', 'misha', 'топот']

for word in words:
    print(is_palindrome(word))