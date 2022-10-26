from copy import deepcopy


database = {
    "Jane": ['chemistry', 'astronomy', 'physics'],
    "Jonathan": ['math', 'programming', 'physics'],
    "John": ['math', 'astronomy', 'physics']
}


def sort_database(unsorted):
    sorted = {}
    for index in range(len(unsorted)):
        max_key = max(unsorted.keys())
        sorted[max_key] = unsorted[max_key]
        del unsorted[max_key]
    database = sorted
    return sorted


def show_all(database):
    database_sorted = sort_database(deepcopy(database))
    for record in database_sorted.items():
        print(record)
    return


def students_for_sub(student):
    for name in database.keys():
        if name == student:
            print(database[student])
            return database[student]
    print("There are no students with this name.")
    return None


def sub_for_students(subject):
    students_list = []
    for name, subjects in database.items():
        for thing in subjects:
            if thing == subject:
                students_list.append(name)

    if not len(students_list) == 0:
        print(students_list)
        return students_list
    else:
        print('There are no matching students.')
        return None


show_all(database)
students_for_sub("Jane")
students_for_sub("Jack")
sub_for_students("math")
sub_for_students("astronomy")
sub_for_students("biology")
