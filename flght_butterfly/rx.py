#coding=utf-8
'''
@author: kohill
'''
from nrf24 import NRF24
import time
from time import gmtime, strftime
 
#设定从机的发送地址pipes[0],pipes[1],本机的发送pipes[0]
pipes = [[0x01,0x02,0x03,0x02,0x01], [0x01,0x02,0x03,0x02,0x01]]
radio = NRF24()
radio.begin(0, 0,22,23) #set gpio 25 as CE pin,gpio 18 as IRQ pin
radio.setRetries(15,15)
radio.setPayloadSize(32)
radio.setChannel(40)
radio.setDataRate(NRF24.BR_2MBPS)
radio.setPALevel(NRF24.PA_MAX)
radio.setAutoAck(0)

radio.openReadingPipe(0, pipes[0])
radio.startListening()
radio.stopListening()
 
radio.printDetails()
radio.startListening()
 
while True:
 
    pipe = [0] #pipe为接收到的信息的从机从机身份标识
    while not radio.available(pipe, True):
        time.sleep(100/1000000.0)
    recv_buffer = []
    radio.read(recv_buffer)
    out = ''.join(chr(i) for i in recv_buffer)
    print "Message from "+str(pipe[0])+":"+out
