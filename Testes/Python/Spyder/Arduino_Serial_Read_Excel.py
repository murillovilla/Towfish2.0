# -*- coding: utf-8 -*-
"""
Created on Thu Jan 25 18:37:28 2018

Ainda não está funcionando. Problema ao escrever no excel! (25/1/18 18:45)

@author: murillo
"""


import serial
import xlwings as xw
import time

wb = xw.Book()
sht = wb.sheets['Sheet1']
#sht.range('A1').value = "Profundidade"
#sht.range('B1').value = "Angulo de Pitch"

arduino_serial = serial.Serial('com3', 9600, timeout =1)

time.sleep(0.5) #delay 500 ms


arduino_sensor1 =[] #Lista que contém todos os valores recebidos pelo sensor 1
arduino_sensor2 =[] #Lista que contém todos os valores recebidos pelo sensor 2
arduino_data_log = ["Inicializando"]
arduino_data_excel = []
count_row = 2       #o numero da linha em que os dados da porta serial vão começar a ser escritos


def read_serial():

    count_array = 0 #Variável para verificar o número de elementos em arduino_array         
    arduino_values = []     #reseta arduino_values para receber os dados a serem passados ao excel

    if (arduino_serial.inWaiting()>0):
        arduino_data_serial = arduino_serial.readline() #Faz a leitura da porta serial
        
        newTime = str(time.localtime().tm_sec)     ##New Time recebe o tempo real em segundos
                     
        print "arduino_serial.readline()= ",arduino_data_serial #Para debugar
        
        arduino_array = arduino_data_serial.split(',') #Separa os dados
        
        print "arduino_array= ", arduino_array     #Para debugar
        
        for element in arduino_array:  #Confere se arduino array separou os dados corretamente
            count_array += 1            
            
        print "Count array = ", count_array   #Para debugar
            
        if (count_array ==2):        #Se o número de elementos em arduino_array = 2, eles são adicionados à suas listas
            arduino_sensor2.append(arduino_array[1])
            arduino_sensor1.append(arduino_array[0])
            arduino_values.append(arduino_array[0]) 
            arduino_values.append(arduino_array[1])
            arduino_values.append(newTime)
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
    
            
  
def excel_write(data):
    global count_row
    try:
        sht.range(count_row,1).value = data
        count_row += 1
    except:
        pass
        
    
        
    

while(True):  
    
    time.sleep(0.1)         #delay de 100ms
    arduino_data_excel.append(read_serial()) 
    
    if (arduino_data_excel!=["Null"]):
        
        try:
            excel_write(arduino_data_excel)   #passa arduino_data para ser passado ao excel
        except:
                pass                   
        
        
        print"arduino_data_excel= ", arduino_data_excel       #para debugar
        arduino_data_excel = []     #reseta arduino_data_excel
    else:
        arduino_data_excel = []     #reseta arduino_data_excel
        pass
    
    arduino_data_excel = []
    

    
    