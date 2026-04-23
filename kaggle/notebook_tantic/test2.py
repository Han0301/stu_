import pandas as pd
from matplotlib import pyplot as plt
from scipy.stats.mstats import winsorize
import seaborn as sns
from sklearn.preprocessing import MinMaxScaler

train_df = pd.read_csv("../../datasets/titanic/train.csv")
test_df = pd.read_csv("../../datasets/titanic/test.csv")

# 1 使用 .info 加载csv表格的数据集信息, 查看是否有缺少特征的数据
# print(train_df.info())
# print(test_df.info())

# 2 拼接训练集和测试集, 进行数据清洗
all_df = pd.concat([train_df,test_df], ignore_index=True)
isnull_dict = all_df.isnull().sum().to_dict()

# 2.1 查找缺失的数据和对应缺失的数量
"""
缺少:  
key: Age, value: 263
key: Fare, value: 1
key: Cabin, value: 1014
key: Embarked, value: 2
"""
# 找到int/float/float32/float64相关的数字特征列
num_columns = all_df.select_dtypes(include=['number']).columns.to_list()        # 返回一个特征名列表
print(f"num_columns: {num_columns}")

for (key, value) in isnull_dict.items():
    # 进行缩尾
    if key in num_columns and key not in ['PassengerId', 'Survived']:
        all_df[key] = winsorize(all_df[key],[0.03,0.03])
    # 打印缺失数据的数量
    if value > 0:
        print(f"key: {key}, value: {value}")
# print(f"winsorize: {all_df['Fare'].describe()}")

# 对 Age 的处理
age_median = all_df["Age"].median()     # .median() 取到这一列的中位数
print(f"age_median: {age_median}")

all_df["Age"] = all_df["Age"].fillna(age_median)    # .fillna(value)  填充这一列缺失值

isnull_dict2 = all_df.isnull().sum().to_dict()
print(isnull_dict2)

# 对 Embarked 的处理
print(all_df["Embarked"].value_counts())        # value_count() 获得这一列的统计数据, 值和对应该值的数量, 返回的是 panda 的序列(series)
all_df["Embarked"] = all_df["Embarked"].fillna("S")
print(all_df["Embarked"].value_counts())

isnull_dict3 = all_df.isnull().sum().to_dict()
print(isnull_dict3)

# 对 Cabin 的处理
print(all_df["Cabin"].value_counts().to_dict())

# .apply(func) 对改列的每一个元素应用 func 进行变换
all_df["Cabin_"] = all_df["Cabin"].apply(lambda x: x[0] if pd.notnull(x) else "U")      # null 置为 U
Cabin_count = all_df["Cabin_"].value_counts()
Cabin_less_li = Cabin_count[Cabin_count < 10].index.to_list()       # 找到序列中数量较少的直接置为U

all_df["Cabin_"] = all_df["Cabin_"].replace(Cabin_less_li, "U")
print("Cabin_: ")
print(all_df["Cabin_"].value_counts())
print(all_df.info())
all_df = all_df.drop(columns="Cabin")       # drop(columns= ) 按照对应的标签名删除整行
print(all_df.info())

# 3 数据的特征建模
# plt.figure(figsize=(8, 5)) # 设置画布大小
# 语法解释：sns.barplot 绘制条形图
# x='Pclass': 横轴是舱位等级
# y='Survived': 纵轴是存活率的均值
# data=train: 数据源
# sns.barplot(x='Pclass', y='Survived', data=all_df, palette='Reds')        # 可视化
# plt.title('Survival Rate by Passenger Class')
# plt.show()

# 对name的建模
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

# 3. 批量替换，完成二次分类
all_df['Title'] = all_df['Title'].replace(title_map)
print(all_df['Title'].value_counts())

# one-hot编码
categorical_cols = ["Sex", "Embarked", "Cabin_", "Title",'Pclass', "SibSp", "Parch"]

# 执行独热编码（核心代码）
all_df = pd.get_dummies(
    all_df,
    columns=categorical_cols,  # 批量编码所有分类列
    drop_first=True           # 必须加！避免虚拟变量陷阱
)

print(all_df.columns.to_list())

all_df = all_df.drop(columns=["Ticket", "Name"])
print(all_df.info())

# 归一化
scaler = MinMaxScaler()
numeric_cols = ['Age', 'Fare']
all_df[numeric_cols] = scaler.fit_transform(all_df[numeric_cols])
print(all_df["Fare"].value_counts())

print(all_df.info())
print(all_df['Fare'])

# 4 拆回训练集和验证集
train_data = all_df[all_df["Survived"].notna()].copy()
test_data = all_df[all_df["Survived"].isna()].copy()