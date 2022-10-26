min_temp = 0    # Celsium
max_temp = 300  # Celsium
step = 20


def celsium_to_kelv_fahr(min, max, step):
    minimal = min
    while minimal <= max:
        kelvin = minimal + 273
        fahr = (9 / 5 * minimal) + 32
        print("Celsium: {0}; Fahrenheit: {1}; Kelvin: {2}".format(minimal, fahr, kelvin))
        minimal += step


celsium_to_kelv_fahr(min_temp, max_temp, step)