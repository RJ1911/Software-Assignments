#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    FILE *ptr1, *ptr2;
    ptr1 = fopen("256x256_cover1.txt", "r"); // cover data file pointer
    ptr2 = fopen("Secret_info8.txt", "r");   // secret_info file pointer

    int cover_data[256][256], secret_info[256][512];
     int embedded_data1[256][256]; // 2 LSB without OPAP
     int embedded_data2[256][256]; // 2 LSB with OPAP

    // Scanning cover data text file && storing it in cover_data[256][256]
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            fscanf(ptr1, "%d", &cover_data[i][j]);
        }
    }
    // Scanning secret info text file && storing it in secret_info[256][512]
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 512; j++)
        {
            fscanf(ptr2, "%d", &secret_info[i][j]);
        }
    }
    fclose(ptr1);
    fclose(ptr2);

    // 2 LSB substitution
    for (int i = 0; i < 256; i++)
    {
        int k = 0;
        for (int j = 0; j < 256; j++)
        {
            // taking two consecutive no. from secret info & embeding it into cover data
            embedded_data1[i][j] = ((cover_data[i][j] / 4) * 4) + 2 * secret_info[i][k] + 1 * secret_info[i][k + 1];
            k = k + 2;
        }
    }

    double square_sum = 0 , temp1;
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
           temp1 = abs(cover_data[i][j] - embedded_data1[i][j]) * abs(cover_data[i][j] - embedded_data1[i][j]);
            square_sum = square_sum + temp1;
        }
    }
    // MSE & PSNR without OPAP
    double MSE1, PSNR1;
    MSE1 = square_sum / (256 * 256);
    printf("Without OPAP:\n");
    printf("MSE = %f\n", MSE1);
    PSNR1 = 10 * log10((255 * 255) / MSE1);
    printf("PSNR = %f ", PSNR1);
    

    // Optical Pixel Adjustment Process (OPAP)
   
double square_sum2 = 0;
   for (int i = 0; i < 256; i++)
   {
      for (int j = 0; j < 256; j++)
      {
         double temp;
         int d = embedded_data1[i][j] - cover_data[i][j];
         if (d > 2 && d < 4 && embedded_data1[i][j] >= 4)
         {
               embedded_data2[i][j] = embedded_data1[i][j] - 4;
         }
         else if (d >= -4 && d <= -2 && embedded_data1[i][j] < (256-4))
         {
               embedded_data2[i][j] = embedded_data1[i][j] + 4;
         }
         else
         {
            embedded_data2[i][j] = embedded_data1[i][j];
         }
         square_sum2 = square_sum2 + abs(cover_data[i][j]-embedded_data2[i][j]) * abs(cover_data[i][j]-embedded_data2[i][j]);
      }
   }
   // MSE & PSNR with OPAP
   double MSE2,PSNR2,max;
   MSE2 = square_sum2 / (256 * 256);
   max = 255;
   PSNR2 = 10 * log10((max * max) / MSE2);
    printf("\nWith OPAP:\n");
   printf("MSE is = %f\n", MSE2);
   printf("PSNR is = %f\n", PSNR2);


   //Creating PGM file
    int i, j, temp = 0;
   int width = 256, height = 256;
   FILE *pgmimg2;
   pgmimg2 = fopen("pgmimg_2.pgm", "wb");

   // Writing Magic Number to the File
   fprintf(pgmimg2, "P2\n");

   // Writing Width and Height
   fprintf(pgmimg2, "%d %d\n", width, height);

   // Writing the maximum gray value
   fprintf(pgmimg2, "255\n");
   int count = 0;
   for (i = 0; i < height; i++)
   {
      for (j = 0; j < width; j++)
      {
         // Writing the gray values in the 2D array to the file
         fprintf(pgmimg2, "%d ", embedded_data2[i][j]);
      }
      fprintf(pgmimg2, "\n");
   }
   fclose(pgmimg2);
    return 0;
}