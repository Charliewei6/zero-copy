#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int main (int argc, char** argv)
{

  if (argc != 3) {
    printf("The number of arguments is not correct\n");
    exit(1);
  }

  
  int buff_size = 5*1024;
  char buffer[buff_size];

  const char *read_path= argv[1];
  FILE *read_file = fopen(read_path, "rb");

  const char *write_path = argv[2];
  FILE *write_file = fopen(write_path, "wb");
  
  size_t length;
  while(!feof(read_file)) {
    length = fread(buffer, 1, buff_size, read_file);
    fwrite(buffer, 1, length, write_file);
  }

  fclose(read_file);
  fclose(write_file);
  return 0;
}
