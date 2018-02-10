# -*- coding: utf-8 -*-
"""
Created on Thu Feb 01 15:25:14 2018

@author: murillo
"""

import sys 
import time
import numpy as np
try:
    import serial
except:
    import pip
    pip.main(['Install', 'pyserial'])
    import serial
try:
    import xlwings as xw
except:
    import pip
    pip.main(['Install', 'xlwings'])
    import xlwings as xw
    



class DataLogger(object): 
    
    count_row = 2 #número da linha em que os dados começaram a ser escritos
    
      
    def findPort(self):
        
         #Procura a porta serial que está conectado o arduino   
        
        if sys.platform.startswith('win'):
            ports = ['COM%s' % (i + 1) for i in range(25)]      
        elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
            # this excludes your current terminal "/dev/tty"
            ports = glob.glob('/dev/tty[A-Za-z]*')
        elif sys.platform.startswith('darwin'):
            ports = glob.glob('/dev/tty.*')
        else:
            raise EnvironmentError('Unsupported platform')
        
        result = []
        for port in ports:
            try:
                s = serial.Serial(port)
                s.close()
                result.append(port)
            except (OSError, serial.SerialException):
                pass
        if (result==[]):
            print "Problems connecting from Arduino. Please try unplugging and reconnecting Arduino"
            sys.exit()
        return result[0]
  
    
    def __init__(self, port=None, baud=9600):
        self.baudrate = baud             #Atribui a baudrate ao objeto
        self.port = self.findPort()           #Encontra a porta serial e a define como atributo do objeto
        
        wb = xw.Book()
        global sht
        sht = wb.sheets['Sheet1']
       
        print('Opening connection') 
        
        global sp
        self.sp = serial.Serial(port=self.port, baudrate=baud, timeout=2) #Inicia a comunicação Serial
        self.sp.flushInput()
        self.sp.flushOutput()
        time.sleep(1)
        
        print('Connected via Arduino on port ' + self.port)
        
    def get_baudrate(self):
        return self.baudrate   
    
    
    def get_port(self):
        return self.port 
    
    ##Faz a leitura da porta serial
    
    def get_sensors_data(self):
        
        arduino_sensor2 = []        
        arduino_sensor1 = []
        arduino_data_log = []
    
        count_array = 0 #Variável para verificar o número de elementos em arduino_array         
        arduino_values = []     #reseta arduino_values para receber os dados a serem passados ao excel
    
        if (self.sp.inWaiting()>0):
            arduino_data_serial = self.sp.readline() #Faz a leitura da porta serial
            
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
                
            self.sp.flushInput()
            
            arduino_data_log.append(arduino_values)
            
            return arduino_values
        else:
            return "Sem dados na serial"
        
    def excel_write(self,data):
        global count_row
        try:
            global sht
            sht.range(count_row,1).value = data
            count_row += 1
        except:
            pass
            
    
        
    def set_set_point(self,set_point):
        #Envia para via porta serial o novo valor do set point.
        #Quando utilizado para captação do modelo empírico, deverá ser enviado o valor para controle do servo
        self.sp.write(set_point)
    

    def close(self):
        
        #Fecha a porta Serial.
        try:
            self.sp.close(self.close)
            print('Arduino disconnected successfully')
        except:
            print('Problems disconnecting from Arduino.')
            print('Please unplug and reconnect Arduino.')
        return True

arduino_serial = DataLogger() 

while(True):
    
    command = raw_input()
    
    while(raw_input() != "s"):
         print arduino_serial.get_sensors_data()
         
arduino_serial.set_set_point(raw_input("Novo set_point:"))
    
    



    


