/* get standard i/o library */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#ifdef BOOL_DEFINED
typedef bool boolean;
#else
#define false 0
#define true  (!false)
typedef unsigned char  boolean;
#endif

#define PI3        1.0471975511965977462

int counter = 0;
boolean first = true;
double start_x, start_y;


void drawCurve(FILE *output,   
               double x1, double y1,     /* Startpunkt fuer die Teilstrecken */
               double angle1,            /* Winkel zwischen den Teilstrecken */
               double sideLength,        /* Laenge einer Teilstrecke         */
               int level)                /* Schachtelungstiefe               */
{
   /*                                                                        */
   /* Jede Teilstrecke wird eindeutig durch einen Startpunkt, einen Winkel   */
   /* und eine Laenge definiert. Anzahl der Teilstrecken = 3*4^(level-1),    */
   /* level 1 = gleichseitiges Dreieck.                                      */
   /*                                                                        */
   double x2, y2, angle2, x3, y3, angle3, x4, y4;
   
   if (level > 1) {
      /* Teilstrecke in vier neue Teilstrecken zerlegen                      */
      sideLength /= 3.0;
      level -= 1;
      
      /* erste Teilstrecke                                                   */
      drawCurve(output, x1,y1, angle1, sideLength, level);
      
      /* zweite Teilstrecke                                                  */
      x2 = x1 + sideLength * cos(angle1);
      y2 = y1 + sideLength * sin(angle1);
      angle2 = angle1 - PI3;
      drawCurve(output, x2, y2, angle2, sideLength, level);
      
      /* dritte Teilstrecke                                                  */
      x3 = x2 + sideLength * cos(angle2);
      y3 = y2 + sideLength * sin(angle2);
      angle3 = angle1 + PI3;
      drawCurve(output, x3, y3, angle3, sideLength, level);
      
      /* vierte Teilstrecke                                                  */
      x4 = x3 + sideLength * cos(angle3);
      y4 = y3 + sideLength * sin(angle3);
      /* angle4 = angle1                                                     */
      drawCurve(output, x4, y4, angle1, sideLength, level);
   }
   else {
      /* Teilstrecke ausgeben                                               */
      fprintf(output, "%f %f\n", x1, y1);
      if (first) {
         start_x = x1;
         start_y = y1;
         first   = false;
      }
   }
    
   return;
}


void PrintHeader(void)
{
   printf("\n");
   printf("***********************************************************\n");
   printf("*                                                         *\n");
   printf("*                 make_koch_snowflake                     *\n");
   printf("*                                                         *\n");
   printf("* Generation of a (nested) Koch snowflake.                *\n");
   printf("*                                                         *\n");
   printf("*      Martin Held 2015-2020        held@cs.sbg.ac.at     *\n");
   printf("*                                                         *\n");
   printf("***********************************************************\n");

   return;
}


void OpenFile(FILE  **output, const char *file_name)
{
   /* open file */
   if((*output = fopen(file_name, "w")) == NULL) {
      fprintf(stderr,"*** Output file not created! ***\n");
      exit(1);
   }
   
   return;
}   


int main(int argc, char **argv)
{
   int count = 1;
   boolean success = true;
   boolean name_read = false, nested = false;
   double x1, y1, angle;
   int level = 0;
   FILE *output;
   char *file_name = "koch.line";
   int i, number;

   PrintHeader();

   /*                                                                        */
   /* parse command-line arguments                                           */
   /*                                                                        */
   while ((count < argc)  &&  success)    {

      if (strcmp(argv[count],"--number") == 0) {
         ++count;
         if ((success = (count < argc)))  level = atoi(argv[count]);
      }
      else if (strcmp(argv[count],"--nested") == 0) {
         nested = true;
      }
      else if (strcmp(argv[count],"--output") == 0) {
         ++count;
         if ((success = (count < argc))) {
            file_name = argv[count];
            name_read = true;
         }
      }
      else {
         success = false;
      }
      ++count;
   }

   if (!success  ||  !name_read  ||  (level <= 0)) {
      if (!success) 
         printf("\nUnrecognized command-line option: %s\n", argv[count-1]); 
      printf("\nUsage: make_koch_snowflake --number N --output XYZ [--nested]\n       where N is a positive integer.\n"); 
      exit(2);
   }

   /*                                                                        */
   /* initialization                                                         */
   /*                                                                        */
   OpenFile(&output, file_name);
   x1    =  10.0;
   y1    = 310.0;
   angle = - PI3;

   number = 1;
   for (i = 1; i < level; i++) {
      number *= 4;
   }
   fprintf(output, "%d\n", 3 * number + 1);
   printf("... generating %d vertices: ", 3 * number);
   fflush(stdout);

   /*                                                                        */
   /* recursive generation of Koch curve                                     */
   /*                                                                        */
   for (i = 0; i < 3; i++) {
      drawCurve(output, x1, y1, angle, 350, level);
      x1 += 350.0 * cos(angle);
      y1 += 350.0 * sin(angle);
      angle += 2.0 * PI3;
   }
   fprintf(output, "%f %f\n", start_x, start_y);
 
   printf("done\n");

   if (nested) {
      fprintf(output, "%d\n", 3 * number + 1);
      printf("... generating inner %d vertices: ", 3 * number);
      fflush(stdout);
      x1    =  97.5;
      y1    = 259.481852;
      angle = - PI3;
      first = true;
      
      /*                                                                     */
      /* recursive generation of Koch curve                                  */
      /*                                                                     */
      for (i = 0; i < 3; i++) {
         drawCurve(output, x1, y1, angle, 175, level);
         x1 += 175.0 * cos(angle);
         y1 += 175.0 * sin(angle);
         angle += 2.0 * PI3;
      }
      fprintf(output, "%f %f\n", start_x, start_y);
      
      printf("done\n");
   }

   fclose(output);

   return 0;
}
