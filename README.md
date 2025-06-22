<h1 align="center">MSc(Scientific Computing) Project 2024-25</h1>
<h3 align="center">(This is a repository that contains all the things I've done, related to my MSc(Scientific Computing)<br/>semester-2 research-based project.)</h3>
<h2 align="center"> ECDLP (Elliptic Curve Discrete Logarithm Problem) </h2>

### Project Aim :
Given a big matrix, later reduced using an anti-offset (of say, 0.2 or 0.3 that is, 20-30%), the aim is to check whether the zero minor problem can still be solved using this reduced matrix. 

### Project Description : 
- Things to prove :
  1) Is the anti-offset useful?
  2) If yes, what is the good value for the anti-offset within the range 0 to 1 (as the matrix has to be shrunk)?
     -  Values of anti-offset that have already been tested : 0.2, 0.3, that is a 20-30% reduced matrix.
    
### Approach :
1) Brute force : Getting each and every minor from the given matrix and checking if its determinant is 0.
2) The Latecomer's Algorithm : Checking to see if in some way the calculation of the determinant of the 2x2 minors can yield some useful results such that the calculation of the determinants of the minors dependent on these 2x2 minors can be eliminated or reduced in some way using probabilistic pruning, since there are only 2 possibilities : either the determinant is 0, or it is not, so in a way reducing calculations to some amount (given that the algorithm works).
</br>

## Elliptic Curve :

> Note : At certain values of 'a' and 'b', the curve is divided into components.

https://github.com/user-attachments/assets/c72a7632-273e-4495-a993-21380324cdc3

<p align="center"> (Made using Desmos) </p>

## Double and Add Algorithm

https://github.com/user-attachments/assets/5f95fba4-1cac-4156-9366-b93e4c9d58fa

<p align="center"> Reference : https://www.youtube.com/watch?v=bLktMcHuyYE </p></br>

### Things I've Learnt Till Date : 
- Parallelizing tasks amongst available processors : setting start and end indices for each processor to work on a single matrix parallelly.<br/>
- Using functions like MPI_Barrier(), MPI_Bcast(), MPI_Finalize(), MPI_Comm_size(), MPI_Comm_rank()
- Getting familiar with NTL by using datatypes like ZZ_p, mat_ZZ_p, etc.
- Basics of what Finite Fields are.
- Double and Add algorithm along with what ECDLP is.
- Configuration of Master-Slave architecture in a cluster containing 6 working servers using password-less ssh, nfs, rsync.
- Getting familiar with basic Bash Scripts.
