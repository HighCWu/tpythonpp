## The Fibonacci Sequence ##

def fib(n):
	if n == 0:
		return 0
	elif n == 1:
		return 1
	else:
		return fib(n-1) + fib(n-2)

def run_test():
	a = fib( 32 )
	print(a)

def main():
	print('enter main...')
	run_test()

main()
