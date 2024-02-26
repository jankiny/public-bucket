#coding:utf-8
import tensorflow as tf
import numpya as np

BATCH_SIZE = 100
STEPS = 50000
MODEL_SAVE_PATH = "./modle/"
MODEL_NAME = "mnist_modle"
# learning rate
LEARNING_RATE = 0.01
# inputs size
IMAGE_SIZE = 28
IMAGE_CHANNELS = 1
# conv1 size
CONV1_KERNEL_SIZE = 5
CONV1_KERNEL_NUM = 6
# pool2 size
POOL2_KERNEL_SIZE = 2
# conv3 size
CONV3_KERNEL_SIZE = 5
CONV3_KERNEL_NUM = 16
# pool4 size
POOL4_KERNEL_SIZE = 2
# conv5 size
CONV5_KERNEL_SIZE = 5
CONV5_KERNEL_NUM = 120
# fc nodes
FC6_NODES = 84
OUTPUT_NODES = 10

def weight_variable(shape):
    initial = tf.truncated_normal(shape, stddev=0.1)
    return tf.Variable(initial)

def bias_variable(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)

def conv2d(x, W):
    return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='VALID')

def max_pool_2x2(x):
    return tf.nn.max_pool(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')

def forward(x):
    # convolution variable
    conv1_w = weight_variable([CONV1_KERNEL_SIZE, CONV1_KERNEL_SIZE, IMAGE_CHANNELS, CONV1_KERNEL_NUM])
    conv1_b = bias_variable([CONV1_KERNEL_NUM])
    conv3_w = weight_variable([CONV3_KERNEL_SIZE, CONV3_KERNEL_SIZE, CONV1_KERNEL_NUM, CONV3_KERNEL_NUM])
    conv3_b = bias_variable([CONV3_KERNEL_NUM])
    conv5_w = weight_variable([CONV5_KERNEL_SIZE, CONV5_KERNEL_SIZE, CONV3_KERNEL_NUM, CONV5_KERNEL_NUM])
    conv5_b = bias_variable([CONV5_KERNEL_NUM])
    # connection variable
    fc6_w = weight_variable([CONV5_KERNEL_NUM, FC6_NODES])
    fc6_b = bias_variable([FC6_NODES])
    fc7_w = weight_variable([FC6_NODES, OUTPUT_NODES])
    fc7_b = bias_variable([OUTPUT_NODES])

    # farward graph
    conv1 = tf.nn.conv2d(x, conv1_w, strides=[1, 1, 1, 1], padding='SAME')
    pool2 = max_pool_2x2(tf.nn.relu(tf.nn.bias_add(conv1, conv1_b)))
    conv3 = conv2d(pool2, conv2_w)
    pool4 = max_pool_2x2(tf.nn.relu(tf.nn.bias_add(conv3, conv3_b)))
    conv5 = conv2d(pool4, conv5_w)
    conv_outputs = tf.nn.relu(tf.nn.bias_add(conv5, conv5_b))

    fc_inputs = conv_outputs.reshape((1, CONV5_KERNEL_NUM))

    fc6 = tf.nn.relu(tf.matmul(fc_inputs, tf6_w) + fc6_b)
    y = tf.matmul(fc6, fc7_w) + fc7_b
    return y

def backward( inputs, targets ):
    x = tf.placeholer(tf.float32, [BATCH_SIZE, IMAGE_SIZE, IMAGE_SIZE, IMAGE_CHANNELS])
    y_= tf.placeholer(tf.float32, [None, OUTPUT_NODES])
    
    y = forward(x)
    loss = tf.reduce_mean(tf.square(y-y_))

    train_step = tf.train.GradientDescentOptimizer(learning_rate).minimize(loss)

    saver = tf.train.Saver()

    with tf.Session() as sess:
        init_op = tf.global_variables_initializer()
        sess.run(init_op)

        cjpt = tf.train.get_checkpoint_state(MODEL_SAVE_PATH)
        if ckpt and ckpt.model_checkpoint_path:
            saver.restore(sess, ckpt,model_ceckpoint_path)

        for i in range(STEPS):
            reshaped_inputs = np.reshape(inputs, (
                BATCH_SIZE,
                IMAGE_SIZE,
                IMAGE_SIZE,
                IMAGE_CHANNELS))
            _, loss_value = sess.run([train_step, loss], feed_dict={x: reshaped_inputs, y_: targets})
            if i % 100 == 0
            print("After %d training step(s), loss is %g." % (i, loss_value))
            saver.save(sess, os.path.join(MODEL_SAVE_PATH, MODEL_NAME))

if __name__ == '__main__':
    pass

