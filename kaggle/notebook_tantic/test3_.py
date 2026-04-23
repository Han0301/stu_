"""
线性模型, 输出为1
"""
import pandas as pd
import torch
from scipy.stats.mstats import winsorize
from sklearn.metrics import f1_score
from sklearn.preprocessing import MinMaxScaler
from torch.utils.data import TensorDataset, DataLoader
from sklearn.model_selection import train_test_split

# 1 预处理
train_df = pd.read_csv("../../datasets/titanic/train.csv")
test_df = pd.read_csv("../../datasets/titanic/test.csv")
all_df = pd.concat([train_df,test_df], ignore_index=True)

# 1.1 查找缺失数据
isnull_dict = all_df.isnull().sum().to_dict()                               # 有缺失数据的
num_column_list = all_df.select_dtypes(include=['number']).columns.to_list()       # 特征为 数字数据的

# 1.2 对数字数据进行 缩尾处理
for column in num_column_list:
    if column not in ['PassengerId', 'Survived']:
        all_df[column] = winsorize(all_df[column], [0.03,0.03])

# 1.3 对缺失值的处理
all_df["Age"] = all_df["Age"].fillna(all_df["Age"].median())        # 填充 中位数
all_df["Embarked"] = all_df["Embarked"].fillna("S")                 # 填充 众数

all_df["Cabin"] = all_df["Cabin"].apply(lambda x: x[0] if pd.notnull(x) else "U")       # 单独作为一个 U 类填充
Cabin_seque = all_df["Cabin"].value_counts()
Cabin_less_column = Cabin_seque[Cabin_seque < 10].index.to_list()
all_df["Cabin"] = all_df["Cabin"].replace(Cabin_less_column, "U")       # 将数量过少的置成 U

# 1.4 对 name 的 处理
all_df['Title'] = all_df['Name'].str.extract(' ([A-Za-z]+)\.', expand=False)
print(all_df['Title'].value_counts())

title_map = {
    # 小众女性头衔 → 合并到标准女性头衔
    'Mlle': 'Miss',
    'Ms': 'Mrs',
    'Mme': 'Mrs',

    # 职业/军官/公职 → 合并为 Officer
    'Rev': 'Officer',
    'Dr': 'Officer',
    'Col': 'Officer',
    'Major': 'Officer',
    'Capt': 'Officer',

    # 贵族头衔 → 合并为 Noble
    'Lady': 'Noble',
    'Sir': 'Noble',
    'Countess': 'Noble',
    'Jonkheer': 'Noble',
    'Don': 'Noble',
    'Dona': 'Noble'
}
all_df["Title"] = all_df["Title"].replace(title_map)

all_df = all_df.drop(columns=["Ticket","Name","PassengerId"])

# 2 进行 ont-hot 编码
categorical_cols = ["Sex", "Embarked", "Cabin", "Title",'Pclass', "SibSp", "Parch"]
all_df = pd.get_dummies(
    all_df,
    columns=categorical_cols,
    drop_first=True
)

# 3 归一化操作
scaler = MinMaxScaler()
scaler_columns = ["Age", "Fare"]
all_df[scaler_columns] = scaler.fit_transform(all_df[scaler_columns])
all_df = all_df.astype('float32')       # 转成 float32 用于神经网络输入
print(all_df.info())

# 4 数据输入准备
# 4.1 划分数据集
tra_df = all_df[ all_df["Survived"].notna()]
tes_df = all_df[ all_df["Survived"].isna()]

# 4.2 划分特征和标签
x_tra = tra_df.drop(columns='Survived').values
y_tra = tra_df['Survived'].values
x_tes = tes_df.drop(columns='Survived').values

x_train, x_val, y_train, y_val = train_test_split(
    x_tra, y_tra, test_size=0.2, random_state=42, stratify=y_tra
)


# 4.3 转张量
x_train_tensor = torch.tensor(x_train, dtype=torch.float32)
y_train_tensor = torch.tensor(y_train, dtype=torch.float32).view(-1,1)
x_val_tensor = torch.tensor(x_val, dtype=torch.float32)
y_val_tensor = torch.tensor(y_val, dtype=torch.float32).view(-1,1)
x_test_tensor = torch.tensor(x_tes, dtype=torch.float32)

# 4.4 构建数据集
train_dataset = TensorDataset(x_train_tensor,y_train_tensor)
val_dataset = TensorDataset(x_val_tensor,y_val_tensor)
train_dataloader = DataLoader(train_dataset, batch_size=32, shuffle=True)
val_dataloader = DataLoader(val_dataset, batch_size=32, shuffle=True)

# 5 构建简单线性模型
class LinearModel(torch.nn.Module):
    def __init__(self, input_dim = 23):
        super(LinearModel, self).__init__()
        self.input_dim = input_dim
        self.Linear1 = torch.nn.Linear(23,128)
        self.Linear2 = torch.nn.Linear(128,64)
        self.Linear3 = torch.nn.Linear(64,16)
        self.Linear4 = torch.nn.Linear(16,4)
        self.Linear5 = torch.nn.Linear(4,1)

    def forward(self, x):
        x = self.Linear1(x)
        x = self.Linear2(x)
        x = torch.nn.functional.relu(self.Linear3(x))
        x = self.Linear4(x)
        return torch.nn.functional.sigmoid(self.Linear5(x))

model = LinearModel()

adam = torch.optim.Adam(params=model.parameters(),lr=0.005)

loss_fn = torch.nn.BCELoss()

best_f1 = 0.0
early_stop_count = 0
save_path = r"H:\pycharm\learn_\kaggle\notebook\01titanic\best3_.pt"
# for epoch in range(2000):
#
#     total_loss = 0.0
#     model.train()
#     for batch_x, batch_y in train_dataloader:
#         y_pred = model(batch_x)
#         loss = loss_fn(y_pred,batch_y)
#
#         adam.zero_grad()
#         loss.backward()
#         adam.step()
#         total_loss += loss.item()
#     # print(f"epoch: {epoch + 1}, total_loss = {total_loss:.2f}")
#
#     model.eval()
#     val_loss = 0.0
#     all_label = []
#     all_pred = []
#     with torch.no_grad():
#         for batch_x, batch_y in val_dataloader:
#             y_pred = model(batch_x)
#             loss = loss_fn(y_pred, batch_y)
#             val_loss += loss.item()
#
#             pred = (y_pred > 0.5).cpu().numpy().astype(int)
#             all_pred.extend(pred)
#             all_label.extend(batch_y.cpu().numpy())
#
#     val_f1 = f1_score(all_label,all_pred)
#     print(f"epoch: {epoch + 1}, val_loss = {val_loss:.2f}, val_f1 = {val_f1:.4f}")
#
#     if val_f1 > best_f1:
#         best_f1 = val_f1
#         early_stop_count = 0
#         torch.save(model.state_dict(), save_path)
#         print(f"saveing model, best_f1 = {val_f1:.4f}")
#     else:
#         early_stop_count += 1
#     if early_stop_count >= 1000 or epoch == 1999:
#         print(f"over, best_f1 = {best_f1:.4f}")
#         break


model = LinearModel()
# 2. 加载保存的最优模型权重
model.load_state_dict(torch.load(save_path))
# 3. 切换为评估模式，关闭梯度计算
model.eval()

# 4. 测试集推理（预测生存结果）
with torch.no_grad():
    test_output = model(x_test_tensor)
    # 获取预测类别 (0/1)
    test_predictions = (test_output > 0.5).cpu().numpy().astype(int).flatten()

# 5. 读取原始测试集，获取 PassengerId（预处理时删掉了，必须重新读）
test_df_raw = pd.read_csv("../../datasets/titanic/test.csv")
# 6. 构建提交表格（Kaggle要求：两列 PassengerId, Survived）
submission = pd.DataFrame({
    "PassengerId": test_df_raw["PassengerId"],
    "Survived": test_predictions
})

# 7. 保存为CSV文件（无索引，直接提交）
submission.to_csv("titanic_submission_.csv", index=False)
print("✅ 提交表格已生成！文件名为：titanic_submission.csv")
print(submission.head())  # 打印前5行查看格式