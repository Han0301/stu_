import pandas as pd    # 数据处理核心库（读取Excel/CSV、数据清洗）
import numpy as np     # 数值计算库（处理数组、数学运算）
import torch           # PyTorch深度学习框架（建模、训练、预测）
import torch.nn as nn  # PyTorch的神经网络模块（搭建模型）

#  scikit-learn：机器学习预处理工具
from sklearn.model_selection import train_test_split  # 拆分训练集/验证集
from sklearn.preprocessing import StandardScaler      # 数据标准化
from tqdm import tqdm

# 固定随机种子（保证结果100%可复现）
torch.manual_seed(42)   # 固定PyTorch的随机数
np.random.seed(42)      # 固定numpy的随机数

train_df = pd.read_csv("../../datasets/titanic/train.csv")
test_df = pd.read_csv("../../datasets/titanic/test.csv")

# 合并训练集+测试集，统一做数据清洗（关键：避免数据泄露）
all_df = pd.concat([train_df, test_df], ignore_index=True)

# 打印数据形状：(训练集行数, 列数) (测试集行数, 列数)
print("原始数据形状：", train_df.shape, test_df.shape)

# ---------------------- 1. 填充 Age 年龄（最优方案） ----------------------
# 按【性别+船舱等级】分组 → 每组的年龄中位数 → 填充该组的缺失值
all_df['Age'] = all_df.groupby(['Sex', 'Pclass'])['Age'].transform(
    lambda x: x.fillna(x.median())
)

# 逐行拆解：
# groupby(['Sex','Pclass'])：把乘客分成 男/女 × 1/2/3等舱 → 共6组
# transform：对每组的Age列执行操作
# lambda x：x代表每组的年龄数据
# fillna(x.median())：用当前组的年龄中位数填充缺失值
# 为什么不用全局中位数？不同性别、船舱的年龄差异极大，分组填充更准确！

# ---------------------- 2. 填充 Embarked 登船港口 ----------------------
# mode()[0]：取出现次数最多的值（众数），填充2个缺失值
all_df['Embarked'] = all_df['Embarked'].fillna(all_df['Embarked'].mode()[0])

# ---------------------- 3. 填充 Fare 票价 ----------------------
# median()：中位数（抗异常值，比如天价票价不会影响结果），填充1个缺失值
all_df['Fare'] = all_df['Fare'].fillna(all_df['Fare'].median())

# ---------------------- 4. 丢弃无用列 ----------------------
drop_cols = ['PassengerId', 'Name', 'Ticket', 'Cabin']
all_df = all_df.drop(drop_cols, axis=1)

# 丢弃原因：
# PassengerId：纯序号，无预测价值
# Name/Ticket：文本无规律，无法提取有效特征
# Cabin：77%缺失，填充也没用，直接删掉

# ---------------------- 检查最终缺失值 ----------------------
print("处理后缺失值统计：\n", all_df.isnull().sum())
# 输出结果：除了测试集的Survived（本来就没有），其余列缺失值=0

# ---------------------- 1. 分类特征转数字 ----------------------
# Sex性别：male=0，female=1（二分类直接映射）
all_df['Sex'] = all_df['Sex'].map({'male': 0, 'female': 1})

# Embarked登船港口：S/C/Q 三分类 → 独热编码（One-Hot）
all_df = pd.get_dummies(all_df, columns=['Embarked'], drop_first=True)
# get_dummies：把1列分类特征转成多列0/1
# drop_first=True：避免冗余（比如3个分类转2列，不影响结果）

# ---------------------- 2. 拆分回训练集/测试集 ----------------------
# 训练集：Survived有值（891行）
train_processed = all_df[all_df['Survived'].notna()]
# 测试集：Survived无值（418行）
test_processed = all_df[all_df['Survived'].isna()]

# ---------------------- 3. 分离特征(X)和标签(y) ----------------------
# X：所有输入特征（去掉Survived列）
X = train_processed.drop('Survived', axis=1).values
# y：标签（生还=1，死亡=0），转成整数类型
y = train_processed['Survived'].values.astype(int)

# 测试集特征（最终预测用）
X_test = test_processed.drop('Survived', axis=1).values

# ---------------------- 4. 拆分训练集/验证集 ----------------------
X_train, X_val, y_train, y_val = train_test_split(
    X, y,
    test_size=0.2,   # 20%数据做验证集，80%训练
    random_state=42, # 固定随机拆分
    stratify=y       # 分层抽样：保证训练/验证集的生还比例一致
)

# ---------------------- 5. 数据标准化（神经网络必须做！） ----------------------
scaler = StandardScaler()
# 训练集：fit_transform（计算均值+方差，再标准化）
X_train = scaler.fit_transform(X_train)
# 验证集/测试集：transform（只用训练集的均值+方差标准化，避免数据泄露）
X_val = scaler.transform(X_val)
X_test = scaler.transform(X_test)

# 标准化作用：把所有特征缩放到 均值=0，方差=1
# 比如Age=20，Fare=100，尺度差太大，神经网络学不动

# ---------------------- 6. 转PyTorch张量（模型只能用张量） ----------------------
# 特征：float32（浮点型，适合计算）
X_train_tensor = torch.tensor(X_train, dtype=torch.float32)
X_val_tensor = torch.tensor(X_val, dtype=torch.float32)
X_test_tensor = torch.tensor(X_test, dtype=torch.float32)

# 标签：long（整型，分类任务专用）
y_train_tensor = torch.tensor(y_train, dtype=torch.long)
y_val_tensor = torch.tensor(y_val, dtype=torch.long)


# 定义模型：继承nn.Module（PyTorch所有模型的父类）
class TitanicModel(nn.Module):
    # 初始化函数：input_dim=输入特征数量（自动计算）
    def __init__(self, input_dim):
        # 调用父类初始化
        super(TitanicModel, self).__init__()

        # Sequential：按顺序搭建神经网络
        self.layers = nn.Sequential(
            # 第一层：输入层 → 64个神经元
            nn.Linear(input_dim, 64),
            nn.ReLU(),  # 激活函数：引入非线性，让模型学复杂规律
            nn.Dropout(0.25),  # 随机失活20%神经元：防止过拟合

            # 第二层：64 → 32个神经元
            nn.Linear(64, 32),
            nn.ReLU(),
            nn.Dropout(0.25),

            # 输出层：32 → 2个神经元（生还/死亡 二分类）
            nn.Linear(32, 2)
        )

    # 前向传播：数据流过网络的过程
    def forward(self, x):
        return self.layers(x)


# 初始化模型
input_dim = X_train.shape[1]  # 输入特征数量（自动获取，不用手动改）
model = TitanicModel(input_dim)
# 打印模型结构
print(model)

# ---------------------- 训练配置 ----------------------
criterion = nn.CrossEntropyLoss()  # 损失函数：二分类专用（自带Softmax）
optimizer = torch.optim.Adam(model.parameters(), lr=0.005)  # 优化器：更新模型参数
epochs = 10000  # 训练轮数：把所有数据训练100次

# 记录训练过程（画图用）
train_losses, val_losses = [], []
train_accs, val_accs = [], []

max_acc = 0.0
save_path = "./best.pt"
early_stop_count = 0
patience = 1500
# ---------------------- 训练循环 ----------------------
for epoch in (tqdm(range(epochs), desc="训练中...", colour="red")):
    # 1. 训练模式（启用Dropout，更新参数）
    model.train()

    # 前向传播：输入数据 → 模型输出预测结果
    y_pred_train = model(X_train_tensor)
    # 计算训练损失：预测值和真实值的误差
    loss_train = criterion(y_pred_train, y_train_tensor)

    # 反向传播 + 优化参数
    optimizer.zero_grad()  # 清空上一轮的梯度（必须做！）
    loss_train.backward()  # 反向传播：计算梯度
    optimizer.step()  # 更新模型参数

    # 计算训练准确率
    _, pred_train = torch.max(y_pred_train, 1)  # 取概率最大的类别（0/1）
    acc_train = (pred_train == y_train_tensor).sum().item() / len(y_train_tensor)

    # 2. 验证模式（关闭Dropout，不更新参数）
    model.eval()
    with torch.no_grad():  # 关闭梯度计算：加快速度，节省内存
        y_pred_val = model(X_val_tensor)
        loss_val = criterion(y_pred_val, y_val_tensor)
        # 计算验证准确率
        _, pred_val = torch.max(y_pred_val, 1)
        acc_val = (pred_val == y_val_tensor).sum().item() / len(y_val_tensor)
        if acc_val > max_acc:
            torch.save(model.state_dict(),save_path)
            max_acc = acc_val
            print(f"epoch: {epoch}, max_acc_val: {acc_val}, saving model")
            early_stop_count = 0
        else:
            early_stop_count += 1

        # if early_stop_count > patience:
        #     print(f"max_acc_val: {acc_val}, early_stop_count = {early_stop_count} > patience = {patience}")
        #     break

    # 保存损失和准确率
    train_losses.append(loss_train.item())
    val_losses.append(loss_val.item())
    train_accs.append(acc_train)
    val_accs.append(acc_val)

    # 每10轮打印结果
    # if (epoch + 1) % 10 == 0:
    #     print(f"Epoch [{epoch + 1}/{epochs}] | "
    #           f"Train Loss: {loss_train:.3f} Acc: {acc_train:.3f} | "
    #           f"Val Loss: {loss_val:.3f} Acc: {acc_val:.3f}")

# ---------------------- 测试集预测 ----------------------
checkpoint = torch.load(save_path)
if "model_state_dict" in checkpoint:
    model_weight = checkpoint["model_state_dict"]
    model.load_state_dict(model_weight)
model.eval()  # 切换到评估模式
with torch.no_grad():  # 关闭梯度
    test_output = model(X_test_tensor)  # 模型输出预测结果
    _, test_pred = torch.max(test_output, 1)  # 转换为0/1（死亡/生还）

# ---------------------- 生成提交文件（Kaggle标准格式） ----------------------
submission = pd.DataFrame({
    'PassengerId': test_df['PassengerId'],  # 必须保留原始乘客ID
    'Survived': test_pred.numpy()           # 模型预测的生还结果
})

# 保存为CSV文件，index=False（不要行号）
submission.to_csv("titanic_submission.csv", index=False)
print("提交文件已生成：titanic_submission.csv")