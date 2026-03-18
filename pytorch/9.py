import numpy as np
import torch
from torch.utils.data import DataLoader
from torchvision import datasets
from torchvision import transforms
import matplotlib.pyplot as plt
import torch.nn.functional as F

# ----------------------------------------------------------------set_params
save_path = "./model_pt/minst_best9.pt"
batch_size = 64
workers = 6
patience = 15
epochs = 100

device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
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

class InceptionA(torch.nn.Module):
    def __init__(self,in_channels):
        super(InceptionA,self).__init__()
        # 分支1
        self.branch_pool = torch.nn.Conv2d(in_channels=in_channels, out_channels=24,kernel_size=1)
        #分支2
        self.branch_conv1x1 = torch.nn.Conv2d(in_channels=in_channels,out_channels=16,kernel_size=1)
        #分支3
        self.branch_3conv1x1 = torch.nn.Conv2d(in_channels=in_channels, out_channels=16, kernel_size=1)
        self.branch_conv5x5 = torch.nn.Conv2d(in_channels=16, out_channels=24, kernel_size=5)
        #分支4
        self.branch_4conv1x1 = torch.nn.Conv2d(in_channels=in_channels, out_channels=16, kernel_size=1)
        self.branch_1conv3x3 = torch.nn.Conv2d(in_channels=16,out_channels=24,kernel_size=3, padding=1)
        self.branch_2conv3x3 = torch.nn.Conv2d(in_channels=24,out_channels=24,kernel_size=3, padding=1)

    def forward(self,x):
        #分支1
        branch_pool1 = F.avg_pool2d(x,kernel_size=3,padding=1,stride=1)
        branch_pool1 = self.branch_pool(branch_pool1)
        #分支2
        branch_pool2 = self.branch_conv1x1(x)
        #分支3
        branch_pool3 = self.branch_3conv1x1(x)
        branch_pool3 = self.branch_conv5x5(branch_pool3)
        #分支4
        branch_pool4 = self.branch_4conv1x1(x)
        branch_pool4 = self.branch_1conv3x3(branch_pool4)
        branch_pool4 = self.branch_2conv3x3(branch_pool4)
        # 接下来按照C通道进行拼接
        outputs = [branch_pool1,branch_pool2,branch_pool3,branch_pool4]     # C: 24*3+16*1 = 88
        return torch.cat(outputs,dim=1)     # 使用cat 进行拼接, dim=1表示C通道, =0 表示B通道

class Model(torch.nn.Module):
    def __init__(self):
        super(Model,self).__init__()
        self.conv1 = torch.nn.Conv2d(in_channels=1,out_channels=10,kernel_size=5)
        self.conv2 = torch.nn.Conv2d(in_channels=88,out_channels=20,kernel_size=5)

        self.InceptionA1 = InceptionA(in_channels=10)
        self.InceptionA2 = InceptionA(in_channels=20)

        self.max_pool = torch.nn.MaxPool2d(kernel_size=2)
        self.linear = torch.nn.Linear(1408,10)

    def forward(self,x):
        batch_size = x.size(0)                      # b*1*28*28
        x = F.relu(self.max_pool(self.conv1(x)))    # b*10*24*24 -> b*10*12*12
        x = self.InceptionA1(x)                     #
        x = F.relu(self.max_pool(self.conv2(x)))
        x = self.InceptionA2(x)
        x = x.view(batch_size, -1)
        x = self.linear(x)
        return x

conv_model = Model()

optimizer = torch.optim.SGD(params=conv_model.parameters(),lr=0.01)
loss_fn = torch.nn.CrossEntropyLoss()

def train():
    total_loss = 0
    for batch_idx, data in enumerate(train_loader,0):
        images,targets = data
        images, targets = images.to(device),targets.to(device)
        y_pred = conv_model(images)
        loss = loss_fn(y_pred, targets)
        total_loss += loss.item()

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
    print(f"epoch: {epoch}, loss: {total_loss}")
    return total_loss

def test():
    acc = 0
    total = 0
    for batch_idx, data in enumerate(test_loader,0):
        with torch.no_grad():
            images, targets = data
            images, targets = images.to(device), targets.to(device)
            y_pred = conv_model(images)
            _, pred = torch.max(y_pred.data,dim=-1)
            total += targets.size(0)
            acc += (pred == targets).sum().item()
    print(f"epoch: {epoch}, acc: {acc}, total: {total}, acc_rate: {acc/total}")
    return acc/total

max_acc = 0
early_count = 0
epochs_li = []
total_loss_li = []
acc_li = []


conv_model.to(device)

if __name__ == "__main__":
    for epoch in range(epochs):
        loss = train()
        acc_rate = test()

        total_loss_li.append(loss)
        acc_li.append(acc_rate)
        epochs_li.append(epoch)

        if acc_rate > max_acc:
            max_acc = acc_rate
            torch.save(conv_model.state_dict(),save_path)
            print("saving model")
            early_count = 0
        else:
            early_count += 1

        save_plt(epochs_li, total_loss_li, "epoch", "total_loss", "loss with epoch", "./plt/minst_loss9_.png")
        save_plt(epochs_li, acc_li, "epoch", "acc", "acc with epoch", "./plt/minst_acc9_.png")

        if early_count >= patience or epoch == epochs - 1:
            print("early stopping, train over")
            break