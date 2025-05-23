<img height=200 src="https://github.com/user-attachments/assets/a57c1548-0157-4edd-afd5-e1f0ef83ff22">

### Yet to do :
- Reading about the NVIDIA course.<br/>
- Coming up with a rough solution for making sure if the ZMP can be solved even if the matrix is sized down using an anti-offset</br>
- Come up with a way to apply probabilistic pruning in order to eliminate 2x2 minor calculation.<br/>

### Done :
✅ Running NTL examples : ZZ_p matrix programs.<br/>
✅ Finding the count of (n-1) x (n-1) sub-matrices in nxn matrices.<br/>
✅ Finding all 2x2 and 3x3 (in general nxn minors) in a bigger matrix. <br/>
❌ (Incorrect) Optimize general nxn matrix program to a matrix that is created within a specific field of a 15-30 bit prime number, and calculating their determinants and keeping count of the determinants that are 0, i.e the count of Zero Minors in that matrix.<br/>
✅ Trying to integrate NTL and OpenMPI.<br/>
❌ (Incorrect) Dividing the minor calculations and process of getting the minors in 4 processors, each of which will get 'n' combinations for the minor indices each.<br/>
✅ Reading about 'finite fields'.<br/>
❌ (Incorrect) Trying out the written 'kth-combination with OpenMPI' code on the server with more than 4 processors and gauging the performance.<br/>
✅ Correcting the program, first in a serial manner, then using parallel computing - Program for getting (n-1) minors by dividing the number of minors evenly among all processors.<br/>
✅ Configured Master-Slave architecture for 6 servers using password-less ssh, nfs, rsync (48 processors are working).<br/>
✅ Setting up Raspberry Pi as a master and laptop as the slave.<br/>
✅ Understanding the send, receive, broadcast and barrier functions of OpenMPI.<br/>
✅ Getting the determinants of consecutive 2x2 minors and if the determinant is 0, then storing the minor in a file.<br/>
