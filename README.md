# pplsd_mubqp_sequential
# A sequential version of PPLS/D for solving the multiobjective UBQP problem
# Jialong Shi (jialong.shi@xjtu.edu.cn)



## Introduction

In this program, a sequential version of PPLS/D (Parallel Pareto Local Search based on Decomposition) is implemented to optimize the multiobjective Unconstrained Binary Quadratic Programming (mUBQP) problem. It returns an approximation of the Pareto optimal solution set of the input mUBQP instance. The original PPLS/D is a parallel algorithm with multiple parallel processes. This implementation sequentialize the original PPLS/D by simply executing the processes one by one. Hence, this program does NOT require parallelization libraries like MPI. 

** The MPI parallel version of this program is available at https://github.com/JialongShi/pplsd_mubqp

The code is distributed for research use. The author reserves all rights to the code.

Relevant literature:

[1] Shi J, Zhang Q, Sun J. PPLS/D: Parallel Pareto local search based on decomposition[J]. IEEE transactions on cybernetics, 2020, 50(3): 1060-1071.

[2] Shi J, Zhang Q, Derbel B, et al. Using parallel strategies to speed up Pareto local search[C] Asia-Pacific Conference on Simulated Evolution and Learning. 2017: 62-74.



## The mUBQP problem

The mUBQP problem can be formalized as follows

maximize  f_k(x) = x^T * Q_k * x,    k=1, ... ,m 

where a solution x = (x_1, ... ,x_n) is a vector of n binary (0-1) variables and Q_k = [q^k_{ij}] is a n * n matrix for the k-th objective. Hence the k-th objective function is calculated by f_k(x) = \sum_{i=1}^{n} \sum_{j=1}^{n} q^k_{ij} * x_i * x_j. The UBQP is NP-hard and it represents the problems appearing in a lot of areas. In this program, the neighborhood structure in the mUBQP is taken as the 1-bit-flip, which is directly related to a Hamming distance of 1.

The details of mUBQP are described in:

[3] A. Liefooghe, S. Verel, J-K. Hao, A hybrid metaheuristic for multiobjective unconstrained binary quadratic programming. In Journal: Applied Soft Computing, vol. 16, , p. 10-19, 2014.



## File list (the following files should be in the same directory)

- Source code: main.cpp  problem.h  problem.cpp  solution.h  solution.cpp  archive.h  archive.cpp  misc.h  misc.cpp  pplsd.h  pplsd.cpp

- Problem file examples: example_mubqp_m2_n200.dat example_mubqp_m3_n100.dat

- Weight vector file examples: example_wv_m2_6procs.txt example_wv_m3_15procs.txt

- cmake file: CMakeLists.txt



## How to compile it

CMakeLists.txt has been provided for compiling the program by cmake on linux (such as Ubuntu), so make sure that cmake has been installed. Then you can compile the project by running

```
cd <directory-of-this-program>
cmake CMakeLists.txt
make
```

Then an executable named ???pplsdsv??? will appear in the directory. 

!!! If the cmake command or the make command is failed, you can directly compile the program by the following command. 

```
g++  -o  pplsdsv  -O2  main.cpp  problem.cpp  solution.cpp  archive.cpp  misc.cpp  pplsd.cpp
```



## How to use it

You can run the program by

```
./pplsdsv  <problem_filename>  <weight_vector_filename>  <process_num>  <max_runtime>
```

** Describes **

- <problem_filename>: This argument is the input mubqp problem filename. We have given two example problem files in the package. Both are generated by the mUBQP generator which is available at http://mocobench.sourceforge.net

-  <weight_vector_filename>: This argument is the file describes the weight vectors of different PPLS/D processes. The format is 

         <process_ID>  <weight_value_1>  <weight_value_2> ... <weight_value_M>

Note here that the process ID must start from 0, the weight vector dimension M should be equal to the objective number of the input problem, and the weight vector number (i.e. the line number) should be equal to the third argument <process_num>. We have given two example problem files in the package.

- <process_num>: This argument is the process number of PPLS/D. Again, it should be equal to the weight vector number in the input weight vector file.

- <max_runtime>: This argument is the runtime budget. The units are seconds. Note here that PPLS/D may converge and finish before the time budget. Since this is a sequential version of PPLS/D, each process???s runtime budget will be <max_runtime>/<process_num>.

** Example **

```
./pplsdsv  example_mubqp_m2_n200.dat  example_wv_m2_6procs.txt  6  60
```

The above command runs a 6-process PPLS/D on a 2-objective mUBQP. The runtime budget is 60s.



## Outputs

After finish, the program will create a file named ???result_final.txt??? in the same directory. It lists the solutions in the final archive of PPLS/D. The first line is the solution number in the final archive. The second line are the objective number M and the dimension N of the problem. From the third line to the end, each line indicates a solution. In each line, the first M values is the objective function vector of the solution and the last N values are the variable values of the solution. The format can be summarize as

     <solution_num>
     <obj_num_M>  <dim_N>
     <obj_value_1> <obj_value_2> ... <obj_value_M> <var_1> <var_2> ... <var_N>
     ... ...

The program also will output the sub-archive of each process, which are listed in the files ???result_process0.txt???, ???results_process_1.txt???, ...


## Visualization

For 2-objective or 3-objective problems, the following MATLAB script can help to visualize the result. Remember to modify the values of ???m???, ???procs_num??? and ???dir??? before using the script.

```
clear all
close all
clc

m = 3;
procs_num = 15;
dir = '.';

figure()
for procs_index = 0:procs_num-1
    filename = sprintf('%s\\result_process%d.txt',dir,procs_index);
    res = read_result_file(filename);
    if m == 2
        scatter(res(:,1),res(:,2));
        hold on
    elseif m == 3
        scatter3(res(:,1),res(:,2),res(:,3));
        hold on
    end
end
hold off


function result  = read_result_file( filename )

    result = [];
    FID = fopen(filename, 'r');
    if FID == -1 
        disp(['ERROR: cannot open file',filename]);
    else
        archiveSize = fscanf(FID, '%d', 1);
        if archiveSize > 0
            m = fscanf(FID, '%d',1);
            n = fscanf(FID, '%d',1);
            result = zeros(archiveSize,m+n);
            for line = 1:archiveSize
                fit = fscanf(FID, '%lf',m);
                sol = fscanf(FID, '%d',n);
                result(line,:) = [fit; sol]';
            end
        end
        fclose(FID);
    end

end
```


