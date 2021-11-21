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
  
 const char *src_path = argv[1];
 const char *dst_path = argv[2];
  FILE *src, *dst;
  int buffer_size = 8 * 1024;
  char buffer[buffer_size];
  size_t length;

  
  src = fopen(src_path, "rb");
  dst = fopen(dst_path, "wb");
  
  while(!feof(src)) {
    length = fread(buffer, 1, buffer_size, src);
    fwrite(buffer, 1, length, dst);
  }

  fclose(src);
  fclose(dst);
  return 0;
}
