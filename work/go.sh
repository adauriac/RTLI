#!/bin/bash -f

# call4 81920 1e-1 0 10000 >> Resultat
# call4 81920 1e-2 0 10000 >> Resultat
# call4 81920 1e-3 0 10000 >> Resultat
# call4 81920 1e-4 0 10000 >> Resultat
# call4 819200 1e-1 0 1000 >> Resultat
# call4 819200 1e-2 0 1000 >> Resultat
# call4 819200 1e-3 0 1000 >> Resultat
# call4 819200 1e-4 0 1000 >> Resultat

# anaRes.py Resultat 0 81920 1e-1
# anaRes.py Resultat 0 81920 1e-2
# anaRes.py Resultat 0 81920 1e-3
# anaRes.py Resultat 0 81920 1e-4
# anaRes.py Resultat 0 819200 1e-1
# anaRes.py Resultat 0 819200 1e-2
# anaRes.py Resultat 0 819200 1e-3
# anaRes.py Resultat 0 819200 1e-4

# callAndAnalyze L=8 H=0.1 per=1 seed=51154 nCalls=10000 verbose=0 > Results25Sept
# callAndAnalyze L=10 H=0.1 per=1 seed=51154 nCalls=10000 verbose=0 >> Results25Sept
# callAndAnalyze L=12 H=0.1 per=1 seed=51154 nCalls=10000 verbose=0 >> Results25Sept
# callAndAnalyze L=16 H=0.1 per=1 seed=51154 nCalls=10000 verbose=0 >> Results25Sept
# callAndAnalyze L=20 H=0.1 per=1 seed=51154 nCalls=10000 verbose=0 >> Results25Sept
# callAndAnalyze L=24 H=0.1 per=1 seed=51154 nCalls=10000 verbose=0 >> Results25Sept
# callAndAnalyze L=32 H=0.1 per=1 seed=51154 nCalls=10000 verbose=0 >> Results25Sept

# callAndAnalyze L=8 H=0.05 per=1 seed=51154 nCalls=10000 verbose=0 > Results27Sept
# callAndAnalyze L=10 H=0.05 per=1 seed=51154 nCalls=10000 verbose=0 >> Results27Sept
# callAndAnalyze L=12 H=0.05 per=1 seed=51154 nCalls=10000 verbose=0 >> Results27Sept
# callAndAnalyze L=16 H=0.05 per=1 seed=51154 nCalls=10000 verbose=0 >> Results27Sept
# callAndAnalyze L=20 H=0.05 per=1 seed=51154 nCalls=10000 verbose=0 >> Results27Sept
# callAndAnalyze L=24 H=0.05 per=1 seed=51154 nCalls=10000 verbose=0 >> Results27Sept
# callAndAnalyze L=32 H=0.05 per=1 seed=51154 nCalls=10000 verbose=0 >> Results27Sept

# callAndAnalyze L=8192 H=0.05 per=1 seed=51154 nCalls=10000 verbose=0 > Results29Sept
# callAndAnalyze L=16384 H=0.05 per=1 seed=51154 nCalls=10000 verbose=0 >> Results29Sept
# callAndAnalyze L=32768 H=0.05 per=1 seed=51154 nCalls=10000 verbose=0 >> Results29Sept
# callAndAnalyze L=65536 H=0.05 per=1 seed=51154 nCalls=10000 verbose=0 >> Results29Sept
# callAndAnalyze L=131072 H=0.05 per=1 seed=51154 nCalls=10000 verbose=0 >> Results29Sept

# for H in 0.1 0.01 0.005; do
#     for L in 16 32 64 128 256; do
#	echo $H" "$L
#        callAndAnalyze L=$L H=$H nCalls=1000000 per=1 seed=0 verbose=0 > "Results_"$H"_"$L
#    done
# done

# for H in 0.01; do
#     for L in 512 1024 2048 8192 16384 32768; do
# 	time callAndAnalyze L=$L H=$H nCalls=1000000 per=1 seed=0 verbose=0 > "bid_"$H"_"$L
#     done
# done

# { time callAndAnalyze L=2048 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_2048_1" &
# { time callAndAnalyze L=2048 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_2048_2" &
# { time callAndAnalyze L=2048 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_2048_3" &
# { time callAndAnalyze L=2048 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_2048_4" &

# { time callAndAnalyze L=4096 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_4096_1" &
# { time callAndAnalyze L=4096 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_4096_2" &
# { time callAndAnalyze L=4096 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_4096_3" &
# { time callAndAnalyze L=4096 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_4096_4" &

{ time callAndAnalyze L=8192 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_8192_1" &
{ time callAndAnalyze L=8192 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_8192_2" &
{ time callAndAnalyze L=8192 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_8192_3" &
{ time callAndAnalyze L=8192 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_8192_4" &
