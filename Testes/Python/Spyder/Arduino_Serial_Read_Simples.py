# -*- coding: utf-8 -*-
"""
Created on Wed Jan 24 17:08:47 2018

Esse programa serve para ler a porta serial. São esperados
valores de dois sensores. Os valores recebidos são armazenados
em duas listas diferentes

@author: murillo
"""

import serial
 
arduino_serial = serial.Serial('com3', 9600, timeout =1)

arduino_sensor1 =[] #Lista que contém todos os valores recebidos pelo sensor 1
arduino_sensor2 =[] #Lista que contém todos os valores recebidos pelo sensor 2

while(True):
    if (arduino_serial.inWaiting()>0):
        arduino_data = arduino_serial.readline() #Faz a leitura da porta serial
        arduino_array = arduino_data.split(',') #Separa os dados
        
        arduino_sensor1.append(arduino_array[0])
        arduino_sensor2.append(arduino_array[1])
        
        arduino_serial.flushInput()
        

   