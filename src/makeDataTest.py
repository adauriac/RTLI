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

H = 1.3
L = int(argv[1])
periodic = int(argv[2])
f=open("dataTest","w")
for i in range(L) :
    J = random.random()
    h = (random.random()*2-1) * H
    if (not periodic) and i==L-1:
        J=0
    f.writelines(f"{h} {J}\n")
f.close()
