#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#define WIDTH 300
#define HEIGHT 218
#define CHANNELS 3

float magnitude(int a, int b, int c)
{
    int result;
    result = sqrt(pow(a,2) + pow(b,2) + pow(c,2));
    return result;
}

int main(void) {
    int width, height, channels;

    unsigned char* background = stbi_load("./image/background.jpg", &width, &height, &channels, 0);
    if(background == NULL) {
        printf("Error in loading the image\n");
        exit(1);
    }
    //printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);

    unsigned char* object = stbi_load("./image/foreground.jpg", &width, &height, &channels, 0);
    if(object == NULL) {
        printf("Error in loading the image\n");
        exit(1);
    }
    
    unsigned char* forecast_bg = stbi_load("./image/new_background.jpg", &width, &height, &channels, 0);
    if(forecast_bg == NULL) {
        printf("Error in loading the image\n");
        exit(1);
    }

    // for(int i=0; i<HEIGHT; i++)
    // {
    //     for(int j=0; j<WIDTH; j++)
    //     {
    //         if (object[(i * width + j) * channels + 1]*1.5 < object[(i * width + j) * channels + 2] + object[(i * width + j) * channels])
    //         {
    //             for(int k=0; k<CHANNELS; k++)
    //             {
    //                 forecast_bg[(i * width + j) * channels + k] = object[(i * width + j) * channels + k];
    //             }
    //         }
    //     }        
	// }

    for(int i=0; i<HEIGHT;i++)
    {
    	for(int j=0; j<WIDTH;j++)
    	{
            if (magnitude(object[(i*WIDTH + j)*CHANNELS + 0]-background[(i*WIDTH+j)*CHANNELS + 0], object[(i*WIDTH+j)*CHANNELS + 1]-background[(i*WIDTH+j)*CHANNELS + 1], object[(i*WIDTH + j)*CHANNELS + 2]-background[(i*WIDTH+j)*CHANNELS + 2]) > 100)
            {
                forecast_bg[(i*WIDTH + j)*CHANNELS + 0] = object[(i*WIDTH + j)*CHANNELS + 0];
                forecast_bg[(i*WIDTH + j)*CHANNELS + 1] = object[(i*WIDTH + j)*CHANNELS + 1];
                forecast_bg[(i*WIDTH + j)*CHANNELS + 2] = object[(i*WIDTH + j)*CHANNELS + 2];
            }
    	}
	}

    stbi_write_jpg("./image/final.jpg", width, height, channels, forecast_bg, 100);
  
    stbi_image_free(background);
    stbi_image_free(object);
    stbi_image_free(forecast_bg);

    return 0;
}





