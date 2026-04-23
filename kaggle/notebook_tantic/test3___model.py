import torch


# 5 构建简单线性模型
class LinearModel(torch.nn.Module):
    def __init__(self, input_dim = 25):
        super(LinearModel, self).__init__()
        self.input_dim = input_dim
        self.Linear1 = torch.nn.Linear(self.input_dim,16)
        self.Linear2 = torch.nn.Linear(16,8)
        self.Linear3 = torch.nn.Linear(8,4)
        self.Linear4 = torch.nn.Linear(4,1)

    def forward(self, x):
        x = torch.nn.functional.relu(self.Linear1(x))
        torch.nn.Dropout(0.25)
        x = torch.nn.functional.relu(self.Linear2(x))
        torch.nn.Dropout(0.25)
        x = torch.nn.functional.relu(self.Linear3(x))
        torch.nn.Dropout(0.25)
        return torch.nn.functional.sigmoid(self.Linear4(x))

