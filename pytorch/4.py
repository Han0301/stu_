import torch

class LinearModel(torch.nn.Module):
    def __init__(self):
        super(LinearModel, self).__init__()
        self.Linear = torch.nn.Linear(1,1)
    def forward(self,x):
        y_pred = self.Linear(x)
        return y_pred
model = LinearModel()
