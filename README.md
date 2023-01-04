# OSES_project
This is the project for the Operating Systems for Embedded Systems course at Politecnico di Torino in the academic year 2022/2023.


TODOs:

1) Find a way and test how to count time with a timer, DWT or SYSTICK. We should do this bare-metal before the OS starts up, with some bare-metal.
    Have access to the DWT register without the OS part
2) Measure the startup time and average with some kind of error margin that we consider correct boot time
3) Save this startup time on the board and at the next startup check if it is the same (within the margin)

4) Model the attack: change something in source (startup routine) and see if it can notice it or not.
