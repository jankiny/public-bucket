import numpy as np
import scipy.special

class neuralNetwork( object ):

    # neural network class definition
    def __init__( self, inputnodes, hiddennodes, outputnodes, learningrate ):
        # set number of nodes in each input, hidden, output layer
        self.inodes = inputnodes
        self.hnodes = hiddennodes
        self.onodes = outputnodes

        # weights between inputlayer and hiddenlayer, wih
        self.wih = ( np.random.rand ( self.hnodes, self.inodes ) - 0.5 )
        # who
        self.who = ( np.random.rand ( self.onodes, self.hnodes ) - 0.5 )
        # normal version: +- 1/sqrt(in-nodes) 
        # self.wih = np.random.normal ( 0.0, pow(self.hnodes, -0.5), (self.hnodes, self.inodes) )
        # self.who = np.random.normal ( 0.0, pow(self.onodes, -0.5), (self.onodes, self.hnodes) )

        # learning rate
        self.lr = learningrate

        # activation function is sigmoid function
        self.activation_function = lambda x: scipy.special.expit(x)

        pass
    
    # train the neural network
    def train( self, inputs_list, targets_list ):
        # convert input list to column vector array
        inputs = np.array(inputs_list, ndmin=2).T
        targets = np.array(targets_list, ndmin=2).T

        # calculate signals into hidden layer
        hidden_inputs = np.dot( self.wih, inputs )
        hidden_outputs = self.activation_function(hidden_inputs)

        # calculate signals into final output layer
        final_inputs = np.dot( self.who, hidden_outputs )
        final_outputs = self.activation_function(final_inputs)

        # error is the ( target - actual )
        final_errors = targets - final_outputs

        # hidden layer error
        hidden_errors = np.dot( self.who.T, final_errors )

        # update the weights for the links between hidden and output layers
        self.who += self.lr * np.dot( (final_errors * final_outputs * (1.0 - final_outputs)), hidden_outputs.T)
        # update the weights for the links between input and hidden layers
        self.wih += self.lr * np.dot( (hidden_errors * hidden_outputs * (1.0-hidden_outputs)), inputs.T)

        pass

    # query the neural network
    def query( self, inputs_list ):
        # convert input list to column vector array
        inputs = np.array(inputs_list, ndmin=2).T

        # calculate signals into hidden layer
        hidden_inputs = np.dot( self.wih, inputs )
        hidden_outputs = self.activation_function(hidden_inputs)

        # calculate signals into final output layer
        final_inputs = np.dot( self.who, hidden_outputs )
        final_outputs = self.activation_function(final_inputs)

        return final_outputs

# if __name__ == "__main__":
#     # number of input, hidden and output nodes
#     input_nodes = 3
#     hidden_nodes = 3
#     output_nodes = 3
#     
#     # learning rate is 0.3
#     learning_rate = 0.3
#     
#     # creat instance of neural network
#     n = neuralNetwork( input_nodes, hidden_nodes, output_nodes, learning_rate )

