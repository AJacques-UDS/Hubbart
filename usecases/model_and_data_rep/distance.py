from math import sqrt

# Compute the distance between two 2D points
def compute_distance(a: Point, b: Point) -> float:
    diffX: float = b.x - a.x
    diffY: float = b.y - a.y

    return sqrt(diffX * diffX + diffY * diffY)

# Is run when the script is called by python.
# **Hubbart** must ignore this construct
if __name__ == "__main__":
    a: Point = Point(2, 3)
    b: Point = Point(5, 5)

    print("The distance is {}.".format(compute_distance(a, b)))