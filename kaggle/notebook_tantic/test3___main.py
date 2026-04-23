"""
根据test3__ 重新进行特征工程
"""

import pandas as pd
import torch
from sklearn.metrics import f1_score

from test3___feature import pre_feature
from test3___model import LinearModel

train_csv_path = "../../datasets/titanic/train.csv"
test_csv_path = "../../datasets/titanic/test.csv"

train_dataloader,val_dataloader,x_test_tensor, input_shape = pre_feature(train_csv_path, test_csv_path)
print(f"input_shape: {input_shape}")
model = LinearModel(input_dim=input_shape - 1)

adam = torch.optim.Adam(params=model.parameters(),lr=0.005)

loss_fn = torch.nn.BCELoss()

save_path = r"H:\pycharm\learn_\kaggle\notebook\01titanic\best3__.pt"
def train(save_path):

    best_f1 = 0.0
    early_stop_count = 0

    for epoch in range(2000):
        total_loss = 0.0
        model.train()
        for batch_x, batch_y in train_dataloader:
            y_pred = model(batch_x)
            loss = loss_fn(y_pred,batch_y)

            adam.zero_grad()
            loss.backward()
            adam.step()
            total_loss += loss.item()
        # print(f"epoch: {epoch + 1}, total_loss = {total_loss:.2f}")

        model.eval()
        val_loss = 0.0
        all_label = []
        all_pred = []
        with torch.no_grad():
            for batch_x, batch_y in val_dataloader:
                y_pred = model(batch_x)
                loss = loss_fn(y_pred, batch_y)
                val_loss += loss.item()

                pred = (y_pred > 0.5).cpu().numpy().astype(int)
                all_pred.extend(pred)
                all_label.extend(batch_y.cpu().numpy())

        val_f1 = f1_score(all_label,all_pred)
        print(f"epoch: {epoch + 1}, val_loss = {val_loss:.2f}, val_f1 = {val_f1:.4f}")

        if val_f1 > best_f1:
            best_f1 = val_f1
            early_stop_count = 0
            torch.save(model.state_dict(), save_path)
            print(f"saveing model, best_f1 = {val_f1:.4f}")
        else:
            early_stop_count += 1
        if early_stop_count >= 1000 or epoch == 1999:
            print(f"over, best_f1 = {best_f1:.4f}")
            break

train(save_path)

model = LinearModel(input_dim=input_shape - 1)
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