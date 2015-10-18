/*
  C verion of the character learning using a neural network described in 
  http://enakai00.hatenablog.com/entry/20150108/1420719651
 */

#include <stdio.h>

#define SIZE 5

int synapse[SIZE*SIZE][SIZE*SIZE];

char d_test[SIZE][SIZE] = {
  "#### ",
  " #  #",
  " #  #",
  " #  #",
  "#### "
};

char m_test[SIZE][SIZE] = {
  "#   #",
  "## ##",
  "# # #",
  "#   #",
  "## ##"
};


char d[SIZE][SIZE] = {
  "#### ",
  " #  #",
  " #  #",
  " #  #",
  " ### "
};

char j[SIZE][SIZE] = {
  "#####",
  "   # ",
  "   # ",
  "#  # ",
  "###  "
};

char c[SIZE][SIZE] = {
  " ####",
  "#    ",
  "#    ",
  "#    ",
  " ####"
};

char m[SIZE][SIZE] = {
  "#   #",
  "## ##",
  "# # #",
  "#   #",
  "#   #"
};
  
void learn(char input[][SIZE]){
  int i, j;

  for(i=0;i<SIZE*SIZE;i++){
    for(j=0;j<SIZE*SIZE;j++){
      int ix=i/SIZE, iy=i%SIZE, jx=j/SIZE, jy=j%SIZE;

      if(ix == jx && iy == jy)
	continue;
      
      if(input[ix][iy] == input[jx][jy])
	synapse[i][j]++;
      else
	synapse[i][j]--;
    }		      
  }
}

void create_neurons(char input[][SIZE]){
  int i;

  for(i=0;i<SIZE*SIZE;i++){
    int ix=i/SIZE, iy=i%SIZE;

    if(input[ix][iy] == '#')
      input[ix][iy] = 1;
    else
      input[ix][iy] = -1;
  }
}

void run_hopfield(char input[][SIZE]){
  int i, j;

  for(i=0;i<SIZE*SIZE;i++){
    int ix=i/SIZE, iy=i%SIZE;
    int sum = 0;
    
    for(j=0;j<SIZE*SIZE;j++){
      int jx=j/SIZE, jy=j%SIZE;
      sum += input[jx][jy] * synapse[i][j];
    }

    if(sum >= 0)
      input[ix][iy] = 1;
    else
      input[ix][iy] = -1;
  }
}

void show(char input[][SIZE]){
  int i;

  for(i=0;i<SIZE*SIZE;i++){
    int ix=i/SIZE,iy=i%SIZE;

    if(input[ix][iy] == 1)
      printf("#");
    else
      printf(" ");
    
    if(iy == SIZE-1)
      printf("\n");
  }
}

main(){
  create_neurons(d_test);
  create_neurons(m_test);

  create_neurons(d);
  create_neurons(j);
  create_neurons(c);
  create_neurons(m);

  show(m_test);
  printf("---------------------\n");

  
  learn(d);
  learn(j);
  learn(c);
  learn(m);

  run_hopfield(m_test);
  show(m_test);
  printf("---------------------\n");

  run_hopfield(m_test);
  show(m_test);
  printf("---------------------\n");
}
