### 使用MnistTrain.py文件的一些方法
 - MnistTrain.py里是train_and_test('learingRate')的函数，返回测试结果
的正确率。
 - 可以用correct_rate列表来保存训练结果，然后使用一下python语句:
''' 
rate_list = [0.1, 0.2 ]
for lr in rate_list: 
    for i in range(10): 
        correct_rate.append(train_and_test(lr))
'''

