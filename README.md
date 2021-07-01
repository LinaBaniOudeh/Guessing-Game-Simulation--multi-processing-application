# Guessing-Game-Simulation--multi-processing-application

 We would like to create a multi-processing application that simulates a guessing game
between 2 processes using signals. A parent process will create 2 children processes. We’ll
call the first child process P1 and the second child process P2.
The behavior of the whole system should be as follows:

1. Upon creation, the children P1 and P2 will be sensitive to signal SIGUSR1. The
   parent process will be sensitive to both signals SIGINT and SIGQUIT.

2. The parent process will ask P1 and P2 to pick a random integer number in the range
   [1 . . . 100].
3. Once they pick their numbers, P1 will write its picked number in the file P1.txt
   while P2 will write its picked number in the file P2.txt.
          
4. Once P1 finishes writing the number it picked in the file P1.txt, it informs the parent
   process.

5. Once P2 finishes writing the number it picked in the file P2.txt, it informs the parent
   process.

6. Upon being informed by P1, the parent process will read the picked number in file
   P1.txt.

7. Upon being informed by P2, the parent process will read the picked number in file
   P2.txt.

8. The parent process declares the round winner by comparing the numbers picked by
   P1 and P2. It increments a counter associated with the round winner process. If by
   chance P1 and P2 have both picked the same number, the parent process increments
   the counters of both P1 and P2. Afterwards, the parent process deletes the files
   P1.txt and P2.txt. This ends the current round.

9. Go to step 2. above unless the counter of either P1 or P2 has reached 10.
 
10. The parent process declares the winner of the game then kills P1 and P2 and exits.
    If both counters are 10, then both P1 and P2 are winners of the game.

