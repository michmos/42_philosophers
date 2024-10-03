# 42 Philosophers

## About the Project
### Task
This project serves as an introduction to multi-threading. The program simulates multiple philosophers sitting around a table with one common pot of pasta. 
There are as many forks on the table as there are philosophers. Eating requires two forks, so the philosophers compete for them. The program takes
the following parameters (all times in milliseconds):
- Number of philosophers
- Time to die
- Time to eat
- Time to sleep

The philosophers eat, sleep, think (no time specified), and repeat. If the `time to die` has passed since the start of the last meal, the philosopher dies. As soon as
a philosopher dies, the simulation ends. All activities need to be printed to stdout with a respective timestamp. The output should not be mixed up. 
If possible, the philosophers should not die — requiring your program to be efficient and fast. Furthermore, the 'dead' message needs to be printed within 10 milliseconds
of the event actually happening. 

## Learnings
This project introduced many new concepts since it was my first time writing a multi-threaded program. I learned about:
- Protection of shared memory through pthread mutexes to prevent data races
- Prevention of deadlocks
- Debugging threads

## Utilization
### Cloning
Run the following command to clone the repository and build the executable:
```
git clone https://github.com/michmos/42_philosophers.git && cd 42_philosophers && make
```
### Running
Run the executable with the arguments listed above:
```
./philo 200 420 200 200
```
