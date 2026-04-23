import pandas as pd
from scipy.stats.mstats import winsorize
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import cross_val_score
from sklearn.ensemble import RandomForestClassifier

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

# 5 构建模型
rf_model = RandomForestClassifier(
    n_estimators=400,      # 100棵树（专家数量）
    max_depth=12,           # 每棵树最大深度（防止过拟合）
    min_samples_split=2,   # 节点最少样本数
    random_state=42,       # 随机种子（复现结果）
    n_jobs=-1              # 使用所有CPU核心并行训练
)

cv_scores = cross_val_score(rf_model, x_tra, y_tra, cv=5, scoring='f1')
print(f"随机森林 5折交叉验证 F1分数: {cv_scores.mean():.4f}")

rf_model.fit(x_tra, y_tra)

test_pred = rf_model.predict(x_tes)

test_df_csv = pd.read_csv("../../datasets/titanic/test.csv")

submission = pd.DataFrame({
    "PassengerId": test_df_csv["PassengerId"],
    "Survived": test_pred
})

submission.to_csv("titanic_rf_submission.csv", index=False)