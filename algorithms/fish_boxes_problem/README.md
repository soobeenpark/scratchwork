## Practice Problem for Dynamic Programming

### Selling Fish Boxes

Problem Statement:

Suppose there are two stacks of fish boxes, each with labelled weights on them.
For example,

 fish stack1:   top [40kg, 10kg, 50kg] bottom
 fish stack2:   top [20kg, 20kg, 60kg] bottom

 We want to sell all the fish to make a profit. Say the amount of money sold is proportional to the weight (ie. 1kg = $10). Our goal is to sell the fish in a way to maximize the profit.

 On each day, only one of the boxes at the top of either stack can be sold. So in the example, we must choose between selling 40kg from stack1 or 20kg from stack2 on the first day.

 Every day, the value of the remaining fish not sold decreases by 0.9 times its original value because it becomes less fresh. So for example, if we sold 40kg from stack1 on day 1, and 20kg from stack2 on day 2, then the overall profit would be $10 * (40 + 0.9\*20) = $580. Continuing the example, if we sell 10kg from stack1 on day 3, then the profit until day 3 would be $580 + $0.9\*0.9\*10 = $588 (we round down to the nearest integer).

Devise an algorithm to sell all the fish from both stacks while maximizing profit, keeping in mind that value decrease as freshness decreases. In the example, the max profit should be $1540.25


