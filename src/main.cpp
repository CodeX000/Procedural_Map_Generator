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
    double seed = .5;
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
                seed -= 1.0;
        if (GetKey(olc::Key::R).bHeld)
            seed += 1.0;

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
                double perlinVal = (1 + perlin::noise((x * seed), (y * seed))) / 2.0;
                Draw(x - xPos, y - yPos, olc::Pixel(255 * perlinVal, 255 * perlinVal, 255 * perlinVal));
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
    int screenPixelsX = 64;
    int screenPixelsY = 64;

    MapGenerator map;
    if (map.Construct(screenPixelsX, screenPixelsY, 8, 8, false, true))
        map.Start();

    return 0;
}
