import re
import matplotlib.pyplot as plt

def read_points_from_file(filename):
    points = []
    with open(filename, "r") as f:
        for line in f:
            #get x and y
            matches = re.findall(r"\(([-\d\.]+),\s*([-\d\.]+)\)", line)
            row = [(float(x), float(y)) for x, y in matches]
            points.extend(row)
    return points

if __name__ == "__main__":
    file_path = "cmake-build-debug/transformed-matrix.txt"  

    pts = read_points_from_file(file_path)

    xs, ys = zip(*pts)  
    plt.scatter(xs, ys, marker=".")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.title("Matrix points")
    plt.grid(True)
    plt.show()