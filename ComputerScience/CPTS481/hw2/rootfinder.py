#Homework #2
#rootfinder.py
#CPTS481
#Alex Hortin
#10732085

#Bisection method
def root_find(f, xlo, xhi, eps):
	xcheck = xhi	
	for i in range(1000):
		flo,fhi = f(xlo),f(xhi)
		x = xlo - (flo*(xhi-xlo)) / (f(xhi) - f(xlo))
		if (abs(x - xcheck) < abs(x) * eps): return x
		else:
			xcheck = x
			if (f(xlo)*f(x) > 0):
				xlo = x
			else:
				xhi = x
		if  (f(xhi) - f(xlo)) == 0:
			return x
	return 
	
if __name__ == '__main__':
	def func(x):
		return float((-5*(x**3))-(4*(x**2))+(3*x)+2)	
		#return float(x**2)	
	print "root is " + str(root_find( func, (0), (1), (10**-6)))
	
