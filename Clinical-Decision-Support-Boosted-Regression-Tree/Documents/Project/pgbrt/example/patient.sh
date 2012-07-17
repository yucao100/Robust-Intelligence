mpirun -np 1 ../bin/pgbrt patTrain1.dat 301 14 5 100 0.005 \-V patVal1.dat -v 129 > patOut.log
cat patOut.log | python ../scripts/crossval.py 2 -r  | python ../scripts/compiletest.py test
cat patTest1.dat | ./test > pTest.pred
python ../scripts/evaluate.py patTest2.dat pTest.pred > pEval.log
