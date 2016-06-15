The objective of the program is to shoot the green target. 

When you miss the target, a red X will appear. 

If you hit the target, the target will stop moving and flash red.

There is nothing that keeps score.

Controls:

m : If target is still, target starts moving in a random direction. If target is moving, it will stop.

\+ : Increases target’s move speed

\- : Decreases target’s move speed

a : moves tank left

d : moves tank right

w : raises tank nozzle

s : lowers tank nozzle

space bar : shoot bullet

esc : resets to beginning position and speed

q : quits the program

Mouse click/drag:  Nozzle points to pointer

I made this in Xcode on a mac. The Sleep() function on line 128 should be changed to work on Windows. If not, it should be sleep() on the mac.

For instructions to run the OpenGL project in Xcode on mac, go here:
http://csns.calstatela.edu/site/s16/cs450-1/item/5384003

For instructions to run the OpenGL project in visual studio on Windows, go here:
http://in2gpu.com/2014/10/15/setting-up-opengl-with-visual-studio/