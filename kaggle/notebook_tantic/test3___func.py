
def analyze_feature(df,feature):
    result = df.groupby(feature).agg(
        总人数=("Survived", "count"),
        生还人数=("Survived", "sum"),
        生还率=("Survived", "mean")
    )
    # 格式化生还率为百分比
    result["生还率"] = result["生还率"].apply(lambda x: f"{x:.2%}")
    # 重置索引，让特征值变成普通列
    result = result.reset_index()
    # 重命名列名，更清晰
    result.rename(columns={feature: "特征取值"}, inplace=True)
    return result

def func_Age(x):
    if x <= 18:
        return 1
    elif 18 < x <= 36:
        return 2
    elif 36 < x <= 54:
        return 3
    else:
        return 4

def func_Fare(x):
    if x < 10:
        return 0
    elif 10 < x < 30:
        return 1
    else:
        return 2      # 小费越高, 生还率越高

def func_Cabin(x):
    if x in ["B","D","E"]:
        return 2
    elif x in ["A", "C", "F"]:
        return 1
    else:
        return 0

def func_FamilySize(x):
    if x in [4]:
        return 2
    elif x in [2,3]:
        return 1
    else:
        return 0

def func_Title(x):
    if x in ["Mrs", "Miss", "Noble"]:
        return 2
    elif x in ["Master"]:
        return 1
    else:
        return 0

def func_SibSp(x):
    if x in [1,2]:
        return 2
    elif x in [0]:
        return 1
    else:
        return 0
