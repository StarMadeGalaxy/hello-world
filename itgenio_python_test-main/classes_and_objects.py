import pickle


class Autobus:
    def __init__(self, start_point, final_point, route_number, travel_time):
        self.start_point = start_point
        self.final_point = final_point
        self.route_number = route_number
        self.travel_time = travel_time

    # route number methods
    def set_number(self, new_number):
        print("The route number changed from {} to {}".format(self.route_number, new_number))
        self.route_number = new_number
        return self.route_number

    def get_number(self):
        print("The current route number is", self.route_number)
        return self.route_number

    # starting point methods
    def set_start(self, new_start):
        print("The starting point changed from {} to {}".format(self.start_point, new_start))
        self.start_point = new_start
        return self.start_point

    def get_start(self):
        print("The starting point is", self.start_point)
        return self.start_point

    # final point methods
    def set_final(self, new_final):
        print("The final point changed from {} to {}".format(self.final_point, new_final))
        self.final_point = new_final
        return self.final_point

    def get_final(self):
        print("The destination is", self.final_point)
        return self.final_point

    # travel time methods
    def set_time(self, new_time):
        print("The travel time changed from {} to {}".format(self.travel_time, new_time))
        self.travel_time = new_time
        return self.travel_time

    def get_time(self):
        print("The current travel time is", self.travel_time)
        return self.travel_time

    def get_info(self):
        print("+----------------------------->\n"
              "| Route number: {}\n"
              "| Starting point: {}\n"
              "| Destination point: {}\n"
              "| Travel time: {}\n"
              "+----------------------------->".format(self.route_number, self.start_point,
                                                       self.final_point, self.travel_time))
        return


def create_bus_list(list_bus):
    while True:
        try:
            bus_amount = abs(int(input("Enter number of buses: ")))
        except ValueError:
            print("Input is incorrect. Try again.")
        else:
            for bus_number in range(bus_amount):
                print("\n---------BUS {}---------".format(bus_number + 1))
                start_point = custom_input("str", "Enter start point to add for bus #{}: ".format(bus_number + 1))
                final_point = custom_input("str", "Enter final point to add for bus #{}: ".format(bus_number + 1))
                route_number = custom_input("int", "Enter route number to add for bus #{}: ".format(bus_number + 1))
                travel_time = custom_input("str", "Enter travel time to add for bus #{}: ".format(bus_number + 1))
                list_bus.append(Autobus(start_point, final_point, route_number, travel_time))
            return


def custom_input(param, text):
    if param == "int":
        while True:
            try:
                int_input = int(input(text))
            except ValueError:
                print("Input is incorrect. Try again.")
            else:
                return int_input
    elif param == "str":
        while True:
            try:
                str_input = str(input(text))
            except ValueError:
                print("Input is incorrect. Try again.")
            else:
                return str_input
    else:
        return


def show_autopark(autopark):
    print("\nCurrent autopark.")
    for bus in autopark:
        bus.get_info()
    print("END.\n")
    return


def write_to_file(source_list, filename):
    print("\nWriting data into '", filename, "'...")
    with open(filename, 'wb') as file:
        pickle.dump(source_list, file)
    print("Writing is completed.\n")
    return


def read_from_file(source_file):
    print("\nReading data from '", source_file, "'...")
    with open(source_file, 'rb') as file:
        destination = pickle.load(file)
    print("Reading is completed.\n")
    return destination


def sort_by_number(autopark):
    autopark.sort(key=lambda bus: bus.route_number, reverse=True)
    return


def search_by_point(point, autopark):
    for bus in autopark:
        if bus.final_point == point or bus.start_point == point:
            print("Bus with '", point, "' point is found.")
            bus.get_info()
    return


buses_filename = "buses_file.dat"
bus_list = []

create_bus_list(bus_list)
show_autopark(bus_list)
sort_by_number(bus_list)
write_to_file(bus_list, buses_filename)
bus_list.clear()
bus_list = read_from_file(buses_filename)
search_by_point("Prague", bus_list)




