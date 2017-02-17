#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define DEVICE "/dev/simple_char_drv"

int main()
{ int fd;
  int write_buf,read_buf;
  fd = open(DEVICE, O_RDWR);
  printf("The lower limit is 0. \n");
  printf("Please enter the upper limit \n");
  scanf("%d" , &write_buf);
  write(fd, &write_buf, sizeof(write_buf));
  read(fd, &read_buf, sizeof(read_buf));
  printf("random number: %d \n",read_buf);
  close(fd);
  return 0;
}


