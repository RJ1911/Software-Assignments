#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    FILE *ptr1, *ptr2;
    ptr1 = fopen("256x256_cover1.txt", "r"); // cover data file pointer
    ptr2 = fopen("Secret_info1.txt", "r");   // secret_info file pointer
    int cover_data[256][256], secret_info[256][256], embedded_data[256][256];

    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            fscanf(ptr1, "%d", &cover_data[i][j]);  // scanning file from cover data text file
            fscanf(ptr2, "%d", &secret_info[i][j]); // scanning file from secret info text file
        }
    }
    fclose(ptr1);
    fclose(ptr2);

    /*embedding secret info into cover data by 1 LSB substitution and storing it in  embedded_data[][] array*/
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            embedded_data[i][j]=(cover_data[i][j]/2)*2+secret_info[i][j];
        }
    }

    // calculating mean square error(MSE) and PSNR
    float square_sum = 0;
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            square_sum = square_sum + (cover_data[i][j] - embedded_data[i][j]) * (cover_data[i][j] - embedded_data[i][j]);
        }
    }

    double MSE, PSNR;
    MSE = square_sum / (256 * 256);
    printf("MSE = %f\n", MSE);
    PSNR = 10 * log10((255 * 255) / MSE);
    printf("PSNR = %f ", PSNR);

    // creating pgm file
    FILE *pgmimg;
    int w = 256, h = 256;
    pgmimg = fopen("pgmimg_1.pgm", "wb");//write the file in binary mode
    fprintf(pgmimg, "P2\n");//writing magic no. to file
    fprintf(pgmimg, "%d %d\n", w, h);// writing width and height to the file
    fprintf(pgmimg, "255\n");//writing the maixmum gray value
    int count = 0;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            fprintf(pgmimg, "%d ", embedded_data[i][j]);//copying gray value from array to pgm file
        }
        fprintf(pgmimg, "\n");
    }
    fclose(pgmimg);

    return 0;
}