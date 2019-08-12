import torch
import matplotlib.pyplot as plt
import time

start = time.time()

torch.manual_seed(0)

class RegressionNet(torch.nn.Module):
    def __init__(self, hidden0):
        super(RegressionNet, self).__init__()
        self.fc1 = torch.nn.Linear(1, hidden0)
        self.act1 = torch.nn.Softmax(dim = 1)
        self.fc2 = torch.nn.Linear(hidden0, 1)

    def forward(self, x):
        x = self.fc1(x)
        x = self.act1(x)
        x = self.fc2(x)
        return x


net = RegressionNet(30)
#130,

def target_function(x):
    return 2**x * torch.sin(2**-x)

# ------Dataset preparation start--------:
x_train =  torch.linspace(-10, 5, 100)
y_train = target_function(x_train)
noise = torch.randn(y_train.shape) / 20.
y_train = y_train + noise
x_train.unsqueeze_(1)
y_train.unsqueeze_(1)

x_validation = torch.linspace(-10, 5, 1000)
y_validation = target_function(x_validation)
x_validation.unsqueeze_(1)
y_validation.unsqueeze_(1)
# ------Dataset preparation end--------:

def metric(pred, target):
    return (pred - target).abs().mean()

def loss(pred, target):
    squares = (pred - target) ** 2
    return squares.mean()
"""
optimizer = torch.optim.Adam(net.parameters(), lr=0.01, weight_decay=0.1)
criterion = torch.nn.SmoothL1Loss()
for epoch_index in range(4000):
    optimizer.zero_grad()

    y_pred = net.forward(y_train)
    loss_value = metric(y_pred, y_train)

    loss_value.backward()
    optimizer.step()
"""

neurons_data = 0
lr_data = 0
epochs_data = 0
MAE = 0

optimizer = torch.optim.Adam(net.parameters(), lr=1e-4, weight_decay=1e-7)

loss_func = torch.nn.MSELoss()

for epoch_index in range(2000):
    optimizer.zero_grad()

    y_pred = net.forward(y_train)
    loss_value = loss(y_pred, y_train)

    loss_value.backward()
    optimizer.step()

end = time.time() - start

print("MAE value: {}".format(metric(net.forward(x_validation), y_validation).item()))

def predict(net, x, y):
    y_pred = net.forward(x)

    plt.plot(x.numpy(), y.numpy(), 'o', label='Groud truth')
    plt.plot(x.numpy(), y_pred.data.numpy(), 'o', c='r', label='Prediction');
    plt.legend(loc='upper left')
    plt.xlabel('$x$')
    plt.ylabel('$y$')


predict(net, x_validation, y_validation)