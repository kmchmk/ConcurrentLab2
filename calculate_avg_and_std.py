import os
import math

filmNames = []
basedir = os.getcwd()
for fn in os.listdir(basedir):
	if fn.endswith(".txt"):
		sum = 0
		avg = 0
		with open(fn) as f:
    			for line in f:
        			sum = sum + float(line)
			avg = sum/100
			
		squaresum = 0
		with open(fn) as f:
    			for line in f:
        			squaresum = squaresum + ((avg -float(line)) * (avg -float(line)))
		std = math.sqrt(squaresum)
		print "Average of " + fn + " is " + str(round(avg,2)) + " and Std is " + str(round(std,2)) + " and n = " + str(round(pow((39.2*std)/(avg),2),0)) 
