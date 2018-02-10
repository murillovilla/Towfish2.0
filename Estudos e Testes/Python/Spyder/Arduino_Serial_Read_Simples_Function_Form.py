# -*- coding: utf-8 -*-
"""
Created on Thu Jan 25 15:17:33 2018

Prgrama Funcionando!


@author: murillo
"""

import serial
import time


arduino_serial = serial.Serial('com3', 9600, timeout =1)    #Abre a porta com3 com baud 9600

time.sleep(0.5) #delay 500 ms


arduino_sensor1 =[] #Lista que contém todos os valores recebidos pelo sensor 1
arduino_sensor2 =[] #Lista que contém todos os valores recebidos pelo sensor 2
arduino_data_log = ["Iniciando"] ##Faz o log de tudo que estiver na serial
arduino_data_excel = [] #variável utilizada para passar ao excel os dados
count = 1


def read_serial():

    count_array = 0 #Variável para verificar o número de elementos em arduino_array         
    arduino_values = []     #reseta arduino_values para receber os dados a serem passados ao excel

    if (arduino_serial.inWaiting()>0):
        arduino_data_serial = arduino_serial.readline() #Faz a leitura da porta serial
                     
        print "arduino_serial.readline()= ",arduino_data_serial #Para debugar
        
        newtime = str(time.localtime().tm_sec)      #tempo real em segundos
        
        arduino_array = arduino_data_serial.split(',') #Separa os dados
        
        print "arduino_array= ", arduino_array     #Para debugar
                
        for element in arduino_array:  #Confere se arduino array separou os dados corretamente
            count_array += 1            
            
        print "Count array = ", count_array #Para debugar
            
        if (count_array ==2):        #Se o número de elementos em arduino_array = 2, eles são adicionados à suas listas
            arduino_sensor2.append(arduino_array[1])
            arduino_sensor1.append(arduino_array[0])
            arduino_values.append(arduino_array[0]) 
            arduino_values.append(arduino_array[1])
            arduino_values.append(newtime)
        else:
            arduino_sensor2.append("Lost Data")
            arduino_sensor1.append("Lost Data") 
            arduino_values.append("Lost Data") 
            arduino_values.append("Lost Data")
                            
        arduino_array = []          #Reseta arduino_array para receber os próximos dados
            
        arduino_serial.flushInput()
        
        arduino_data_log.append(arduino_values)
        
             
        return arduino_values
    else:
        return "Null" 
    
         
  

while(True):  
    
    time.sleep(0.01)         #delay de 100ms
    arduino_data_excel.append(read_serial())      #chama a função que faz leitura da porta serial
    
    if (arduino_data_excel!=["Null"]):
        print"arduino_data_excel= ", arduino_data_excel       #para debugar
        arduino_data_excel = []     #reseta arduino_data_excel
    else:
        arduino_data_excel = []     #reseta arduino_data_excel
        pass
           
    
    