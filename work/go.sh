#!/bin/bash -f

###########################################################
# L=1024 nCalls=1000000 per=1 H=0.01 takes roughly 30 sec #
###########################################################

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

# { time callAndAnalyze L=8192 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_8192_1" &
# { time callAndAnalyze L=8192 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_8192_2" &
# { time callAndAnalyze L=8192 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_8192_3" &
# { time callAndAnalyze L=8192 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_8192_4" &

# 14 octobre 17h
# for n in 1 2 3 4; do
#     L=$((1024 + n*128))
#     echo $L
#     { time callAndAnalyze L=$L H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_"$L &
# done

# 14 octobre 17h30
# for n in 5 6 7 ; do
#     L=$((1024 + n*128))
#     echo $L
#     { time callAndAnalyze L=$L H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 ; } &> "Results_0.01_"$L &
# done

# jeu. 15 oct. 2026 12:07:43 CEST
# callAndAnalyze L=2048 H=0.01 nCalls=25000000 per=1 seed=1769153053 verbose=0 outFullDistrib=1 > FullDistrib_0.01_2048_1769153053 &

# lun. 19 oct. 2026 11:26:35 CEST
# callAndAnalyze L=2048 H=0.01 nCalls=25000000 per=1 seed=1185603221 verbose=0 outFullDistrib=1 > FullDistrib_0.01_2048_1185603221 &
# seed=23524103
# n=1
# callAndAnalyze L=2048 H=0.01 nCalls=25000000 per=1 seed=$seed verbose=0 outFullDistrib=1 > FullDistrib_0.01_2048_$n &
# seed=641702055
# n=2
# callAndAnalyze L=2048 H=0.01 nCalls=25000000 per=1 seed=$seed verbose=0 outFullDistrib=1 > FullDistrib_0.01_2048_$n &

# mer. 21 oct. 2026 10:56:59 CEST
# for n in 5 6 7 8 ; do
#     time callAndAnalyze L=2048 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 > "Results_0.01_2048_"$n &
# done

# mer. 21 oct. 2026 10:56:59 CEST
# for n in 9 10 11 12 ; do
#     time callAndAnalyze L=2048 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 > "Results_0.01_2048_"$n &
# done

# mer. 21 oct. 2026 10:56:59 CEST
# for n in 13 14 15 16 ; do
#     time callAndAnalyze L=2048 H=0.01 nCalls=25000000 per=1 seed=0 verbose=0 >  "Results_0.01_2048_"$n &
# done

# mer. 21 oct. 2026 10:56:59 CEST
# nCalls=25000000
# for n in 0 1 2 3 ; do
#     seed=$(od -An -N8 -tu8 /dev/urandom | tr -d ' ')
#     callAndAnalyze L=2048 H=0.01 nCalls=$nCalls per=1 seed=$seed verbose=0 >  "newGeneResults/Results_0.01_2048_"$seed &
# done
# echo "waiting"
# wait
# echo "ok"
# for n in 0 1 2 3 ; do
#     seed=$(od -An -N8 -tu8 /dev/urandom | tr -d ' ')
#     callAndAnalyze L=2048 H=0.01 nCalls=$nCalls per=1 seed=$seed verbose=0 >  "newGeneResults/Results_0.01_2048_"$seed &
# done
# echo "waiting"
# wait 
# echo "ok"
# for n in 0 1 2 3 ; do
#     seed=$(od -An -N8 -tu8 /dev/urandom | tr -d ' ')
#     callAndAnalyze L=2048 H=0.01 nCalls=$nCalls per=1 seed=$seed verbose=0 >  "newGeneResults/Results_0.01_2048_"$seed &
# done
# echo "waiting"
# wait 
# echo "ok"
# for n in 0 1 2 3 ; do
#     seed=$(od -An -N8 -tu8 /dev/urandom | tr -d ' ')
#     callAndAnalyze L=2048 H=0.01 nCalls=$nCalls per=1 seed=$seed verbose=0 >  "newGeneResults/Results_0.01_2048_"$seed &
# done
# echo "waiting"
# wait 
# echo "ok"

# mer. 21 oct. 2026 21:38:16 CEST
nCalls=25000000
for n in 0 1 2 3 ; do
    seed=$(od -An -N8 -tu8 /dev/urandom | tr -d ' ')
    callAndAnalyze L=2048 H=0.01 nCalls=$nCalls per=1 seed=$seed verbose=0 >  "newNewGeneResults/Results_0.01_2048_"$seed &
done
wait
for n in 0 1 2 3 ; do
    seed=$(od -An -N8 -tu8 /dev/urandom | tr -d ' ')
    callAndAnalyze L=2048 H=0.01 nCalls=$nCalls per=1 seed=$seed verbose=0 >  "newNewGeneResults/Results_0.01_2048_"$seed &
done
wait 
for n in 0 1 2 3 ; do
    seed=$(od -An -N8 -tu8 /dev/urandom | tr -d ' ')
    callAndAnalyze L=2048 H=0.01 nCalls=$nCalls per=1 seed=$seed verbose=0 >  "newNewGeneResults/Results_0.01_2048_"$seed &
done
wait 
for n in 0 1 2 3 ; do
    seed=$(od -An -N8 -tu8 /dev/urandom | tr -d ' ')
    callAndAnalyze L=2048 H=0.01 nCalls=$nCalls per=1 seed=$seed verbose=0 >  "newNewGeneResults/Results_0.01_2048_"$seed &
done
wait 
