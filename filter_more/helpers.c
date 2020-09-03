#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp;
            temp = image[i][width - j - 1];
            image[i][width - j - 1] = image[i][j];
            image[i][j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    int count;
    float x, y, z;
    RGBTRIPLE image1[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image1[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            count = 0;
            x = 0;
            y = 0;
            z = 0;
            for (int l = -1; l < 2; l++)
            {
                for (int m = -1; m < 2; m++)
                {
                    if (i + l >= 0 && j + m >= 0 && i + l < height && j + m < width)
                    {
                        x += image1[l + i][m + j].rgbtRed;
                        y += image1[l + i][m + j].rgbtGreen;
                        z += image1[l + i][m + j].rgbtBlue;
                        count++;
                    }
                }
            }
            x = round(x / count);
            y = round(y / count);
            z = round(z / count);
            if (x > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = x;
            }
            if (y > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = y;
            }
            if (z > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = z;
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    float sumxRed, sumyRed;
    float sumxGreen, sumyGreen;
    float sumxBlue, sumyBlue;
    RGBTRIPLE image1[height][width];
    //creating kernel array
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    //creating copy of given image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image1[i][j] = image[i][j];
        }
    }
    //calculating value of edge filter using kernel array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumxRed = 0;
            sumyRed = 0;
            sumxGreen = 0;
            sumyGreen = 0;
            sumxBlue = 0;
            sumyBlue = 0;
            for (int l = -1; l < 2; l++)
            {
                for (int m = -1; m < 2; m++)
                {
                    //multiply with 0 for edge and corner cases
                    if ((i + l) < 0 || (j + m) < 0 || (i + l) >= height || (m + j) >= width)
                    {
                        sumxRed += 0;
                        sumyRed += 0;
                        sumxGreen += 0;
                        sumyGreen += 0;
                        sumxBlue += 0;
                        sumyBlue += 0;
                    }
                    //for other pixels multiply with kernel array
                    else
                    {
                        sumxRed += image1[i + l][j + m].rgbtRed * Gx[l + 1][m + 1];
                        sumyRed += image1[i + l][j + m].rgbtRed * Gy[l + 1][m + 1];
                        sumxGreen += image1[i + l][j + m].rgbtGreen * Gx[l + 1][m + 1];
                        sumyGreen += image1[i + l][j + m].rgbtGreen * Gy[l + 1][m + 1];
                        sumxBlue += image1[i + l][j + m].rgbtBlue * Gx[l + 1][m + 1];
                        sumyBlue += image1[i + l][j + m].rgbtBlue * Gy[l + 1][m + 1];
                    }

                }
            }
            //finding square root of kernel sums for each pixel
            float kernelRed = round(sqrt((sumxRed * sumxRed) + (sumyRed * sumyRed)));
            float kernelGreen = round(sqrt((sumxGreen * sumxGreen) + (sumyGreen * sumyGreen)));
            float kernelBlue = round(sqrt((sumxBlue * sumxBlue) + (sumyBlue * sumyBlue)));
            //if out of bounds cap at 255
            if (kernelRed > 255)
            {
                kernelRed = 255;
            }
            if (kernelGreen > 255)
            {
                kernelGreen = 255;
            }
            if (kernelBlue > 255)
            {
                kernelBlue = 255;
            }
            image[i][j].rgbtRed = kernelRed;
            image[i][j].rgbtGreen = kernelGreen;
            image[i][j].rgbtBlue = kernelBlue;
        }
    }
    return;
}
