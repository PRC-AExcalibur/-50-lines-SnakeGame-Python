#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np
import os,keyboard,time,threading
#初始设置
side=np.array([10,10],dtype=int)     #屏幕尺寸（行列,YX）
fps=int(2)                           #帧率(每秒移动格子数)
length=int(2)                        #蛇长度（初始）
direction=np.array([1,0],dtype=int)  #方向向量
snake=np.array([np.ceil(side/2),np.ceil(side/2)-direction])   #蛇身体位置
applelist=np.array([4,2],dtype=int)  #苹果可能出现的空间
apple=applelist      #苹果位置


# In[2]:


while fps!=-1:     
#键盘输入
    if keyboard.is_pressed("s") and all(direction != np.array([-1,0])):
        direction=np.array([1,0])
    elif keyboard.is_pressed("w") and all(direction != np.array([1,0])):
        direction=np.array([-1,0])
    elif keyboard.is_pressed("d") and all(direction != np.array([0,-1])):
        direction=np.array([0,1])
    elif keyboard.is_pressed("a") and all(direction != np.array([0,1])):
        direction=np.array([0,-1])
#主程序
    snake= np.vstack((snake[0]+direction,snake)).astype(np.int32)
    if all(snake[0]==apple):
        length=length+1
        rdm=np.random.randint(0, np.shape(applelist)[1],dtype=int)
        apple=np.array([applelist[0,rdm]+1,applelist[1,rdm]+1])
    snake.resize(length,2)
    screen=np.zeros(side)
    if any(snake[0]>side) or any(snake[0]==0) or any((snake[1:]==snake[0]).all(1)):
        fps=-1
        print("fail")
    elif length==side[0]*side[1]-1:
        fps=-1
        print("success")
    else :
        for i in range(0,length) :
            screen[apple[0]-1,apple[1]-1]=8
            screen[snake[i,0]-1,snake[i,1]-1]=1
            applelist=np.array(np.where(screen==0))  
        i = os.system('cls')
        print("SCORE:%a   FPS:%a   Side:X%a * Y%a"  %(length-2,fps,side[1],side[0]))
        print((str(screen).replace("0"," ")).replace("8","*"))
#时间循环    
        time.sleep(1/fps)


# In[ ]:




