import torch.nn as nn
import torch.optim
import torchvision

class LinearModel(nn.Module):
    def __init__(self):
        super(LinearModel, self).__init__()
        self.Linear1 = nn.Linear(8,4)
        self.Linear2 = nn.Linear(4,2)
        self.Linear3 = nn.Linear(2,1)
        self.Simgod = nn.Sigmoid()

    def forward(self,x):
        x = self.Simgod(self.Linear1(x))
        x = self.Simgod(self.Linear2(x))
        x = self.Simgod(self.Linear3(x))
        return x

model = LinearModel()

loss_fn = nn.MSELoss()
optimizer = torch.optim.SGD(params=model.parameters(), lr=0.001)

epochs = 100
for epoch in range(epochs):
    y_pred = model(x)
    loss = loss_fn(y_pred,y)

    optimizer.zero_grad()
    loss.backward()
    optimizer.step()