import pandas as pd
import torch
from scipy.stats.mstats import winsorize
from sklearn.preprocessing import MinMaxScaler
from torch.utils.data import TensorDataset, DataLoader
from sklearn.model_selection import train_test_split

from test3___func import func_Age,func_Fare,analyze_feature,func_Cabin,func_FamilySize,func_Title,func_SibSp

def pre_feature(train_csv_path, test_csv_path):
    # 1 预处理
    train_df = pd.read_csv(train_csv_path)
    test_df = pd.read_csv(test_csv_path)
    all_df = pd.concat([train_df,test_df], ignore_index=True)

    # 添加特征
    all_df["FamilySize"] = all_df["SibSp"] + all_df["Parch"] + 1  # 家庭总人数
    all_df = all_df.drop(columns=["SibSp", "Parch"])

    # 1.1 查找缺失数据
    isnull_dict = all_df.isnull().sum().to_dict()                               # 有缺失数据的
    num_column_list = all_df.select_dtypes(include=['number']).columns.to_list()       # 特征为 数字数据的

    # 1.2 对数字数据进行 缩尾处理
    for column in num_column_list:
        if column not in ['PassengerId', 'Survived']:
            all_df[column] = winsorize(all_df[column], [0.03,0.03])

    # 1.3 特征建模
    # Age_boxes
    all_df["Age"] = all_df["Age"].fillna(all_df["Age"].median())        # 填充 中位数
    all_df["Age_boxes"] = all_df["Age"].apply(lambda x: 1 if func_Age(x) ==1 else 0)        # 小于18岁记为 1, 否则为 0
    all_df = all_df.drop(columns="Age")

    # Embarked
    all_df["Embarked"] = all_df["Embarked"].fillna("S")                 # 填充 众数
    all_df["Embarked"] = all_df["Embarked"].apply(lambda x: 1 if x == "C" else 0)           # C 记为1, 否则为0

    # Cabin
    all_df["Cabin"] = all_df["Cabin"].apply(lambda x: x[0] if pd.notnull(x) else "U")       # 单独作为一个 U 类填充
    all_df["Cabin"] = all_df["Cabin"].apply(lambda x: func_Cabin(x))

    # Is_Female
    all_df["Is_Female"] = all_df["Sex"].apply(lambda x: 1 if x == "female" else 0)
    all_df = all_df.drop(columns="Sex")

    # Fare_boxes
    all_df["Fare_boxes"] = all_df["Fare"].apply(lambda x: func_Fare(x))
    all_df = all_df.drop(columns="Fare")

    # FamilySize
    all_df["FamilySize"] = all_df["FamilySize"].apply(lambda x: func_FamilySize(x))

    # Title (对 name 的 处理)
    all_df['Title'] = all_df['Name'].str.extract(' ([A-Za-z]+)\.', expand=False)

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
    all_df["Title"] = all_df["Title"].apply(lambda x: func_Title(x))

    all_df = all_df.drop(columns=["Ticket","Name","PassengerId"])
    print(all_df.info())

    # 2 进行 ont-hot 编码
    categorical_cols = ["Cabin", "Title",'Pclass',"Fare_boxes","FamilySize"]
    all_df = pd.get_dummies(
        all_df,
        columns=categorical_cols,
        drop_first=True
    )

    # 4 数据输入准备
    # 4.1 划分数据集
    all_df = all_df.astype('float32')
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
    train_dataloader = DataLoader(train_dataset, batch_size=16, shuffle=True)
    val_dataloader = DataLoader(val_dataset, batch_size=16, shuffle=True)
    return train_dataloader,val_dataloader,x_test_tensor, tra_df.shape[1]