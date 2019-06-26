from keras.layers import Input, Dense, LSTM
from keras.models import Model

batch_size = 64  # Batch size for training.
epochs = 100  # Number of epochs to train for.
latent_dim = 256  # Latent dimensionality of the encoding space.
num_samples = 10000  # Number of samples to train on.

data_path = ""

input_text = []
target_text = []
input_chrs = set()
target_chrs = set()
