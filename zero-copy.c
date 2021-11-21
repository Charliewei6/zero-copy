#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <string.h>

int main (int argc, char** argv)
{

  if (argc != 4) {
    printf("usage: %s <source> <destination> <mode>\n", argv[0]);
    exit(1);
  }
 
  const char *src_path=argv[1];
  const char *dst_path=argv[2];
  int src;
  int dst;
  struct stat stat_buf;
  off_t offset = 0;
  int rc;


  src = open(src_path, O_RDONLY);
  fstat(src, &stat_buf);

  dst = open(dst_path, O_WRONLY|O_CREAT, stat_buf.st_mode);

  rc = sendfile (dst, src, &offset, stat_buf.st_size);

  if (rc != stat_buf.st_size) {
    fprintf(stderr, "incomplete transfer from sendfile: %d of %d bytes\n",
            rc,
            (int)stat_buf.st_size);
    exit(1);
  }

  close(dst);
  close(src);

  return 0;
}
