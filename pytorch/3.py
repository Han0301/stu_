import torch
from google.protobuf.internal.wire_format import INT64_MAX

# 生成的二次函数：y = 6.49x² + 1.39x + 13.05

x_min = -1000.0
x_max = 1000.0
num_points = 300  # 固定生成300个点
x_data = torch.linspace(x_min, x_max, num_points).round(decimals=2)

# 计算对应的y，确保和x维度完全一致
y_data = (6.49 * x_data**2 + 1.39 * x_data + 13.05).round(decimals=2)
x_mean, x_std = x_data.mean(), x_data.std()
y_mean, y_std = y_data.mean(), y_data.std()
x_norm = (x_data - x_mean) / x_std
y_norm = (y_data - y_mean) / y_std

w1 = torch.Tensor([1])
w2 = torch.Tensor([1])
b1 = torch.Tensor([1])
w1.requires_grad = True
w2.requires_grad = True
b1.requires_grad = True

def forward(x):
    return w1 * (x ** 2) + w2 * x + b1

def loss_fn(x, y_target):
    y_pred = forward(x)
    return torch.mean((y_pred - y_target) ** 2)

learning_rate = 0.00000000000001
no_imporve = 0

for i in range(30000):

    loss = loss_fn(x_data, y_data)
    loss.backward()

    with torch.no_grad():
        w1.data = w1.data - learning_rate * w1.grad.item()
        w2.data = w2.data - learning_rate* 120000 * w2.grad.item()
        b1.data = b1.data - learning_rate* 1500000 * b1.grad.item()

        w1.grad.zero_()
        w2.grad.zero_()
        b1.grad.zero_()

        print(f"epoch: {i + 1}, loss: {loss.item()}, w1: {w1.data.item()}, w2: {w2.data.item()}, b1: {b1.data.item()}")