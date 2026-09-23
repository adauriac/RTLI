#!/usr/bin/env python
import os,sys,subprocess
from sys import exit,argv
from os import popen,system
sys.path.append("/home/dauriac/lib")
def w(x):sys.stdout.writelines(x)

import jc2 as jc
def filterDir(x,t):
    print(list(filter(lambda x:x.find(t)!=-1,dir(x))))

def bits(n, longueur=None):
    if longueur is None:
        longueur = max(1, n.bit_length())
    return [(n >> i) & 1 for i in range(longueur)]

para=argv[1:]
alpha = 1
if len(argv)==2:
    filename=argv[1]
elif  len(argv)==3:
    filename=argv[1]
    alpha = float(argv[2])
    print(f"{alpha=}")
else:
    print("syntax: byEnum filename [multiplicateurJ")
    exit(1)

lines = open(filename).readlines()
hs = []
Js = []
for l in lines:
    if l[0]=="#":
        continue
    s = l.split()
    h = float(l.split()[0])
    hs.append(h)
    J = float(l.split()[1])
    Js.append(J*alpha)
L = len(Js)
N=2**L

Emin=1000
print(f"{hs=}")
print(f"{Js=}")
i0=[]
for k in range(N):
    s=bits(k,L)
    print(f"{k=} {s=}",end="   ")
    Eh= 0
    for i in range(L):
        Eh+=  hs[i]  if s[i]==1 else  -hs[i]
    EJ=0
    for i in range(L):
        EJ+= -Js[i] if s[i]==s[(i+1)%L] else Js[i]
    E =  EJ+Eh
    print(f"{EJ,Eh=} {E=}")
    if E<Emin:
        Emin= E
        i0 = [k]
    elif E==Emin:
        i0.append(K)
# s0=bits(i0,L)
print(f"E0={Emin}  {i0=}")
