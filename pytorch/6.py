import numpy as np
import torch
from torch.utils.data import DataLoader
from torchvision import datasets
from torchvision import transforms
import matplotlib.pyplot as plt

# ----------------------------------------------------------------set_params
save_path = "./model_pt/minst_best.pt"
batch_size = 64
workers = 4
patience = 12
epochs = 100
# ----------------------------------------------------------------datasets
transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.1307,), (0.3081,))      # 均值和标准差
])

train_datasets = datasets.MNIST(
    root="./datasets/minst",
    train=True,
    transform=transform,
    download=True,
)

test_datasets = datasets.MNIST(
    root="./datasets/minst",
    train=False,
    transform=transform,
    download=True
)

train_loader = DataLoader(
    dataset=train_datasets,
    batch_size=batch_size,
    shuffle=True,
    num_workers=workers
)

test_loader = DataLoader(
    dataset=test_datasets,
    batch_size=batch_size,
    shuffle=False,       # 减少变量, 便于观察
    num_workers =workers
)

# ----------------------------------------------------------------plt
def save_plt(x,y,x_title:str = "x", y_title:str = "y", title: str = "图", save_path: str = None):
    # 1. 数据类型转换（统一转为NumPy数组，兼容列表输入）
    x = np.array(x)
    y = np.array(y)

    # 2. 异常处理：检查x和y长度是否一致
    if len(x) != len(y):
        raise ValueError(f"X轴数据长度（{len(x)}）与Y轴数据长度（{len(y)}）不一致！")

    # 3. 配置中文显示（解决中文/负号显示问题）
    plt.rcParams['font.sans-serif'] = ['SimHei']
    plt.rcParams['axes.unicode_minus'] = False

    plt.figure(figsize=(8,6))

    plt.plot(
        x, y,
        color='#1f77b4',  # 专业配色（蓝色）
        linestyle='-',    # 实线
        linewidth=2,      # 线条宽度
        marker='o',       # 数据点标记（圆圈）
        markersize=4,     # 标记大小
        alpha=0.8         # 透明度（避免线条/标记过浓）
    )

    # 6. 美化图表（标签、标题、网格）
    plt.xlabel(x_title, fontsize=12)
    plt.ylabel(y_title, fontsize=12)
    plt.title(title, fontsize=14, fontweight='bold', pad=10)  # pad：标题与图表的间距
    plt.grid(True, alpha=0.3)  # 显示网格（透明度0.3，不干扰视线）
    plt.tight_layout()  # 自动调整布局，避免标签重叠

    # 7. 保存图片（若指定路径）
    if save_path is not None:
        plt.savefig(
            save_path,
            dpi=300,                # 分辨率（300DPI=印刷级）
            bbox_inches='tight'     # 去除图片周围白边
        )
        print(f"图片已保存至：{save_path}")

# ----------------------------------------------------------------models
class Model(torch.nn.Module):
    def __init__(self):
        super(Model, self).__init__()
        self.l1 = torch.nn.Linear(784,512)
        self.l2 = torch.nn.Linear(512,256)
        self.l3 = torch.nn.Linear(256,128)
        self.l4 = torch.nn.Linear(128,64)
        self.l5 = torch.nn.Linear(64, 10)       # 最终给到10分类

    def forward(self,x):    # 输入 n * 1 * 28 * 28
        x = x.view(-1, 784)     # 降维到1维, -1表示自适应计算, 784列
        # 全连接层导致缺少图像小范围特征
        x = torch.nn.functional.relu(self.l1(x))
        x = torch.nn.functional.relu(self.l2(x))
        x = torch.nn.functional.relu(self.l3(x))
        x = torch.nn.functional.relu(self.l4(x))
        return self.l5(x)

model = Model()

# ----------------------------------------------------------------optimizer and losss_fn
optimizer = torch.optim.SGD(model.parameters(), lr=0.01)
loss_fn = torch.nn.CrossEntropyLoss()       # softmax + NLLloss

# ----------------------------------------------------------------train
# 将每一轮循环封装成函数
def train(epoch):
    running_loss = 0
    for batch_idx, data in enumerate(train_loader,0):
        inputs, targets = data
        y_pred = model(inputs)
        loss = loss_fn(y_pred, targets)
        running_loss += loss.item()
        # if batch_idx % 10 == 0:
        #     print(f"batch_idx: {batch_idx}, loss: {loss}")

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
    print(f"epoch: {epoch}, total_loss = {running_loss}")
    return running_loss

# ----------------------------------------------------------------test
def test():
    total = 0
    correct = 0
    with torch.no_grad():       # 接下来的代码不会在计算梯度
        for data in test_loader:
            images, targets = data
            y_pred = model(images)
            _, predicted = torch.max(y_pred.data, dim=-1)       # _ 取到的最大值的值, predicted表示取到最大值的下标
            total += targets.size(0)
            correct += (predicted == targets).sum().item()
    print(f"total: {total}, correct: {correct}, acc: {correct / total}")
    return correct / total



# ----------------------------------------------------------------other_params
max_acc = 0
early_count = 0
total_loss_li = []
acc_li = []

# ----------------------------------------------------------------main
if __name__ == "__main__":
    for epoch in range(epochs):
        total_loss = train(epoch)
        acc = test()

        total_loss_li.append(total_loss)
        acc_li.append(acc)

        # save model
        if acc > max_acc:
            max_acc = acc
            early_count = 0
            print(f"epoch: {epoch}, now acc: {acc}, save_best_model: {save_path}")
            torch.save(model.state_dict(),save_path)
        else:
            early_count += 1
            print(f"epoch: {epoch}, early_count: {early_count}, now acc: {acc}, max_acc: {max_acc}")
        if early_count > patience or epoch == epochs - 1:       # 训练结束
            save_plt(epoch, total_loss_li, "epoch", "total_loss", "loss with epoch", "./plt/minst_loss_.png")
            save_plt(epoch, acc_li, "epoch", "acc", "acc with epoch", "./plt/minst_acc_.png")
            break