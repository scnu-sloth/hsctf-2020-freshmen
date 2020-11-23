#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXSIZE 4096
#define MAXROUND 10

int rounds = 0;
int chances = 0;
int nums[MAXSIZE] = {0};

void win() {
  printf("Ooops, you're so lucky!\n");
  system("/bin/sh");
  exit(0);
}

void clear() {
  for (int i=0; i<MAXSIZE; i++) {
    nums[i] = 0;
  }
}

void showState() {
  printf("rounds: %d\n", rounds);
  printf("chances: %d\n", chances);
}

void guess() {
  if (!chances) {
    printf("GAME OVER!\n");
    exit(0);
  }
  clear();
  nums[(rand()%MAXSIZE)] = 1;
  chances -= 1;

  int inp = 0;
  scanf("%d", &inp);
  if (inp >= MAXSIZE) {
    printf("Input too large!\n");
    exit(-1);
  }

  if (nums[inp] == 1) {
    printf("Biiiingo!\nChance++\n");
    rounds += 1;
    chances += 1;

    if (rounds >= MAXROUND) {
      win();
    }
  } else {
    printf("Wrong!\n");
  }

}

void game() {
  while (chances) {
    showState();
    guess();
  }
}

void init() {
  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  setvbuf(stderr, 0LL, 2, 0LL);

  unsigned int seed = 0;
  int fd=open("/dev/urandom",O_RDONLY);
  read(fd, &seed, sizeof(seed));
  close(fd);
  srand(seed);
  chances = 10;
}

int main() {
  init();
  game();

  printf("GAME OVER!\n");

  return 0;
}
