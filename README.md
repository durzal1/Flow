# Flow
created in 2 days about 15 hours of work. 

creates simulation of matching students with schools

Input the amount of students and the amount of schools (max 100 for each). 

Next, it will create a random amount of matches(n) from 0 to numSchools.

Then it will create a connection to a random school n amount of times.

Also, these connections will be ranked from 1 being best to n being the worse.

After, it will run the Ford-Fulkerson algorithm to get the max-flow(maximum student-school matches).

Now it will look to see if it can switch some connections to get the max total happiness.

Here I define max total happiness as the best rankings that can possibly be achieved without creating illegal connections or decreasing the maximum student-school matches.

After it gets all this data it will use SDL to draw it visually on the screen.
