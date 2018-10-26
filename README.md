# Exponential-regression-using-Gradient-descent
This repository contains the code that does exponential regression using gradient descent optimizer. 
Consider the exponential regression, <a href="https://www.codecogs.com/eqnedit.php?latex=$y&space;=&space;a&space;e^{bx}$" target="_blank"><img src="https://latex.codecogs.com/gif.latex?$y&space;=&space;a&space;e^{bx}$" title="$y = a e^{bx}$" /></a>, after the log-transformation the equation becomes <a href="https://www.codecogs.com/eqnedit.php?latex=$log(y)&space;=&space;log(a)&space;&plus;&space;bx$" target="_blank"><img src="https://latex.codecogs.com/gif.latex?$log(y)&space;=&space;log(a)&space;&plus;&space;bx$" title="$log(y) = log(a) + bx$" /></a>.
Gradient Descent algorithm:
<a href="https://www.codecogs.com/eqnedit.php?latex=$SSE&space;=\sum{\hat{log(y)-&space;loga-&space;bx)}^2}&space;/&space;2n$" target="_blank"><img src="https://latex.codecogs.com/gif.latex?$SSE&space;=\sum{\hat{log(y)-&space;loga-&space;bx)}^2}&space;/&space;2n$" title="$SSE =\sum{\hat{log(y)- loga- bx)}^2} / 2n$" /></a>
Step 1: Initialize the weights(loga & b) with random values and calculate Error (SSE)

Step 2: Calculate the gradient i.e. change in SSE when the weights (loga & b) are changed by a very small value from their original randomly initialized value. This helps us move the values of loga & b in the direction in which SSE is minimized.

Step 3: Adjust the weights with the gradients to reach the optimal values where SSE is minimized

Step 4: Use the new weights for prediction and to calculate the new SSE

Step 5: Repeat steps 2 and 3 till further adjustments to weights doesn’t significantly reduce the Error
