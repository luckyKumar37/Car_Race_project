#include "Animation.h"

Animation::Animation(Sprite* sprite, Texture* texture, float frameTime)
    : sprite(sprite), texture(texture), frameTime(frameTime), elapsedTime(0.f), currentFrame(0), activeFrames(nullptr)
{
    this->sprite->setTexture(*this->texture);
}

void Animation::addUpFrame(const IntRect& frame)
{
    upFrames.push_back(frame);
}

void Animation::addLeftFrame(const IntRect& frame)
{
    leftFrames.push_back(frame);
}

void Animation::addDownFrame(const IntRect& frame)
{
    downFrames.push_back(frame);
}

void Animation::addRightFrame(const IntRect& frame)
{
    rightFrames.push_back(frame);
}

void Animation::setDirection(const std::string& direction)
{
    if (direction == "Up")
        activeFrames = &upFrames;
    else if (direction == "Left")
        activeFrames = &leftFrames;
    else if (direction == "Down")
        activeFrames = &downFrames;
    else if (direction == "Right")
        activeFrames = &rightFrames;

    reset(); // Reset's animation when changing direction
}

void Animation::update(float deltaTime)
{
    if (!activeFrames || activeFrames->empty()) return;

    // Updating elapsed time
    elapsedTime += deltaTime;

    // Changing frame if enough time has passed
    if (elapsedTime >= frameTime)
    {
        elapsedTime -= frameTime;
        currentFrame = (currentFrame + 1) % activeFrames->size();
        sprite->setTextureRect((*activeFrames)[currentFrame]);
    }
}

void Animation::reset()
{
    currentFrame = 0;
    elapsedTime = 0.f;
    if (activeFrames && !activeFrames->empty())
    {
        sprite->setTextureRect((*activeFrames)[0]);
    }
}

