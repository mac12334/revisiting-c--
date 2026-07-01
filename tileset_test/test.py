col = 3
row = 4
# had to prototype in python real quick
for index in range(12):
    x = index % col
    y = index // col
    print(index, x, y)