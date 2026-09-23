#!/usr/bin/env python
"""
Lit un fichier crée par call4 et cree un fichier pour tracer un histogramme
par impulse dans gnuplot.
syntax : anaRes.py fileName nBox L H
used in gnuplot :
plot "< anaRes.py Resultat 30 81920 1e4" wit imp
will plot the histogram with 30 boxes
"""
import os,sys,subprocess
from sys import exit,argv
from os import popen,system
sys.path.append("/home/dauriac/lib")
def w(x):sys.stdout.writelines(x)

import jc2 as jc
def filterDir(x,t):
    print(list(filter(lambda x:x.find(t)!=-1,dir(x))))
try:
    fileName = argv[1]
    nBox = int(argv[2])
    L = int(argv[3])
    H = float(argv[4])
except:
    print("syntax : "+argv[0]+" fileName nBox")
    exit(1)

lines = open(fileName).readlines()
Correls = []
for line in lines:
    if line[0]=="#":
        continue
    ls = line.split()
    if int(ls[1]) != L:
        continue
    if abs(float(ls[3]) - H) > 1e-7:
        continue
    Correls.append(ls[9])
if len(Correls)==0:
    print(f"No data survive {L=} {H=}")
    exit(1)
import numpy as np
Cs = np.array(list(map(float,Correls)))
mi = Cs.min()
ma = Cs.max()
histo = np.zeros(nBox)
for x in Cs:
    k = max(0,min(nBox-1,int(nBox*(x-mi)/(ma-mi))))
    # print(f"{x=} {k=}")
    histo[k] += 1
Delta = (ma-mi)/nBox
for i in range(nBox):
    xi = mi+ (i+0.5)*Delta
    print(f"{xi} {histo[i]}")
CorrelsArr= np.array(list(map(float,Correls)))
mean = np.mean(CorrelsArr)
stdErr = np.std(CorrelsArr,ddof=1)
print(f"# {mean=} {stdErr=}")
