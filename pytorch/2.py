import torch
from google.protobuf.internal.wire_format import INT64_MAX

x_data = [1.0,2.0,3.0]
y_data = [2.0,4.0,6.0]

w = torch.Tensor([1.0])     # 权重
w.requires_grad = True      # 保留损失对权重的梯度

def forward(x):
    return x*w          # x,w 都是tensor, 进行 tensor和tensor之间的数乘

def loss_fn(x,y_target):
    y_pred = forward(x)
    return (y_pred - y_target) ** 2


for epoch in range(1000):
    for x,y in zip(x_data,y_data):
        loss = loss_fn(x,y)
        loss.backward()     # 反向传播
        last_w_data = w.data

        # 这里的 grad 也是 tensor, 所以直接使用会使下面的计算变成图计算, 所以要取item, 来计算标量, 同理loss 都是 tensor
        w.data = w.data - 0.000001 * w.grad.item()           # 学习率影响准确度
        w.grad.data.zero_()  # 更新完参数后要将梯度清零

        print(f"loss: {loss.item()}, w.grad.item: {w.grad.item()},last_w_data: {last_w_data},  w.data: {w.data}")
