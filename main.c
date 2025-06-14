#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define BACKGROUND '.'

int rows = 0;
int cols = 0;

typedef struct {
   int  rows;
   int  cols;
   char *grid;
} Canvas;

// sets ROWS and COLS based on current terminal size
void set_canvas_size() {
   struct winsize w;
   ioctl (STDOUT_FILENO, TIOCGWINSZ, &w);
   rows = w.ws_row;
   cols = w.ws_col;
}

Canvas blank_canvas() {
   set_canvas_size();
   Canvas canvas;
   canvas.rows = rows;
   canvas.cols = cols;
   canvas.grid = malloc (rows * cols * sizeof (char));
   memset (canvas.grid, BACKGROUND, rows * cols);
   return canvas;
}

void destroy (Canvas canvas) {
   free (canvas.grid);
}

void clear (Canvas *canvas) {
   memset (canvas->grid, BACKGROUND, canvas->rows * canvas->cols);
}

void display (Canvas canvas) {
   for (int i = 0; i < canvas.rows * canvas.cols; i++) {
      putc (canvas.grid [i], stdout);
      if ((i + 1) % canvas.cols == 0) {
         putc ('\n', stdout);
      }
   }
}

void draw (Canvas *canvas, int i, int j, char c) {
   if (0 <= i && i < canvas->rows && 0 <= j && j < canvas->cols) {
      canvas->grid [i * canvas->cols + j] = c;
   }
}

void clear_terminal() {
   printf ("\033[H\033[J");
   // /033[H\033[J is the ANSI escape code for clearing
   // the screen and moving cursor to the top left corner
}



int main() {
   
   clear_terminal();
   Canvas canvas = blank_canvas();

   int t = 0;
   
   int j = 0;   

   while (t >= 0) {
      clear (&canvas);
      draw (&canvas, canvas.rows/2, canvas.cols * (1 - cos(0.02 * j))/2, '*');
      clear_terminal();
      display (canvas);
      j++;
      usleep (15000);
   }

   destroy (canvas);

}
