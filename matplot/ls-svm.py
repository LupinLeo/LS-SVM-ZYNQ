# -*- coding: utf-8 -*-
"""
Created on Tue Jun  5 20:24:11 2018

@author: Administrator
"""

import numpy as np
import matplotlib.pyplot as plt


x = np.arange(3.5, 7, .01)
y = np.arange(0.5, 2.5, .01)
goodData=np.array([[4.7,1.4],[4.5,1.5],[4.9,1.5]])
badData=np.array([[6,2.5],[5.1,1.9],[5.9,2.1],[5.6,1.8]])
x, y = np.meshgrid(x, y)
f = 0.3692*np.exp((-1)*(pow((x-4.7),2)+pow((y-1.4),2))/0.5)+0.4189 *np.exp((-1)*(pow((x-4.5),2)+pow((y-1.5),2))/0.5)\
+0.5858*np.exp((-1)*(pow((x-4.9),2)+pow((y-1.5),2))/0.5)-0.2916*np.exp((-1)*(pow((x-6),2)+pow((y-2.5),2))/0.5)\
-0.6570*np.exp((-1)*(pow((x-5.1),2)+pow((y-1.9),2))/0.5)-0.2126*np.exp((-1)*(pow((x-5.9),2)+pow((y-2.1),2))/0.5)\
-0.2126*np.exp((-1)*(pow((x-5.6),2)+pow((y-1.8),2))/0.5)-0.362203
t = 0.3292*np.exp((-1)*(pow((x-4.7),2)+pow((y-1.4),2))/0.5)+0.4302 *np.exp((-1)*(pow((x-4.5),2)+pow((y-1.5),2))/0.5)\
+0.9177*np.exp((-1)*(pow((x-4.9),2)+pow((y-1.5),2))/0.5)-0.3563*np.exp((-1)*(pow((x-6),2)+pow((y-2.5),2))/0.5)\
-0.9709*np.exp((-1)*(pow((x-5.1),2)+pow((y-1.9),2))/0.5)-0.0977*np.exp((-1)*(pow((x-5.9),2)+pow((y-2.1),2))/0.5)\
-0.2520*np.exp((-1)*(pow((x-5.6),2)+pow((y-1.8),2))/0.5)-0.2463
d = 0.3463*np.exp((-1)*(pow((x-4.7),2)+pow((y-1.4),2))/0.5)+0.4054 *np.exp((-1)*(pow((x-4.5),2)+pow((y-1.5),2))/0.5)\
+0.4056*np.exp((-1)*(pow((x-4.9),2)+pow((y-1.5),2))/0.5)-0.2896*np.exp((-1)*(pow((x-6),2)+pow((y-2.5),2))/0.5)\
-0.2893*np.exp((-1)*(pow((x-5.1),2)+pow((y-1.9),2))/0.5)-0.2893*np.exp((-1)*(pow((x-5.9),2)+pow((y-2.1),2))/0.5)\
-0.2893*np.exp((-1)*(pow((x-5.6),2)+pow((y-1.8),2))/0.5)-0.4214
g=pow(x,2)/4+pow(y,2)/9
plt.figure()
plt.contour(x, y, t, 0)
plt.scatter(badData[:,0], badData[:,1], marker = 'o', color = 'k', s=10, label = u'坏')  
plt.scatter(goodData[:,0],goodData[:,1], marker = 'o', color = 'g', s=10, label = u'好')  
plt.show()
