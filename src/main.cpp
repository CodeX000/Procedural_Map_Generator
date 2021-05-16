#define OLC_PGE_APPLICATION
#include "../include/olcPixelGameEngine.h"
#include "../include/noise.hpp"
#include <stdlib.h>

class MapGenerator : public olc::PixelGameEngine
{
public:
    MapGenerator()
    {
        sAppName = "Map Generator";
    }
private:
    //TODO: implement chunk system, chunks that are modified are saved and are loaded when seen again based on x,y coords
    double seed = rand();
    double modifier = 232.143324;
    int xPos = 0;
    int yPos = 0;
public:
    bool OnUserCreate() override
    {
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {

        Clear(olc::DARK_CYAN);
        if (GetKey(olc::Key::E).bHeld)
                seed -= .2123213;
        if (GetKey(olc::Key::R).bHeld)
            seed += .2123213;

        if (GetKey(olc::Key::W).bHeld)
            yPos--;
        if (GetKey(olc::Key::A).bHeld)
            xPos--;
        if (GetKey(olc::Key::S).bHeld)
            yPos++;
        if (GetKey(olc::Key::D).bHeld)
            xPos++;

        for(int x = xPos; x < ScreenWidth() + xPos; x++){
            for(int y = yPos; y < ScreenHeight() + yPos; y++){
                double perlinVal = (1 + perlin::noise((x * seed / modifier), (y * seed / modifier))) / 2.0;

                if(perlinVal > .75){
                    Draw(x - xPos, y - yPos, olc::VERY_DARK_GREY);
                }
                else if(perlinVal > .65){
                    Draw(x - xPos, y - yPos, olc::GREY);
                }
                else if(perlinVal > .55){
                    Draw(x - xPos, y - yPos, olc::VERY_DARK_GREEN);
                }
                else if(perlinVal > .52){
                    Draw(x - xPos, y - yPos, olc::DARK_GREEN);
                }
                else if(perlinVal > .5){
                    Draw(x - xPos, y - yPos, olc::WHITE);
                }
                else if(perlinVal > .3){
                    Draw(x - xPos, y - yPos, olc::DARK_BLUE);
                }
                else if(perlinVal > 0){
                    Draw(x - xPos, y - yPos, olc::VERY_DARK_BLUE);
                }

                //Draw(x, y, olc::Pixel(255 * perlinVal, 255 * perlinVal, 255 * perlinVal));
            }
        }

        return true;
    }

    bool OnUserDestroy() override
    {
        return true;
    }
};

int main() {
    int screenPixelsX = 128;
    int screenPixelsY = 128;

    MapGenerator map;
    if (map.Construct(screenPixelsX, screenPixelsY, 4, 4, false, true))
        map.Start();

    return 0;
}
