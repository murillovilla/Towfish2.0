# -*- coding: utf-8 -*-
"""
Created on Fri Jan 26 17:29:32 2018

@author: murillo
"""

import serial
import xlwings as xw
import time

wb = xw.Book()
sht = wb.sheets['Data_Sensores']
sht.range('A1').value = "Profundidade"
sht.range('B1').value = "Angulo de Pitch"