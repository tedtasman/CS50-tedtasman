#include "helpers.h"
#include <math.h>

#define RED 0
#define GREEN 1
#define BLUE 2
#define VERTICAL 0
#define HORIZONTAL 1

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through vertically
    for (int i = 0; i < height; i++)
    {
        // iterate through horizontally
        for (int j = 0; j < width; j++)
        {
            // get rgb values
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;
            // average rgb values
            int grey = round((red + green + blue) / 3);
            // set rgb for pixel i, j to average
            image[i][j].rgbtRed = grey;
            image[i][j].rgbtGreen = grey;
            image[i][j].rgbtBlue = grey;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through image vertically
    for (int i = 0; i < height; i++)
    {
        // iterate through image horizontally stopping half way
        for (int j = 0; j < (width / 2); j++)
        {
            // calculate opposite pixel of j
            int k = width - j - 1;
            // get and store pixel on left
            RGBTRIPLE temp = image[i][j];
            // get and reflect pixel on right
            image[i][j] = image[i][k];
            // move stored pixel to right
            image[i][k] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //RGBRTRIPLE for temp image
    RGBTRIPLE temp[height][width];
    // iterate through vertically
    for (int i = 0; i < height; i++)
    {
        // iterate through horizontally
        for (int j = 0; j < width; j++)
        {
            int redsum = 0;
            int greensum = 0;
            int bluesum = 0;
            float boxsum = 0;
            // iterate across pixel vertically
            for (int y = -1; y <= 1; y++)
            {
                // iterate across pixel horizontally
                for (int x = -1; x <= 1; x++)
                {
                    // new coordinates with adjustment (f is vertical, g is horizontal)
                    int f = i + y;
                    int g = j + x;
                    // if there is a pixel there
                    if (f >= 0 && f < height && g >= 0 && g < width)
                    {
                        // add rgb values to respective sums
                        redsum += image[f][g].rgbtRed;
                        greensum += image[f][g].rgbtGreen;
                        bluesum += image[f][g].rgbtBlue;
                        // increase the number of pixels in average
                        boxsum++;
                    }
                }
            }
            // apply blured pixels to temp image
            temp[i][j].rgbtRed = round(redsum / boxsum);
            temp[i][j].rgbtGreen = round(greensum / boxsum);
            temp[i][j].rgbtBlue = round(bluesum / boxsum);
        }
    }
    // set real image to temp values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // initialize g array
    int gmod[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    //RGBRTRIPLEs for temp images
    int red[height][width];
    int green[height][width];
    int blue[height][width];
    for (int channel = RED; channel <= BLUE; channel ++)
    {
        // iterate through image vertically
        for (int i = 0; i < height; i++)
        {
            // iterate through image horizontally
            for (int j = 0; j < width; j++)
            {
                float sumx[] = {0, 0, 0};
                float sumy[] = {0, 0, 0};
                // iterate across pixel vertically
                for (int y = -1; y <= 1; y++)
                {
                    // iterate across pixel horizontally
                    for (int x = -1; x <= 1; x++)
                    {
                        // new coordinates with adjustment (f is vertical, g is horizontal)
                        int f = i + y;
                        int g = j + x;
                        // get g horizontal for channel
                        int mod = 0;
                        if (f >= 0 && f < height && g >= 0 && g < width)
                        {
                            // get g value based direction
                            mod = gmod[y + 1][x + 1];
                            // add g values to selected sum
                            if (channel == RED)
                            {
                                sumx[RED] += image[f][g].rgbtRed * mod;
                            }
                            else if (channel == GREEN)
                            {
                                sumx[GREEN] += image[f][g].rgbtGreen * mod;
                            }
                            else
                            {
                                sumx[BLUE] += image[f][g].rgbtBlue * mod;
                            }
                        }
                        //get g vertical for channel
                        if (f >= 0 && f < height && g >= 0 && g < width)
                        {
                            // get g value based direction
                            mod = gmod[x + 1][y + 1];
                            // add g values to selected sum
                            if (channel == RED)
                            {
                                sumy[RED] += image[f][g].rgbtRed * mod;
                            }
                            else if (channel == GREEN)
                            {
                                sumy[GREEN] += image[f][g].rgbtGreen * mod;
                            }
                            else
                            {
                                sumy[BLUE] += image[f][g].rgbtBlue * mod;
                            }
                        }
                    }
                }
                int result = round(sqrt((sumx[channel] * sumx[channel]) + (sumy[channel] * sumy[channel])));
                if (result > 255)
                {
                    result = 255;
                }
                if (channel == RED)
                {
                    red[i][j] = result;
                }
                else if (channel == GREEN)
                {
                    green[i][j] = result;
                }
                else
                {
                    blue[i][j] = result;
                }
            }
        }
    }
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[i][j].rgbtRed = red[i][j];
            image[i][j].rgbtGreen = green[i][j];
            image[i][j].rgbtBlue = blue[i][j];
        }
    }
    return;
}
