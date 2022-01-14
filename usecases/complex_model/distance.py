from math import sqrt

# Represent a 2D points in a cartesian plane
class Point:
    def __init__(self, x: float, y: float):
        self.x: float = x
        self.y: float = y

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