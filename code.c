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

void subtract_background(unsigned char* img_1, unsigned char* img_2, unsigned char* img_3, char* file_name)
{
    for(int i=0; i<HEIGHT;i++)
    {
    	for(int j=0; j<WIDTH;j++)
    	{
            if (magnitude(img_2[(i*WIDTH + j)*CHANNELS + 0]-img_1[(i*WIDTH+j)*CHANNELS + 0], img_2[(i*WIDTH+j)*CHANNELS + 1]-img_1[(i*WIDTH+j)*CHANNELS + 1], img_2[(i*WIDTH + j)*CHANNELS + 2]-img_1[(i*WIDTH+j)*CHANNELS + 2]) > 100)
            {
                img_3[(i*WIDTH + j)*CHANNELS + 0] = img_2[(i*WIDTH + j)*CHANNELS + 0];
                img_3[(i*WIDTH + j)*CHANNELS + 1] = img_2[(i*WIDTH + j)*CHANNELS + 1];
                img_3[(i*WIDTH + j)*CHANNELS + 2] = img_2[(i*WIDTH + j)*CHANNELS + 2];
            }
    	}
	}
    stbi_write_jpg(file_name, WIDTH, HEIGHT, CHANNELS, img_3, 100);
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

    subtract_background(background, object, forecast_bg, "./image/final_1.jpg");

    stbi_image_free(background);
    stbi_image_free(object);
    stbi_image_free(forecast_bg);

    return 0;
}