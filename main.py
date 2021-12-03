import numpy as np
import matplotlib.pyplot as plt


colors = ['r', 'g', 'b', 'c', 'm', 'y', 'k', 'bisque', 'purple', 'lime', 'lightcoral', 'darkgrey',
          'darkgreen', 'yellow', 'orange', 'goldenrod', 'dodgerblue', 'darkmagenta', 'hotpink', 'cyan']

if __name__ == '__main__':
    lines = []
    with open('data1.txt', 'r') as f:
        lines = f.readlines()

    matrix = []
    lst = []
    minn = 1000000000
    for line in lines:
        num = int(line)
        if (num == -1):
            matrix.append(lst)
            lst = []
            minn = 1000000000
        else:
            if (num < minn):
                minn = num
            lst.append(minn)
    i = 0
    indexes = np.linspace(1, len(matrix[0]), len(matrix[0]))
    plt.figure()
    plt.xlabel("Iterations")
    plt.ylabel("Cumulative minimums")
    for arr in matrix:
        plt.loglog(indexes, arr, colors[i])
        i += 1
    plt.figure()
    plt.xlabel("Iterations")
    plt.ylabel("AVERAGE Cumulative minimums")
    lst = []
    for i in range(len(matrix[0])):
        avg = 0.0
        for arr in matrix:
            avg += arr[i]
        avg = float(1.0 * avg / len(matrix))
        lst.append(avg)
    plt.loglog(indexes, lst)
    plt.show()