"""
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143?

Solution comment:
Implementing a priority queue, where for each iteration, the largest
element is selected and attempted to be divided in two parts. If
this succeeds, then the parts are added to the queue. If it does
not succeed, the largest prime is found.

This also keeps the list in sorted order, so finding max of queue
is O(1).
"""

def greatest_prime_factor(n):
    queue = [n]
    while True:
        print "queue =",
        queue
        g = queue.pop(0)
        div = 2
        while div < g:
            if g % div == 0:
                queue = [g // div, div] + queue
                break
            div += 2 - int(div == 2)

        if queue[0] != g // div:
            return g


n = 600851475143
print greatest_prime_factor(n)
