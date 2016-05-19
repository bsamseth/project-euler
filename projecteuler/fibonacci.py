"""This module gives several ways of computing the Fibonacci numbers"""

def fibonacci_generator(F1=0, F2=1, maxindex=None):
    """Generate Fibonacci numbers, starting with F1 and F2.
    If no max index is given, all numbers will be yielded in succesion.
    maxindex is inclusive, and 1-based, i.e. fib(maxindex=4) -> [0, 1, 1, 2]."""
    from itertools import count, islice
    Fp = F1
    F = F2
    yield Fp
    for i in islice(count(), 2, maxindex+1):
        yield F
        Fp, F = F, F + Fp


def F(n):
    """Calculate n-th Fibonacci number using closed form expression.
    Note, this is only accurate for F(i) for i in [0, 124]. Diviation
    of 1 for i = 125, and worse after that.

    This can be improved by:
        from decimal import getcontext
        getcontext().prec = <wanted precision>

    With prec set to 100, F(i) is accurate up to i = 471.
    With prec set to 212, F(i) is accurate past i = 1000
    """
    from decimal import Decimal
    sqrt5 = Decimal(5).sqrt()
    numerator = (Decimal(1) + sqrt5)**Decimal(n) - (Decimal(1)-sqrt5)**Decimal(n)
    denomenator = Decimal(2)**Decimal(n) * sqrt5
    return int((numerator / denomenator).to_integral_value())

if __name__ == '__main__':
    from decimal import getcontext
    getcontext().prec = 212
    for i, fib in enumerate(fibonacci_generator(maxindex=1000)):
        assert fib == F(i), 'i={0}, fib={1}, F(i)={2}'.format(i, fib, F(i))
