### 1.all_df = Pandas 的 **DataFrame** 二维表格对象

    行：所有乘客（训练集 891 人 + 测试集 418 人 = 1309 人）
    
    列：所有特征（PassengerId, Survived, Pclass, Name, Sex, Age...
    
    作用：统一清洗训练集 + 测试集（避免数据不一致）

### 2. panda对表格的常见预处理
```python
#用法:
import pandas as pd
# 1 读取表格
train_df = pd.read_csv("../../datasets/titanic/train.csv")
test_df = pd.read_csv("../../datasets/titanic/test.csv")

# 2 特征名列表和对应的数据类型+缺失值
print(train_df.info())      
print(test_df.info())

# 3 提取统计数据
all_df = pd.concat([train_df,test_df], ignore_index=True)
print(all_df.shape)     # 打印形状, (1309, 12)
print(all_df.columns.tolist())      # 返回一个特征名列表
print(all_df.isnull().sum())        #表示特征名和对应的缺少数量
print(all_df['Fare'].describe())    # 查看某一类的数学统计信息
isnull_dict = all_df.isnull().sum().to_dict()     # 返回一个字典, 表示特征名和对应的缺少数量
#  查找缺失的数据和对应缺失的数量
for (key, value) in isnull_dict.items():
    if value > 0:
        print(f"key: {key}, value: {value}")
        
# 自动筛选所有数值列 (int/float/float32/float64 全部匹配)
numeric_columns = all_df.select_dtypes(include=['number']).columns.tolist()

# 4 提取行列的信息
row_100 = all_df.iloc[100]      # 提取 第100行 的所有数据
Fare_data = all_df["Fare"].to_list()    # 提取"Fare"整列的数据

# 格式：按【特征名】筛选【满足条件的所有行】
# all_df[ all_df['特征名'] == 条件 ]
female_rows = all_df[ all_df['Sex'] == 'female' ]
pclass1_rows = all_df[ all_df['Pclass'] == 1 ]
# 多个条件用 & 连接，每个条件加括号
filter_rows = all_df[ (all_df['Sex']=='female') & (all_df['Pclass']==1) & (all_df['Survived']==1) ]

# 5 拆回训练集和验证集,根据目标标签的是否存在划分回去
train_data = all_df[all_df["Survived"].notna()]
test_data = all_df[all_df["Survived"].isna()]
```
### 3. 对异常极大值和极小值的处理: 缩尾处理
- 缩尾处理（Winsorizing，温莎化）：把数据中超出正常范围的极端异常值，不删除，而是替换成指定分位数的边界值。

    极端小值 → 替换为「下界分位数」

    极端大值 → 替换为「上界分位数」
- 应用场景: 

    - Fare **有严重异常值**：最大值 512，均值仅 33，极端值会让神经网络训练跑偏
    
    - **数据量极小**（总共 1309 行）：删除异常值 = 丢失关键信息；
    
    - **标准化无效**：标准化只能缩放尺度，无法消除极端值的影响；

  - 核心原理
1. 关键参数：limits=[a, b]
   这是缩尾最重要的参数，决定截断多少比例的极端值：

   第一个数 a：下端截断比例（把最小的 a% 数据替换为下界）

   第二个数 b：上端截断比例（把最大的 b% 数据替换为上界）

   你代码里的 limits=[0.01, 0.01]= 截断 最小 1% + 最大 1% 的极端值= 保留中间 98% 的正常数据

2. 计算逻辑（自动完成，不用手算）

    对数据排序
    找到 1% 分位数（下界） 和 99% 分位数（上界）
    
    所有 < 下界的值 → 替换为下界
    
    所有 > 上界的值 → 替换为上界
3. 示例
```python
all_df['Fare'] = winsorize(
    all_df['Fare'],    # 要处理的特征：票价
    limits=[0.01, 0.01], # 上下各截断1%
    inclusive=(True, True), # 包含边界值（默认即可）
    axis=None          # 一维数据处理
)
```

### 4. 对string 特征的建模
---
    在机器学习和 PyTorch 建模中，字符串（string / 文本）不能直接输入模型，必须转换成数值型特征
---
