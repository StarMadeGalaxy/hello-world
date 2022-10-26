voted_list = {}
cache = {           # Collision
    "Vanya": 2,
    "Vanya": 3,
}


def check_voter(name):
    if name in voted_list:
        return "Kick them out !"
    else:
        voted_list[name] = True
        return "Let them vote !"


print(cache["Vanya"])


