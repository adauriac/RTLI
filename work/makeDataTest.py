#!/usr/bin/env python
import os,sys,subprocess
from sys import exit,argv
from os import popen,system
sys.path.append("/home/dauriac/lib")
def w(x):sys.stdout.writelines(x)
import random
import jc2 as jc
def filterDir(x,t):
    print(list(filter(lambda x:x.find(t)!=-1,dir(x))))

helper = """
syntax : make L periodic(0/1) H(float) [filename] 
creation des paramètres hs et Js, si periodic==0 Js[-1]=0
one 2-uple by line h (uniform in [-H,H]) J (uniform in [0,1])
if filename not given output on stdout
"""

f = sys.stdout
try:
    L = int(argv[1])
    periodic = int(argv[2])
    H = float(argv[3])
    if len(argv)==5:
        f=open(argv[4],"w")
except:
    print(helper)
    exit(1)

for i in range(L) :
    J = random.random()
    h = (random.random()*2-1) * H
    if (not periodic) and i==L-1:
        J=0
    f.writelines(f"{h} {J}\n")
f.close()
