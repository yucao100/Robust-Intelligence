README FILE
Explanation of pGBRT package for C++ implementation by 
Albert Thornton
July 22, 2012

CONTENTS
I.	ABOUT
II.	MINIMUM SYSTEM REQUIREMENTS
III.	INSTALLATION
IV.	EXAMPLE
V.	USAGE
VI.	SCRIPTS
VII.	LICENSE

I. ABOUT
Readme contains information provided by original readme document as well as advice and tips about using the package by myself. This package is not originally mines so resort to “LICENSE” when deciding to incorporate it to your own work.

This software package learns gradient boosted regression tree ensembles with training performed in parallel with MPI. See “INSTALLATION” for instructions to compile a C++ executable for training. “EXAMPLE” provides a simple usage example. See “USAGE”/”SCRIPTS” for a description of command line arguments and helpful Python scripts.

Version 0.9, August 2011. For additional documentation and latest release, visit http://machinelearning.wustl.edu/index.php/main/pGBRT. Address problems or bugs to swtyree@wustl.edu. 

II. REQUIREMENTS
Parallel communication in pgbrt is supported by MPI, so this package requires a recent distribution of MPI for compilation and execution. Both OpenMPI (http://www.open-mpi.org) and MPICH2 (http://www.mcs.anl.gov/research/projects/mpich2) are supported. If MPI is not already installed, please refer to either distribution for installation instructions. Either distribution will provide the two binaries required below: a compiler wrapper and a parallel execution handler (e.g. mpirun).

** Please note that MPI may not work on Windows operating system. When running the package, it was used on Linux Ubuntu version 12.04. While it may possibly work with Mac OS, I myself haven’t found an equivalent application of MPI for Windows **

III. INSTALLATION [Referring to Linux Ubuntu 12.04]
To compile with GCC options, run “make” in the source directory. Call “make intel” to compile with options for the Intel ICC compiler. The resulting binary will be written to the bin/ directory.

In  many cases it may be necessary to modify the make file to point to desired MPI compiler wrapper (typically called mpicxx and located in the MPI installation bin/ directory).

IV. EXAMPLE
Here is a simple usage example. Navigate to the example/ directory in the distribution. The following commands will train a model, cross-validate on validation set ERR, produce a test executable, and evaluate a test set using that executable. Depending on your system, replace mpirun with the appropriate MPI execution handler.
	mpirun -np 2 ../bin/pgbrt train.dat 70 700 4 100 0.2 \
		-V valid.dat -v 30 -m > out.log
	cat out.log | python ../scripts/crossval.py 5 -r \
		| python ../scripts/compiletest.py test
	cat test.dat | ./test > test.pred
	python ../scripts/evaluate.py test.dat test.dat


V. USAGE
Here are the required and optional arguments to the pgbrt executable.

Mpirun -np N_PROCS pgbrt TRAIN_FILE TRAIN_SIZE N_FEATURES DEPTH N_TREES RATE [OPTIONS]

N_PROCS	number of processors
TRAIN_FILE	training file
TRAIN_SIZE	number of instances in training file
N_FEATURES	number of features in data sets
DEPTH		maximum regression tree depth
N_TREES	number of regression trees to learn
RATE		learning rate/stepsize

-V, -E		validation/testing files
-v, -e		number of instances in validation/testing files
-m		compute and pring ranking-specific metrics, ERR and NDCG@10 [ranking/non-ranking data]
-t		print timing information
-h		show help message

Required input includes a training data set (filename, size, number of features) in SVM^rank or SVM^light format (http://www.cs.cornell.edu/people/tj/svm_light/index.html) and gradient boosting parameters (tree depth, number of trees, learning rate). **Note that in svm format, the first value should be target (dependent variable for trees). In my experiment I did not use (-m) argument because my data was not ranking.

Output alternates by line between a depth first traversal of the current regression tree and current metrics computed on data sets. Metrics lines may contain the following items (or fewer depending on command line options).
	Iteration, train_rmse, train_err, train_ndcg, valid_rmse, valid_err, valid_ndcg, test_rmse, test_err, test_ndcg

VI. Scripts
scripts/run.py [*wasn’t used in research*]
Edit this template script to call pgbrt with required arguments and capture the output. As provided, this script is configured to train on either Yahoo! LTRC Set 1 or Microsoft LETOR Fold 1. Use one of the following calls (for Yahoo or Microsoft data, respectfully) or modify the script as needed.
	python run.py PATH_TO_EXEC PATH_TO_DATA y NUM_PROCS NUM_TREES
	python run.py PATH_TO_EXEC PATH_TO_DATA m NUM_PROCS NUM_TREES

scripts/crossval.py
This script supports cross-validation on validation metrics computed by pgbrt. Script reads from stdin the trees and metrics output by pgbrt. It prints the trees set of tees selected by cross-validation. Cross-validation is performed on the metric indicated by VAL_METRIC_INDEX, e.g. 3 will cross-validate on the fourth metric in the comma-separated list printed by pgbrt. It is assumed that smaller metric values are better unless the -r option is specified.
	cat LOG | python crossval.py VAL_METRIC_INDEX [-r]

scripts/compiletest.py
Script compiles a lightweight C++ test executable for trees read from stdin, e.g. the output of crossval.py. Executable is written to EXEC_FILE. The default compiler command is ‘gcc -O3’, but an alternative may be supplied as COMPILER. |
	cat TREES | python compiletest.py EXEC_FILE [COMPILER]
	cat TEST_FILE | ./EXEC_FILE > PRED_FILE

scripts/evaluate.py
This script computes RMSE, ERR and NDCG metrics on predicitons provided in PRED_FILE using labels and queries found in TEST_FILLE.
	python  evaluate.py TEST_FILE PRED_FILE


scripts/evtools.py [*wasn’t used in research*]
This script was provided by Anath Mohan in his package rt-rank, which may be found at:
	https://sites.google.com/site/rtranking/home
The script incorporates a metric computation script originally provided by Yahoo! for the Leaning to Rank Challenge. The original may be found at this URL:
	http://learningtorankchallenge.yahoo.com/evaluate.py.txt
Here is the provided description:
“Script to compute the NDCG and ERR scores of a submission. Labels is a list of lines containing the relevance labels (one line per query). Ranks is a list of lines with the predicted ranks (again one line per query). The first integer in a line is the rank --in the predicted ranking-- of the first document where first refers to the order of the data file. k is the truncation level for NDCG. It returns the mean ERR and mean NDCG.” 
	
VII. LICENSE
Copyright © 2011, Washington University in St. Louis
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted profiled that the following conditions are met:
	* Redistribution of source code must retain the above copyright 
	notice, this list of conditions and following disclaimer.
	* Redistribution in binary form must reproduce above copyright 
	notice, this list of conditions and following disclaimer in the 
	documentation and/or other materials provided with the distribution.
	* Neigher the name of the <organization> nor the names of its
	comtributors may be used to endorse or promote products derived
	from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPRYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVANT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NECLICGENCE OR TOHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
