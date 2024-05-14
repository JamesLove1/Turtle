Testing.txt:
Please also refer to the respective test c files. 
As well as the shell script called test.sh.

Testing Parser:
1. Makefile  
I extended the Makefile in include commands to run all of the ./parse_s 
commands, ./interp_s and all of the Postscript commands. This enabled me  
to test all of the ttl files respective to the file i was working on. The  
make run command was insufficient for this purpose as it was only useful once 
I had created all of the .c files. Making this change helped me to test incrementally 
whether the code compiled correctly. 

2. Manually created TTLs within assert testing 
Originally, I had to load the TTLs to test the code. This required me to use a 
static length array allocated at compile time. I changed this to a variable 
length array so that at run time I could add as many words to the word array  
as I wanted. This also enabled me to make flexible word Array that I could  
edit which made my testing easier. 

3. Error codes for debugging 
When I first started to write the paser I would only output whether the code  
was not passing using "Error". I quickly found this irritating as there was  
no way for me to know which part of the paser the code was failing on. This  
lead me to start using error codes, so that I could locate which part of  
the code the error was appearing from. This gave me a place to start debugging   
from.  

4. Bool returns to send to control logic 
When I started the Parser I was using Void returns. This meant I would have to  
rely on the struct, or pointer variables defined in the function definition to  
show whether a function was passing or not. As this meant that the functions  
were not fully reversive. Secondly this made the code cumbersome to small  
changes.  

5. Number from string  
Originally, I was doing this by match the string and if they were True with a  
particular number I would output the corresponding number. This created bugs  
so instead I changed it so that I sscanf in the number checking the return  
value from sscanf and that a '\0' was present. 

6. Changing error code: "error with file" to "TTLS FILE PATH IS INCORRECT" 
When I first wrote the code, I used a standard Error Message as there was 
only one argument. When I extended the code in the extension to use more  
than one I needed a way to be able to tell which input was causing the  
error. This meant that I added a new error code specific to which input  
was not working. This made it much easier to debug the code when inputting  
the wrong input.  

7. variable length word array  
When I first created the file, I used a normal array. This lead to issue  
in the instance of testing my code as it would overflow. I quickly  
changed this over to a variable length array to prevent this in the 
future.   

Testing Interp: 
1. make file command for just interp - ps and ASCII and text files  
See 1. within the "Testing Parser:" section above. 

2. Dynamic array of words  
See 7. within the "Testing Parser:" section above. 

3. Drawing - issues with Int and Double 
Originally, I was using Ints to calculate the Trigonometry for the  
coordinates. This was so that I could translate them into  
coordinates for the 2D array called screen. The issue behind this  
was that this was not an accurate way to calculate the coordinates.  
Type Int floors the values. To get around this I started using  
Doubles to calculate the coordinates. This however had the issue  
that I would then have to convert them back into Ints for the coordinates 
for the 2D Array called screen. To do this by rounding the double and  
then casting the rounded number into and Int. This is a lot more accurate  
as the rounding function will round up and down. While the Int just  
Floors the number. 
  
4. Trigonometry - 0 Degrees Stright Up 
When I initially implemented the Trigonometry it would output 0 degrees  
horizontally. This was a huge issue as I was not able to calculate the  
coordinate correctly. To change this, I altered the Trigonometry so  
that turtle_y was Minus deltaY. which in turn was -distance *  
cos(angleInRadians) this in turn flipped where 0 degrees was pointing  
up and not horizontally.    

5. Which Output and Output structure 
Originally, I would just put the output function where I though was  
appropriate. This had the issue that this did not always lend its  
self to the recursive nature of the function. The outputs in this  
instance would not be correct. To change this I created a function  
to work out which output should be used. this was placed at the  
start of the program. An output function was then placed within the  
body of the program. this meant that the program could call it within  
its recursive functions. this output would then call the relevant  
output function e.g. ASCII_Screen etc. This improved the output of the  
files massively as the output function was being called Mutiple times  
in line with the recursive nature of program and not once the program  
had ended.    

6. Use of TESTING ARGV[2] 
When the ./interp_s program is called with a TTL file it should output  
to the terminal using ASCII character. This is all well and good when  
running it for a user. However, for testing this is a nightmare, as the  
ASCII output covers up most of the error messages and printf's used for  
debugging. To rectify this issue, I included an extra keyword called  
TESTING that is to be place in argv[2]. When TESTING is used no output  
is produced. This allowed me to see the error messages in more detail  
as well as to see the printf's. 

7. LOOP debugging   
Within the LOOP function I had a heavenly nested set of If's this  
was a huge issue to debugging and including the interper code for LOOP.  
I ended up spending most of my time just trying to understand my code  
and struggled to debug it. To rectify this issue, I used Gard statement 
instead, which allowed me to reengineer the code to not have anywhere  
near the same amount of nested if statements. This subsequently enabled 
me to implement the loop interp function correctly.  
  
8. LOOP 
In my initial implementation of loop, I created a LOOP_interp function that  
did the interpreting just before the LOOP function evaluated to be true.  
this caused many issues as I would have to go back figure out were  
to start the loop. This was a real issue to implement. I eneded up  
going back to the drawing board where I figure why not combine the two,  
in terms of functionality. This was a massive change in terms of thought  
as it enabled me to have variables within the LOOP function which saved  
the index of certain important information. It did also mean that I had  
to reengineer functions that LOOP relied on to take pointer variables so  
that this data was available within the LOOP variable scope. When it came  
to implement the for loop this made it much easier as I could use these  
variables. Instead of having to do a massive amount of index manipulation.  

9. Postscript 
I originally tried to use the trigonometry from earlier on in my program.  
This ended up throwing loads of bugs towards me as it was designed around 
intimately outputting coordinates for the 2D array screen. To rectify the  
issue I had to create two new Postscript x and y doubles to store the  
postscript x and y coordinates. I also had to stop looping though draw  
coordinate's function. this made my coordinates a lot more accurate and  
enabled them to be displayed nicely within the postscript outputs.  

10. Stack - push and pushStr   
Within my first initiation I used Char for my array. However, I quickly  
found out this was a massive error as intimately i wanted to calculate  
Doubles. This led me to change my array to doubles to prevent these issues.  
The side effect of this was that I had to create two different versions  
of the push command. One for taking strings from the wordarray converting 
the value and then pushing the converted value onto the stack. the other 
for just pushing doubles onto the stack.  

11. setVar function  
Back at the start of the project I set my variables to hold numbers as  
Ints as I was not aware that the set functionality would actually need  
to use doubles. As such when it came to converting the final number to  
a var it would floor the result. To stop this, I converted the variable  
number type to double and made sure not to cast the value to an Int. 

Extension:
1.PROG
Originally when I created the extension function, I did not take into  
account that if I put PROG inside of a while loop the PROG values  
would have issues when printing it out using the ASCII_screen function.  
This is because every time PROG is called it updates its values. This, 
is good normally until you realise all of the values are massively out.  
to get around this we wanted to retain the wordArray between loops  
though reset all the other values to their defaults. Though to make  
sure, the values did not become distorted we reset all the other values  
back to their defaults. This meant that the values were now being  
calculated correctly. 

BlackBox testing: 
For Blackbox testing I used a shell script called test.sh. This file  
can be found within the /Testing DIR. I started off by moving the CWD 
to be the same as test.sh. This was then followed by testing whether  
the right executables were present to run the files. Once this has  
been completed I test them to see if the right exit codes are produced  
when I run them with ./parse_s and ./interp_s. I then run a test using 
Valgrind to see if there are any memory leaks using both files. Now 
that I know that the right error codes are being produced and that  
there are no memory leaks I move on to test that the right files  
are produced when I run them with the TTLs and store them in  
a temporary folder called ./temp using the ./interp_s executable. Post 
this I zip all the relevant files and use a check to make sure that they  
are present within the ./turtle folder produced ready to be uploaded  
for Neil. 