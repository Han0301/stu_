import numpy as np

x_data = [1.0,2.0,3.0]
y_data = [2.0,4.0,6.0]

def forward(x):
    return x * w

def loss(x,y):
    y_pred = forward(x)
    return (y - y_pred) ** 2

w_list = []
mse_loss = []

for w in np.arange(0.0,4.1,0.1):        # 穷举法
    print("w = ", w)
    total_loss = 0
    for x, y in zip(x_data,y_data):
        y_pred = forward(x)
        total_loss += loss(x,y)
    print("MSE_loss: ", total_loss / 3)
