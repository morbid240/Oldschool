##Final Project CECS 381
##Malcolm Roddy

import numpy as np
import matplotlib.pyplot as plt


# plot and print dict with year as key, values from STD
# mean and probability
def output(pairs, ylab):
    print(pairs)
    # plots graph of dict for std deviation and mean
    year = list(pairs.keys())
    values = list(pairs.values())

    fig, ax = plt.subplots()
    ax.bar(year, values)
    ax.xaxis.set_major_locator(plt.MaxNLocator(5))
    ax.set_ylabel(ylab)
    ax.set_xlabel('year')
    plt.show()


# calculate mean from raw data
def mean(data):
    means = {}  # dict to load from csv
    for i in np.unique(data[:, 0]):
        tmp = data[np.where(data[:, 0] == i)]
        means[i] = np.mean(tmp[:, 1])
    output(means, 'mean price')


# calculate STD from raw data
def std(data):
    stds = {} # dict to load from csv
    for i in np.unique(data[:, 0]):
        tmp = data[np.where(data[:, 0] == i)]
        stds[i] = np.std(tmp[:, 1])
    output(stds, 'STD')


# calc probability of total houses sold between 200,000 and 300,000
# to number each year sold
def prb(data):
    sale_range = 0
    prbs = {}

    sale_range_data = data[np.where((200000 <= data[:, 1]) & (data[:, 1] <= 300000))]
    sale_range = np.shape(sale_range_data)[0]
    for i in np.unique(data[:, 0]):
        tmp = data[np.where(data[:, 0] == i)]
        sold_per_yr = np.shape(tmp)[0]  # total rows is total houses in that year
        prbs[i] = sale_range/sold_per_yr
    output(prbs, 'prb')


def main():
    # csv into 2d array then sort by year
    data = np.genfromtxt("Sales_01_20.csv", dtype='int', delimiter=',', skip_header=1)
    data = data[data[:, 0].argsort()]
    # plot std
    std(data)
    # plot mean
    mean(data)
    # plot probability
    prb(data)


if __name__ == "__main__":
    main()
