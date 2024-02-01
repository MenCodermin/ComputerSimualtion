# ComputerSimualtion
 Assignment of Computer Simulation course

For my simulation for Part 1 I used matplotlibcpp, which is originally was migrated from Pyton libraries, so if you desire to change some values and compile the code you, first of all, you have to download Python compiler (you can find instructions in YouTube or everywhere), then you need to download library called matplotlibccp.h, which you can download there:
https://github.com/lava/matplotlib-cpp

After you downloaded Python compiler with matplotlibcpp.h and LOCATED FILE to your PROJECT FOLDER, include file to your project. To compile code you need a specific command, use this one:

g++ YourProjectName.cpp -o Simulation -I "Python folder\include" -I include -I "Your Disk that Contains unmpy\AppData\Roaming\Python\Python312\site-packages\numpy\core\include" -L "Python folder\libs" -lpython312 (or your version)

Remember: use your version of Python. In my case I just downloaded Pyhton to C disk and found numpy in my Roaming folder.

Good Luck, Stranger!
