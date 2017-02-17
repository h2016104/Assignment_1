INTRODUCTION:
The given program writes a kernel module to implement a random number generation algorithm. There are two main files, one is in kernal space i.e. main.c and the other is in user space i.e. user.c.
user.c takes input from the user and pass it to kernel space using write() system call. In kernel space, random number is generated and paased it back to user space using read() system call. In kernel spcae the input from user is written to kernel space using copy_from_user() function.
The output from kernel space to user space is sent throgh copy_to_user() function.
The algorithm for random number generation takes the seed as second time of the system clock, which is then manipulated as follows:
i = (7*seed)%101
random_number = (i-1)%10 +1
The random number generated is between 0 - 9. To bring it in the required range, we do the following manipulation:
random_number = (random_number * user_input) / 9;




How to bulid:
//to build the kernel module first create a makefile and the use the folloeing command.
$ make
//to make the device entry in /dev file.
$ sudo mknod -m 777 /dev/simple_char_drv c 240 0
//NOTE: care should be taken to check that major number 240 is not already assigned toother device file. This can be done by using the command 
$ ls -l /dev
//In case 240 is an already assigned major number, change the major number to some other unassigned numeber in register_chrdev function in main.c.
//to compile user.c
$ gcc user.c -o user.out
//to insert the module in kernel space 
$ sudo insmod ./main.ko
//to open user.out
$ ./user.out
//to remove the module from kernel space
$ sudo rmmod main.ko
