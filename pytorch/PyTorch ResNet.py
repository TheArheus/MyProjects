import torch
import random
import numpy as np
import matplotlib.pyplot as plt
import torch.nn.functional as F
from torchvision.datasets import CIFAR10

random.seed(0)
np.random.seed(0)
torch.manual_seed(0)
torch.cuda.manual_seed(0)
torch.backends.cudnn.determenistic = True

cifar_train = CIFAR10("./", download=True, train=True)
cifar_test = CIFAR10('./', download=True, train=False)

X_train = cifar_train.data
y_train = cifar_train.targets
X_test = cifar_test.data
y_test = cifar_test.targets

X_train = torch.FloatTensor(X_train)
y_train = torch.LongTensor(y_train)
X_test = torch.FloatTensor(X_test)
y_test = torch.LongTensor(y_test)

X_train /= 255.
X_test /= 255.

X_train = X_train.permute(0, 3, 1, 2)
X_test = X_test.permute(0, 3, 1, 2)

def train(net, X_train, y_train, X_test, y_test):
    device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
    net = net.to(device)
    loss = torch.nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(net.parameters(), lr=1.0e-3)

    batch_size = 100

    test_accuracy_history = []
    test_loss_history = []

    X_test = X_test.to(device)
    y_test = y_test.to(device)

    for epoch in range(30):
        order = np.random.permutation(len(X_train))
        for start_index in range(0, len(X_train), batch_size):
            optimizer.zero_grad()
            net.train()

            batch_indexes = order[start_index:start_index + batch_size]

            X_batch = X_train[batch_indexes].to(device)
            y_batch = y_train[batch_indexes].to(device)

            preds = net.forward(X_batch)

            loss_value = loss(preds, y_batch)
            loss_value.backward()

            optimizer.step()

            X_batch

        net.eval()
        test_preds = net.forward(X_test)
        test_loss_history.append(loss(test_preds, y_test).data.cpu())

        accuracy = (test_preds.argmax(dim=1) == y_test).float().mean().data.cpu()
        test_accuracy_history.append(accuracy)

        print(accuracy)
    del net
    return test_accuracy_history, test_loss_history

class BasicBlock(torch.nn.Module):
    expansion = 1

    def __init__(self, in_filters, filters, stride=1):
        super(BasicBlock, self).__init__()
        self.conv1 = torch.nn.Conv2d(in_filters, filters, stride=stride, kernel_size=3, padding=1)
        self.bn1 = torch.nn.BatchNorm2d(filters)
        self.conv2 = torch.nn.Conv2d(filters, filters, stride=1, kernel_size=3, padding=1)
        self.bn2 = torch.nn.BatchNorm2d(filters)

        self.layer = torch.nn.Sequential()
        if stride != 1 or in_filters != filters:
            self.layer = torch.nn.Sequential(torch.nn.Conv2d(in_filters, self.expansion * filters, kernel_size=1, stride=stride, bias=False),
                                             torch.nn.BatchNorm2d(self.expansion * filters))

    def forward(self, x):
        res = x

        output = self.conv1(x)
        output = self.bn1(output)
        output = F.relu(output)
        output = self.conv2(output)
        output = self.bn2(output)

        output += self.layer(x)
        output = F.relu(output)

        return output

class ResNet(torch.nn.Module):
    def __init__(self, block, num_blocks, num_classes=10):
        super(ResNet, self).__init__()
        self.in_planes = 16

        self.conv1 = torch.nn.Conv2d(3, 16, kernel_size=3, stride=1, padding=1)
        self.bn1 = torch.nn.BatchNorm2d(16)

        self.layer1 = self._make_layer(block, 16, num_blocks[0], 1)
        self.layer2 = self._make_layer(block, 32, num_blocks[1], 2)
        self.layer3 = self._make_layer(block, 64, num_blocks[2], 2)

        self.linear = torch.nn.Linear(64, num_classes)
        self.apply()

    def _make_layer(self, block, out_ch, layers, stride=1):
        strides = [stride] + [1] * (layers - 1)

        layer = []
        for str_ in strides:
            layer.append(block(self.in_planes, out_ch, str_))
            self.in_planes = block.expansion * out_ch

        return torch.nn.Sequential(*layer)

    def forward(self, x):
        out = F.relu(self.bn1(self.conv1(x)))
        out = self.layer1(out)
        out = self.layer2(out)
        out = self.layer3(out)
        out = F.avg_pool2d(out, out.size()[3])
        out = out.view(out.size(0), -1)
        out = self.linear(out)
        return out

def resnet20():
    return ResNet(BasicBlock, [3, 3, 3])

net = resnet20()

val1, val2 = train(net, X_train, y_train, X_test, y_test)

plt.plot(val1)
plt.title("test_accuracy_history")
plt.show()

plt.plot(val2)
plt.title("test loss history")
plt.show()