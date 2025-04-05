import pandas as pd
import numpy as np 
import matplotlib.pyplot as plt
import tensorflow as tf
import seaborn as sns
from tensorflow import keras
from tensorflow.keras import layers
from tensorflow.keras.datasets import mnist
(x_train, y_train),(x_test, y_test)=mnist.load_data()
print("Training_data_shape:", x_train.shape)
print("Testind_data_shape:",x_test.shape)
print("unique_classes:", np.unique(y_train))
# Visualizing some samples
fig, axes = plt.subplots(1, 5, figsize=(10, 3))
for i in range(5):
    axes[i].imshow(x_train[i], cmap='gray')
    axes[i].set_title(f"Label: {y_train[i]}")
    axes[i].axis('off')
plt.show()
model = keras.Sequential([
    layers.Conv2D(32, kernel_size=(3,3), activation='relu', input_shape=(28,28,1)),
    layers.MaxPooling2D(pool_size=(2,2)),
    layers.Conv2D(64, kernel_size=(3,3), activation='relu'),
    layers.MaxPooling2D(pool_size=(2,2)),
    layers.Flatten(),
    layers.Dense(128, activation='relu'),
    layers.Dense(10, activation='softmax')
])
model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=["accuracy"])
history=model.fit(x_train,y_train, validation_data=(x_test,y_test), epochs=10, batch_size=128)
test_loss, test_acc= model.evaluate(x_test,y_test)
print("Test Accuracy:", test_acc)
print("Test_loss:", test_loss)
plt.figure(figsize=(12,5))
plt.subplot(1, 2, 2)
plt.plot(history.history['loss'], label='Train Loss')
plt.plot(history.history['val_loss'], label='Validation Loss')
plt.legend()
plt.title("Model Loss")
plt.xlabel("EPOCHS")
plt.ylabel("accuarcy frequency")
plt.show()
predictions= model.predict(x_test)
prediction_labels= np.argmax(predictions, axis=1)
fig, axes = plt.subplots(1, 5, figsize=(10, 3))
for i in range(5):
    axes[i].imshow(x_test[i], cmap='gray')
    axes[i].set_title(f"Actual: {y_test[i]}\nPredicted: {pred_labels[i]}")
    axes[i].axis('off')
plt.show()


