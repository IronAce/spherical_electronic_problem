#!/usr/bin/env python3

from numpy import linspace
from numpy import loadtxt
import matplotlib.pyplot as plt
from numpy import cos
from numpy import sin

a   =   loadtxt( "legendre_pols.out" )
x   =   linspace( -1 , 1 , 100 )

y   =   x
y   =   -(1.0-x**2)**(1/2)
y   =   ( 1 / 2 ) * ( 3 * ( x**2) - 1 )
y   =   -3 * x * ( 1 - x**2 )**( 1 / 2 )
y   =   3 * ( 1 - x**2 )
y   =   ( 1 / 2 ) * ( 5 *( x**3 ) - 3 * x )
y   =   -3/2 * ( 5*x**2 - 1 ) * ( 1 - x**2 )**( 1 / 2 ) 
y   =   15 * x * ( 1 - x**2 ) 
y   =   -15 * ( 1 - x**2 ) ** ( 3/ 2 ) 



plt.plot( x , y , label='orig' )
plt.plot( a[ : , 0 ] , a[ : , 10 ] , label='calc' )
plt.legend()
plt.show()

