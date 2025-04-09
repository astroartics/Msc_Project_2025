<h1 align="center">MSc(Scientific Computing) Project 2024-25</h1>
<h3 align="center">This is a repository that will contain all the things I've done, related to my MSc(Scientific Computing)<br/>semester-2 research-based project.</h3>
<br/>

Project Title : ECDLP (Elliptic Curve Discrete Logarithm Problem)
<br/>Problem Statement : Trying to verify if the matrix that is shrinked using an anti-offset, can be reduced to the Zero Minor Problem. 
<br/>Project Description :
<br/>

## Elliptic Curve :

> Note : At certain values of 'a' and 'b', the curve is divided into components.

https://github.com/user-attachments/assets/c72a7632-273e-4495-a993-21380324cdc3

<br/>Methods or Approach Being Followed : 
<br/>Things I've Learnt Till Date : 
- Parallelizing tasks amongst available processors : setting start and end indices for each processor to work on a single matrix parallely.<br/>
- Using functions like MPI_Barrier(), MPI_Bcast(), MPI_Finalize(), MPI_Comm_size(), MPI_Comm_rank()
- Getting familiar with NTL by using datatypes like ZZ_p, mat_ZZ_p, etc.
- Basics of what Finite Fields are.
- Double and Add algorithm along with what ECDLP is.

## Double and Add Algorithm

https://github.com/user-attachments/assets/5f95fba4-1cac-4156-9366-b93e4c9d58fa

Reference : https://www.youtube.com/watch?v=bLktMcHuyYE
