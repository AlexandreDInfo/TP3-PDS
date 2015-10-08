#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int nombre_de_ligne(int d){
  int n;
  char c;
  n = 0;

  while(read(d, &c, 1) != 0){
    if (c == '\n'){
      n++;
    }
  }
  return n;
}


int print_line(int n, int max, int d){


  int pass;
  char c;
  pass = max - n;

  while (pass > 0){

    read(d, &c, 1);

    if (c == '\n'){

      pass--;
    }
  }

  while( n > 0){

    read(d,&c,1);

    if (c == '\n'){

      n--;
    }

    printf("%c", c);
  }

  return 0;
}

int main(int argc, char *argv[])
{
  int nb_ligne;
  int c;
  int index;
  int arg;
  int d2;
  int d;
  d = open(argv[1], O_RDONLY);
  d2 = open(argv[1], O_RDONLY);
  nb_ligne = nombre_de_ligne(d);

  if(nb_ligne < 10){
    index = nb_ligne;
  }
  else{
    index = 10;
  }
  

  while((c = getopt(argc, argv, "n:")) != -1){

    switch(c){

      case 'n':

        arg = atoi(optarg);

        if (nb_ligne - arg > 0){
          index = arg;
        }

        break;
    }
  }
  
  print_line(index, nb_ligne, d2);
  
  return 0;
}