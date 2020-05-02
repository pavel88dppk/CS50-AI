#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float grayscale;
    for (int i = 0; i < height; i++)
    {
        for (int n = 0; n < width; n++)
        {
            grayscale = round((image[i][n].rgbtRed + image[i][n].rgbtBlue + image[i][n].rgbtGreen) / 3.000);
            image[i][n].rgbtRed = grayscale;
            image[i][n].rgbtBlue = grayscale;
            image[i][n].rgbtGreen = grayscale;
        }
    }
    return;
}
//Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int n = 0; n < width; n++)
        {
            float sepiared = round((image[i][n].rgbtGreen * 0.769) + (image[i][n].rgbtBlue * 0.189) + (image[i][n].rgbtRed * 0.393));
            float sepiagreen = round(image[i][n].rgbtGreen * 0.686 + image[i][n].rgbtBlue * 0.168 + image[i][n].rgbtRed * 0.349);
            float sepiablue = round(image[i][n].rgbtGreen * 0.534 + image[i][n].rgbtBlue * 0.131 + image[i][n].rgbtRed * 0.272);
            if (sepiared <= 255)
            {
                image[i][n].rgbtRed = sepiared;
            }
            else
            {
                sepiared = 255;
                image[i][n].rgbtRed = sepiared;
            }
            if (sepiagreen <= 255)
            {
                image[i][n].rgbtGreen = sepiagreen;
            }
            else
            {
                sepiagreen = 255;
                image[i][n].rgbtGreen = sepiagreen;
            }
            if (sepiablue <= 255)
            {
                image[i][n].rgbtBlue = sepiablue;
            }
            else
            {
                sepiablue = 255;
                image[i][n].rgbtBlue = sepiablue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int n = 0; n < width / 2; n++)
        {
            int temp[3];
            temp[0] = image[i][n].rgbtRed;
            temp[1] = image[i][n].rgbtGreen;
            temp[2] = image[i][n].rgbtBlue;

            image[i][n].rgbtRed = image[i][width - n - 1].rgbtRed;
            image[i][n].rgbtGreen = image[i][width - n - 1].rgbtGreen;
            image[i][n].rgbtBlue = image[i][width - n - 1].rgbtBlue;
            image[i][width - n - 1].rgbtRed = temp[0];
            image[i][width - n - 1].rgbtGreen = temp[1];
            image[i][width - n - 1].rgbtBlue = temp[2];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE nimage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            nimage[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int n = 0; n < width; n++)
        {
            float sumred, sumgreen, sumblue = 0;

            if (i == 0 && n == 0)
            {
                sumred = round(((nimage[i][n].rgbtRed + nimage[i + 1][n].rgbtRed + nimage[i][n + 1].rgbtRed + nimage[i + 1][n + 1].rgbtRed) /
                                4.000));
                sumgreen = round(((nimage[i][n].rgbtGreen + nimage[i + 1][n].rgbtGreen + nimage[i][n + 1].rgbtGreen + nimage[i + 1][n +
                                   1].rgbtGreen) / 4.000));
                sumblue = round(((nimage[i][n].rgbtBlue + nimage[i + 1][n].rgbtBlue + nimage[i][n + 1].rgbtBlue + nimage[i + 1][n + 1].rgbtBlue) /
                                 4.000));
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;
            }
            else if (i == (height - 1) && n == (width - 1))
            {
                sumred = round(((nimage[i][n].rgbtRed + nimage[i - 1][n].rgbtRed + nimage[i][n - 1].rgbtRed + nimage[i - 1][n - 1].rgbtRed) /
                                4.000));
                sumgreen = round(((nimage[i][n].rgbtGreen + nimage[i - 1][n].rgbtGreen + nimage[i][n - 1].rgbtGreen + nimage[i - 1][n -
                                   1].rgbtGreen) / 4.000));
                sumblue = round(((nimage[i][n].rgbtBlue + nimage[i - 1][n].rgbtBlue + nimage[i][n - 1].rgbtBlue + nimage[i - 1][n - 1].rgbtBlue) /
                                 4.000));
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;
            }
            else if (i == 0 && n == (width - 1))
            {
                sumred = round(((nimage[i][n].rgbtRed + nimage[i + 1][n].rgbtRed + nimage[i][n - 1].rgbtRed + nimage[i + 1][n - 1].rgbtRed) /
                                4.000));
                sumgreen = round(((nimage[i][n].rgbtGreen + nimage[i + 1][n].rgbtGreen + nimage[i][n - 1].rgbtGreen + nimage[i + 1][n -
                                   1].rgbtGreen) / 4.000));
                sumblue = round(((nimage[i][n].rgbtBlue + nimage[i + 1][n].rgbtBlue + nimage[i][n - 1].rgbtBlue + nimage[i + 1][n - 1].rgbtBlue) /
                                 4.000));
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;
            }
            else if (i == (height - 1) && n == 0)
            {
                sumred = round(((nimage[i][n].rgbtRed + nimage[i - 1][n].rgbtRed + nimage[i][n + 1].rgbtRed + nimage[i - 1][n + 1].rgbtRed) /
                                4.000));
                sumgreen = round(((nimage[i][n].rgbtGreen + nimage[i - 1][n].rgbtGreen + nimage[i][n + 1].rgbtGreen + nimage[i - 1][n +
                                   1].rgbtGreen) / 4.000));
                sumblue = round(((nimage[i][n].rgbtBlue + nimage[i - 1][n].rgbtBlue + nimage[i][n + 1].rgbtBlue + nimage[i - 1][n + 1].rgbtBlue) /
                                 4.000));
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;
            }
            else if (i == 0)
            {
                float x = nimage[i][n].rgbtRed;
                float y = nimage[i + 1][n].rgbtRed;
                float z = nimage[i][n + 1].rgbtRed;
                float xx = nimage[i + 1][n + 1].rgbtRed;
                float yy = nimage[i + 1][n - 1].rgbtRed;
                float zz = nimage[i][n - 1].rgbtRed;
                sumred = round((x + y + z + yy + xx + zz) / 6.0);
                float p = nimage[i][n].rgbtGreen;
                float q = nimage[i + 1][n].rgbtGreen;
                float r = nimage[i][n + 1].rgbtGreen;
                float pp = nimage[i + 1][n + 1].rgbtGreen;
                float qq = nimage[i + 1][n - 1].rgbtGreen;
                float rr = nimage[i][n - 1].rgbtGreen;
                sumgreen = round((p + q + r + pp + qq + rr) / 6.0);
                float s = nimage[i][n].rgbtBlue;
                float t = nimage[i + 1][n].rgbtBlue;
                float u = nimage[i][n + 1].rgbtBlue;
                float ss = nimage[i + 1][n + 1].rgbtBlue;
                float tt = nimage[i + 1][n - 1].rgbtBlue;
                float uu = nimage[i][n - 1].rgbtBlue;
                sumblue = round((s + t + u + ss + tt + uu) / 6.0);
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;

            }
            else if (i != 0 && i != (height - 1) && n == 0)
            {
                sumred = round(((nimage[i][n].rgbtRed + nimage[i - 1][n].rgbtRed + nimage[i][n + 1].rgbtRed + nimage[i - 1][n + 1].rgbtRed +
                                 nimage[i + 1][n + 1].rgbtRed + nimage[i + 1][n].rgbtRed) / 6.000));
                sumgreen = round(((nimage[i][n].rgbtGreen + nimage[i - 1][n].rgbtGreen + nimage[i][n + 1].rgbtGreen + nimage[i - 1][n + 1].rgbtGreen
                                   + nimage[i + 1][n + 1].rgbtGreen + nimage[i + 1][n].rgbtGreen) / 6.000));
                sumblue = round(((nimage[i][n].rgbtBlue + nimage[i - 1][n].rgbtBlue + nimage[i][n + 1].rgbtBlue + nimage[i - 1][n + 1].rgbtBlue +
                                  nimage[i + 1][n + 1].rgbtBlue + nimage[i + 1][n].rgbtBlue) / 6.000));
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;
            }
            else if (i == (height - 1))
            {
                sumred = round(((nimage[i][n].rgbtRed + nimage[i - 1][n].rgbtRed + nimage[i][n + 1].rgbtRed + nimage[i - 1][n + 1].rgbtRed +
                                 nimage[i][n - 1].rgbtRed + nimage[i - 1][n - 1].rgbtRed) / 6.000));
                sumgreen = round(((nimage[i][n].rgbtGreen + nimage[i - 1][n].rgbtGreen + nimage[i][n + 1].rgbtGreen + nimage[i - 1][n + 1].rgbtGreen
                                   + nimage[i][n - 1].rgbtGreen + nimage[i - 1][n - 1].rgbtGreen) / 6.000));
                sumblue = round(((nimage[i][n].rgbtBlue + nimage[i - 1][n].rgbtBlue + nimage[i][n + 1].rgbtBlue + nimage[i - 1][n + 1].rgbtBlue +
                                  nimage[i][n - 1].rgbtBlue + nimage[i - 1][n - 1].rgbtBlue) / 6.000));
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;
            }
            else if (i != 0 && i != (height - 1) && n == (width - 1))
            {
                sumred = round(((nimage[i][n].rgbtRed + nimage[i - 1][n].rgbtRed + nimage[i][n - 1].rgbtRed + nimage[i - 1][n - 1].rgbtRed +
                                 nimage[i + 1][n - 1].rgbtRed + nimage[i + 1][n].rgbtRed) / 6.000));
                sumgreen = round(((nimage[i][n].rgbtGreen + nimage[i - 1][n].rgbtGreen + nimage[i][n - 1].rgbtGreen + nimage[i - 1][n - 1].rgbtGreen
                                   + nimage[i + 1][n - 1].rgbtGreen + nimage[i + 1][n].rgbtGreen) / 6.000));
                sumblue = round(((nimage[i][n].rgbtBlue + nimage[i - 1][n].rgbtBlue + nimage[i][n - 1].rgbtBlue + nimage[i - 1][n - 1].rgbtBlue +
                                  nimage[i + 1][n - 1].rgbtBlue + nimage[i + 1][n].rgbtBlue) / 6.000));
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;
            }
            else
            {
                sumred = round(((nimage[i][n].rgbtRed + nimage[i - 1][n].rgbtRed + nimage[i][n - 1].rgbtRed + nimage[i - 1][n - 1].rgbtRed +
                                 nimage[i + 1][n - 1].rgbtRed + nimage[i + 1][n].rgbtRed + nimage[i + 1][n + 1].rgbtRed + nimage[i - 1][n + 1].rgbtRed + nimage[i][n
                                         + 1].rgbtRed) / 9.000));
                sumgreen = round(((nimage[i][n].rgbtGreen + nimage[i - 1][n].rgbtGreen + nimage[i][n - 1].rgbtGreen + nimage[i - 1][n - 1].rgbtGreen
                                   + nimage[i + 1][n - 1].rgbtGreen + nimage[i + 1][n].rgbtGreen + nimage[i + 1][n + 1].rgbtGreen + nimage[i - 1][n + 1].rgbtGreen +
                                   nimage[i][n + 1].rgbtGreen) / 9.000));
                sumblue = round(((nimage[i][n].rgbtBlue + nimage[i - 1][n].rgbtBlue + nimage[i][n - 1].rgbtBlue + nimage[i - 1][n - 1].rgbtBlue +
                                  nimage[i + 1][n - 1].rgbtBlue + nimage[i + 1][n].rgbtBlue + nimage[i + 1][n + 1].rgbtBlue + nimage[i - 1][n + 1].rgbtBlue +
                                  nimage[i][n + 1].rgbtBlue) / 9.000));
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;
            }
        }
    }
    return;
}

