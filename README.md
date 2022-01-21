# Flow
created in 2 days about 15 hours of work. 

creates simulation of matching students with schools

Input the amount of students and the amount of schools (max 100 for each). 

Next, it will create a random amount of matches(n) from 0 to numSchools.
Additionally, each school will allow 0-numStudents to connect to it.

Then it will create a connection to a random school n amount of times.

Also, these connections will be ranked from 1 being best to n being the worse.

After, it will run the Ford-Fulkerson algorithm to get the max-flow(maximum student-school matches).

Now it will look to see if it can switch some connections to get the max total happiness.

Here I define max total happiness as the best rankings that can possibly be achieved without creating illegal connections or decreasing the maximum student-school matches.

After it gets all this data, SDL is used to render the data visually on the screen. the first and last row show the schools in the same order. The middle shows the students and each student is colored to make it more asthetically pleasing. The top half shows every connection POSSIBLE to visually show how many possible combinations there are. The bottom half emulate the BEST possible combination. The schools are also color coded to show what the student ranked the school they are going to. 

colors for places are emerald, plat(blue), gold, ruby, bronze, and white 
emerald being best, (First place) plat, (second place) etc (white is anything worse than 5th place)


# Everything works except 10 students and 10 schools. i have no idea why but it results in 2 connections. 
