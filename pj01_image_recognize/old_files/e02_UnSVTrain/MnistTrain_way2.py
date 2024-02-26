import numpy as np
import datetime
from NeuralNetwork import neuralNetwork

def train_and_test_v2( Rate ):

    start = datetime.datetime.now()
    # Creat neural network
    input_nodes = 784
    hidden_nodes = 100
    output_nodes = 10
    
    learning_rate = Rate
    
    n = neuralNetwork( input_nodes, hidden_nodes, output_nodes, learning_rate)
    
    # Train mnist data
#    training_data_file = open("mnist_dataset/mnist_train_100.csv", 'r')
    training_data_file = open("mnist_dataset/mnist_train.csv", 'r')
   
    training_data_list = training_data_file.readlines()
    training_data_file.close()
    
    for training_data in training_data_list:
        values = training_data.split(',')
        inputs = ( np.asfarray(values[1:]) / 255.0 * 0.99) + 0.01
        targets = np.zeros(output_nodes) + 0.01
        targets[int(values[0])] = 0.99
        n.train( inputs, targets )

    # Test neural Network
#    test_data_file = open("mnist_dataset/mnist_test_10.csv", 'r')
    test_data_file = open("mnist_dataset/mnist_test.csv", 'r')

    test_data_list = test_data_file.readlines()
    test_data_file.close()
    
    data_numbers = 0.0
    correct_numbers = 0.0
    
    for test_data in test_data_list :
        values = test_data.split(',')
        inputs = ( np.asfarray(values[1:]) / 255.0 *0.99 ) + 0.01
        targets = int(values[0])
        outputs = n.query( inputs )

        # !!!!!!!!!!!!!!
        # version 2.0 add:
        # training Neural Network while test
        if np.argmax(outputs) == targets :
            correct_numbers += 1
        else : 
            targets = np.zeros(output_nodes) + 0.01
            targets[int(values[0])] = 0.99
            n.train( inputs, targets )
        data_numbers += 1

    end = datetime.datetime.now()

    print("Learning Rate:", learning_rate)
    print("Correct numbers:", correct_numbers)
    print("Test data numbers:", data_numbers)
    print("Correct Rate:", correct_numbers / data_numbers)
    print("Run time:", end-start)
    print()

    return correct_numbers / data_numbers

