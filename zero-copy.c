#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main (int argc, char** argv)
{

  if (argc != 3) {
    printf("The number of arguments is not correct\n");
    exit(1);
  }
 
  struct stat stat_buf;

  const char *read_path=argv[1];
  int read_file = open(read_path, O_RDONLY);
  fstat(read_file, &stat_buf);
  
  const char *write_path=argv[2];
  int write_file = open(write_path, O_WRONLY|O_CREAT, stat_buf.st_mode);

  off_t offset = 0;
  int zp = sendfile (write_file, read_file, &offset, stat_buf.st_size);
  
  if (zp == -1) {
	      fprintf(stderr, "error transfer from sendfile: %s", strerror(errno));
	      exit(1);
  }
  if (zp != stat_buf.st_size) {
    fprintf(stderr, "incomplete transfer from sendfile: %d of %d bytes\n",zp,(int)stat_buf.st_size);
    exit(1);
  }
  
  close(read_file);
  close(write_file);

  return 0;
}
