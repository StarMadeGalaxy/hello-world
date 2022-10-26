width = 400
height = 640


def find_min_square(width, height):
    if width <= 0 or height <= 0:   # Square cannot be exits with these arguments
        return None
    if height > width:
        width, height = height, width
    elif width == height:     # if width equal to height, that means square
        return width, height    # Return size of square
    residue = width - height    # subtract the biggest squares from all area and get width of the residue
    while residue > height:     # subtraction
        residue -= height
    return find_min_square(height, residue)


print(find_min_square(width, height))