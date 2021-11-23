from math import *
theta = 5.57
r = 28.6
d1 = 1.1
d2 = r-d1
print('(r*sin(theta/180*pi))=', (r*sin(theta/180*pi)))
print('sqrt(r**2 + d2 ** 2 - 2*r*d2*cos(theta/180*pi)))=',
      sqrt(r**2 + d2 ** 2 - 2*r*d2*cos(theta/180*pi)))
alpha = asin((r*sin(theta/180*pi)) /
             (sqrt(r**2 + d2 ** 2 - 2*r*d2*cos(theta/180*pi))))
print('alpha', alpha)
if(alpha*2 > pi):
    print('alpha > pi/2')
else:
    print('alpha < pi/2')

d = sqrt(r**2 - (d2*sin(theta/180*pi)) ** 2) - d2*cos(theta/180*pi)
print('d = sqrt(r**2 -(d2*sin(theta/180*pi)) ** 2) - d2*cos(theta/180*pi) ', d)
