#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

int ROWS = 0;
int COLS = 0;

void clear_terminal() {
   printf ("\033[H\033[J");
}

void set_terminal_size() {
   struct winsize w;
   ioctl (STDOUT_FILENO, TIOCGWINSZ, &w);
   ROWS = w.ws_row;
   COLS = w.ws_col;
}

void fill_canvas (char c) {
   for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
         putchar (c);
      }
   }
   putchar ('\n');
}

int main () {

   while (1) {
      clear_terminal();
      set_terminal_size();
      fill_canvas ('.');
      usleep (100000);
      clear_terminal();
      set_terminal_size();
      fill_canvas ('@');
      usleep (100000);
   }
}
