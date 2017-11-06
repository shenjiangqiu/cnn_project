#coding=utf-8
# -*- coding: utf-8 -*-
import numpy as np
import caffe 
import sys
import struct
import socket
import threading
def tcplink(sock,addr,net):
    print('accept form:%s:%s...'%addr)
    data=sock.recv(1024)
    print data
    x=getarry(net,data)
    for i in xrange(0,9216):
        sock.send(struct.pack('f',x[i]))

    sock.close()
        
def getarry(net,choseImage):
    net.blobs['data'].data[...]  = transformer.preprocess('data', caffe.io.load_image(choseImage))
    out=net.forward()
    pool5Data=net.blobs['pool5'].data.reshape(1,-1)
    return pool5Data.reshape(-1)

caffe_root='/home/sjq/caffe/'
choseImage='123'
caffe.set_mode_gpu()
m=25088
n=4624
net = caffe.Net(caffe_root + 'models/bvlc_alexnet/deploy.prototxt',caffe_root + 'models/bvlc_alexnet/bvlc_alexnet.caffemodel',caffe.TEST)
transformer = caffe.io.Transformer({'data': net.blobs['data'].data.shape})  
transformer.set_transpose('data', (2,0,1))  
transformer.set_mean('data', np.load(caffe_root + 'python/caffe/imagenet/ilsvrc_2012_mean.npy').mean(1).mean(1)) # mean pixel  
transformer.set_raw_scale('data', 255)  # the reference model operates on images in [0,255] range instead of [0,1]  
transformer.set_channel_swap('data', (2,1,0)) # the reference model has channels in BGR order instead of RGB  
 # set net to batch size of 1 即输入为一张图片  
net.blobs['data'].reshape(1,3,227,227)  

s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(('127.0.0.1',9999))
s.listen(5)
while True:
    sock,addr=s.accept()
    t=threading.Thread(target=tcplink,args=(sock,addr,net))
    t.start()





