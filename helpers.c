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

    for (int i = 0; i < height; i++)
    {
        for (int n = 0; n < width; n++)
        {
            float sumred, sumgreen, sumblue;
            if (i == 0 && n == 0)
            {
                sumred = round(((image[i][n].rgbtRed + image[i + 1][n].rgbtRed + image[i][n + 1].rgbtRed + image[i + 1][n + 1].rgbtRed) / 4.000));
                sumgreen = round(((image[i][n].rgbtGreen + image[i + 1][n].rgbtGreen + image[i][n + 1].rgbtGreen + image[i + 1][n + 1].rgbtGreen) /
                                  4.000));
                sumblue = round(((image[i][n].rgbtBlue + image[i + 1][n].rgbtBlue + image[i][n + 1].rgbtBlue + image[i + 1][n + 1].rgbtBlue) /
                                 4.000));
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;
            }
            else if (i == (height - 1) && n == (width - 1))
            {
                sumred = round(((image[i][n].rgbtRed + image[i - 1][n].rgbtRed + image[i][n - 1].rgbtRed + image[i - 1][n - 1].rgbtRed) / 4.000));
                sumgreen = round(((image[i][n].rgbtGreen + image[i - 1][n].rgbtGreen + image[i][n - 1].rgbtGreen + image[i - 1][n - 1].rgbtGreen) /
                                  4.000));
                sumblue = round(((image[i][n].rgbtBlue + image[i - 1][n].rgbtBlue + image[i][n - 1].rgbtBlue + image[i - 1][n - 1].rgbtBlue) /
                                 4.000));
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;
            }
            else if (i == 0 && n == (width - 1))
            {
                sumred = round(((image[i][n].rgbtRed + image[i + 1][n].rgbtRed + image[i][n - 1].rgbtRed + image[i + 1][n - 1].rgbtRed) / 4.000));
                sumgreen = round(((image[i][n].rgbtGreen + image[i + 1][n].rgbtGreen + image[i][n - 1].rgbtGreen + image[i + 1][n - 1].rgbtGreen) /
                                  4.000));
                sumblue = round(((image[i][n].rgbtBlue + image[i + 1][n].rgbtBlue + image[i][n - 1].rgbtBlue + image[i + 1][n - 1].rgbtBlue) /
                                 4.000));
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;
            }
            else if (i == (height - 1) && n == 0)
            {
                sumred = round(((image[i][n].rgbtRed + image[i - 1][n].rgbtRed + image[i][n + 1].rgbtRed + image[i - 1][n + 1].rgbtRed) / 4.000));
                sumgreen = round(((image[i][n].rgbtGreen + image[i - 1][n].rgbtGreen + image[i][n + 1].rgbtGreen + image[i - 1][n + 1].rgbtGreen) /
                                  4.000));
                sumblue = round(((image[i][n].rgbtBlue + image[i - 1][n].rgbtBlue + image[i][n + 1].rgbtBlue + image[i - 1][n + 1].rgbtBlue) /
                                 4.000));
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;
            }
            else if (i == 0 && n != 0 && n != (width - 1))
            {
                sumred = round(((image[i][n].rgbtRed + image[i + 1][n].rgbtRed + image[i][n + 1].rgbtRed + image[i + 1][n + 1].rgbtRed + image[i +
                                 1][n - 1].rgbtRed + image[i][n - 1].rgbtRed) / 6.000));
                sumgreen = round(((image[i][n].rgbtGreen + image[i + 1][n].rgbtGreen + image[i][n + 1].rgbtGreen + image[i +
                                   1][n + 1].rgbtGreen + image[i + 1][n - 1].rgbtGreen + image[i][n - 1].rgbtGreen) / 6.000));
                sumblue = round(((image[i][n].rgbtBlue + image[i + 1][n].rgbtBlue + image[i][n + 1].rgbtBlue + image[i + 1][n + 1].rgbtBlue +
                                  image[i + 1][n - 1].rgbtBlue + image[i][n - 1].rgbtBlue) / 6.000));
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;
            }
            else if (i != 0 && i != (height - 1) && n == 0)
            {
                sumred = round(((image[i][n].rgbtRed + image[i - 1][n].rgbtRed + image[i][n + 1].rgbtRed + image[i - 1][n + 1].rgbtRed + image[i +
                                 1][n + 1].rgbtRed + image[i + 1][n].rgbtRed) / 6.000));
                sumgreen = round(((image[i][n].rgbtGreen + image[i - 1][n].rgbtGreen + image[i][n + 1].rgbtGreen + image[i - 1][n + 1].rgbtGreen +
                                   image[i + 1][n + 1].rgbtGreen + image[i + 1][n].rgbtGreen) / 6.000));
                sumblue = round(((image[i][n].rgbtBlue + image[i - 1][n].rgbtBlue + image[i][n + 1].rgbtBlue + image[i - 1][n + 1].rgbtBlue +
                                  image[i + 1][n + 1].rgbtBlue + image[i + 1][n].rgbtBlue) / 6.000));
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;
            }
            else if (i == (height - 1) && n != 0 && n != (width - 1))
            {
                sumred = round(((image[i][n].rgbtRed + image[i - 1][n].rgbtRed + image[i][n + 1].rgbtRed + image[i - 1][n + 1].rgbtRed + image[i][n
                                 - 1].rgbtRed + image[i - 1][n - 1].rgbtRed) / 6.000));
                sumgreen = round(((image[i][n].rgbtGreen + image[i + 1][n].rgbtGreen + image[i][n + 1].rgbtGreen + image[i + 1][n + 1].rgbtGreen +
                                   image[i][n - 1].rgbtGreen + image[i + 1][n - 1].rgbtGreen) / 6.000));
                sumblue = round(((image[i][n].rgbtBlue + image[i + 1][n].rgbtBlue + image[i][n + 1].rgbtBlue + image[i + 1][n + 1].rgbtBlue +
                                  image[i][n - 1].rgbtBlue + image[i + 1][n - 1].rgbtBlue) / 6.000));
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;
            }
            else if (i != 0 && i != (height - 1) && n == (width - 1))
            {
                sumred = round(((image[i][n].rgbtRed + image[i - 1][n].rgbtRed + image[i][n - 1].rgbtRed + image[i - 1][n - 1].rgbtRed + image[i +
                                 1][n - 1].rgbtRed + image[i + 1][n].rgbtRed) / 6.000));
                sumgreen = round(((image[i][n].rgbtGreen + image[i - 1][n].rgbtGreen + image[i][n - 1].rgbtGreen + image[i - 1][n - 1].rgbtGreen +
                                   image[i + 1][n - 1].rgbtGreen + image[i + 1][n].rgbtGreen) / 6.000));
                sumblue = round(((image[i][n].rgbtBlue + image[i - 1][n].rgbtBlue + image[i][n - 1].rgbtBlue + image[i - 1][n - 1].rgbtBlue +
                                  image[i + 1][n - 1].rgbtBlue + image[i + 1][n].rgbtBlue) / 6.000));
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;
            }
            else
            {
                sumred = round(((image[i][n].rgbtRed + image[i - 1][n].rgbtRed + image[i][n - 1].rgbtRed + image[i - 1][n - 1].rgbtRed + image[i +
                                 1][n - 1].rgbtRed + image[i + 1][n].rgbtRed + image[i + 1][n + 1].rgbtRed + image[i - 1][n + 1].rgbtRed + image[i][n + 1].rgbtRed) /
                                9.000));
                sumgreen = round(((image[i][n].rgbtGreen + image[i - 1][n].rgbtGreen + image[i][n - 1].rgbtGreen + image[i - 1][n - 1].rgbtGreen +
                                   image[i + 1][n - 1].rgbtGreen + image[i + 1][n].rgbtGreen + image[i + 1][n + 1].rgbtGreen + image[i - 1][n + 1].rgbtGreen +
                                   image[i][n + 1].rgbtGreen) / 9.000));
                sumblue = round(((image[i][n].rgbtBlue + image[i - 1][n].rgbtBlue + image[i][n - 1].rgbtBlue + image[i - 1][n - 1].rgbtBlue +
                                  image[i + 1][n - 1].rgbtBlue + image[i + 1][n].rgbtBlue + image[i + 1][n + 1].rgbtBlue + image[i - 1][n + 1].rgbtBlue + image[i][n +
                                          1].rgbtBlue) / 9.000));
                image[i][n].rgbtRed = sumred;
                image[i][n].rgbtGreen = sumgreen;
                image[i][n].rgbtBlue = sumblue;
            }
        }
    }
    return;
}
