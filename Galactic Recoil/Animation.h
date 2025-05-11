#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Animation
{
private:
    Sprite* sprite; 
    Texture* texture; 

    // Separate frame vectors for each direction
    vector<IntRect> upFrames;
    vector<IntRect> leftFrames;
    vector<IntRect> downFrames;
    vector<IntRect> rightFrames;

    vector<IntRect>* activeFrames; // Pointer to the currently active frame vector

    float frameTime; // Time per frame in seconds
    float elapsedTime; // Time elapsed since the last frame change
    int currentFrame; // Index of the current frame

public:
    // Constructor
    Animation(Sprite* sprite, Texture* texture, float frameTime);


    // Add frames for each direction
    void addUpFrame(const IntRect& frame);
    void addLeftFrame(const IntRect& frame);
    void addDownFrame(const IntRect& frame);
    void addRightFrame(const IntRect& frame);

    // Set the active direction
    void setDirection(const std::string& direction);

    // Update the animation
    void update(float deltaTime);

    // Reset the animation
    void reset();
};



