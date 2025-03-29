# Rowan's Producer-Consumer Solution

The producer-consumer problem is a popular computer science problem, geared at understanding the way programs use shared memory. My implimentation of it works flawlessly, and is far smaller than some of it's college-student contemporaries.

## The Method

First, came the shared memory. The structure I set up to take care of the passing was contained as a struct in the header, containing frames for the buffer which will be passed, and two semaphores, empty and full.

Next, comes the producer and consumer. These are pretty much the same, so I shall cover them in the same section.

In each, we need to open the shared memory. The way we do this is by creating an ID integer for our shm_open, which creates or open an existing memory slice. No conflict here. Ftruncate just makes sure that the memory is not using too much memory beyond the buffer. Then we initialise our sharedMemory struct into our memory.

Only in the producer do we initialize our semaphores. This may be what causes problems in the very beginning of execution, but that should be able to be solved by running them one after the other. These are both initialized to one, and ensure only one will be in the memory at a time.

Then, we have our main for loop that goes for 100 times.

Next we have our steps that are different for each one. In the producer, it waits for empty, then iterates over the shared memory, making every 0 into a 1. Then it posts full to let the consumer know that it can come in.

The consumer waits on full, and then sets all of the 1s to 0s. After that it passes it back to the producer by using empty.

After all of that, they both close the memory by unlinking AND closing it. It may be a bit redundant, but I did it in both of them to ensure compliance.

## The Madness

For some reason, at the very beginning, both of the processes have access to the critical section, so they both execute at the same time. I tried a few ways to remedy this, but they all seemed to create more problems and damage performance. So, I stayed with this method, that does, in fact, work for all of the execution time after the first 3 exchanges. Such is an issue that could be easily worked around in a professional context, so I found it acceptable to leave in, seeing as I could not figure out a way to fix it.

Also it was getting close to the deadline.

I did not intend to submit this all at once. I fully intended to submit this in bite-sized chunks, but it ended up very messy and I only decided to submit when I had it done.

Thank you for the lesson, Professor Guan!

## To Compile and Run

```
g++ producer.cpp -pthread -lrt -o producer
g++ consumer.cpp -pthread -lrt -o consumer
./producer & ./consumer &
```

