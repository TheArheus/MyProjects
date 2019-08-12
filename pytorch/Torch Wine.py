import torch
import numpy as np
from sklearn import model_selection
from sklearn import datasets

torch.manual_seed(0)
np.random.seed(0)
torch.cuda.manual_seed(0)
torch.backends.cudnn.determenistic = True

wine = datasets.load_wine()
X_train, Y_train, X_test, Y_test = model_selection.train_test_split(wine.data[:, :2],
                                                                            wine.target,
                                                                            test_size=0.3,
                                                                            shuffle=True)

X_train = torch.FloatTensor(X_train)
X_test = torch.FloatTensor(X_test)
Y_train = torch.LongTensor(Y_train)
Y_test = torch.LongTensor(Y_test)


class WineNet(torch.nn.Module):
    def __init__(self, n_hidden_neurons):
        super(WineNet, self).__init__()

        self.fc1 = torch.nn.Linear(2, n_hidden_neurons)
        self.activ1 = torch.nn.Sigmoid()
        self.fc2 = torch.nn.Linear(n_hidden_neurons, n_hidden_neurons)
        self.activ2 = torch.nn.Sigmoid()
        self.fc3 = torch.nn.Linear(n_hidden_neurons, 3)
        self.sm = torch.nn.Softmax(dim=1)

    def forward(self, x):
        x = self.fc1(x)
        x = self.activ1(x)
        x = self.fc2(x)
        x = self.activ2(x)
        x = self.fc3(x)
        return x

    def inference(self, x):
        x = self.forward(x)
        x = self.sm(x)
        return x


wine_net = WineNet(5)

loss = torch.nn.CrossEntropyLoss()

optimizer = torch.optim.Adam(wine_net.parameters(), lr=1.0e-3)

batch_size = 10

for epoch in range(10000):
    order = np.random.permutation(len(X_train))
    for idx in range(0, len(X_train), batch_size):
        optimizer.zero_grad()

        batch_idxs = order[idx: idx + batch_size]

        x_batch = X_train[batch_idxs]
        y_batch = Y_train[batch_idxs]

        pred = wine_net.forward(x_batch)

        loss_val = loss(pred, y_batch)
        loss_val.backward()

        optimizer.step()

    if epoch % 100 == 0:
        test_pred = wine_net.forward(X_test)
        test_pred = test_pred.argmax(dim=1)
        print((test_pred == Y_test).float().mean())
