#include "camera.h"

#define OFF_CAMERA_EXTRA_SPACE_COEFF 0.5f

Camera::Camera(std::list<Characters::Player>* _players) :
    players(_players), mapBounds(0.f, 0.f, 0.f, 0.f), view()
{
    this->Execute();
};
Camera::Camera(const sf::Vector2f _center, const sf::Vector2f _size, std::list<Characters::Player>* _players, const sf::FloatRect* _mapBounds):
    players(_players), mapBounds(), view(_center, _size)
{
    if (_mapBounds != nullptr)
        this->mapBounds = *_mapBounds;
    this->Execute();
};
Camera::~Camera()
{};

void Camera::Execute()
{
    constexpr float max = std::numeric_limits<float>::max();
    constexpr float min = std::numeric_limits<float>::lowest();
    
    std::list<Characters::Player>::iterator it;
    sf::Vector2f diff, radious(this->view.getSize().x / 2.f, this->view.getSize().y / 2.f);
    sf::Vector2f least(max, max), most(min, min);
    float val = 0.f;
    if (this->players != nullptr)
    {
        for (it = this->players->begin(); it != this->players->end(); it++)
        {
            if (it->GetPosition().x < least.x)
                least.x = it->GetPosition().x;
            if (it->GetPosition().y < least.y)
                least.y = it->GetPosition().y;

            if (it->GetPosition().x > most.x)
                most.x = it->GetPosition().x;
            if (it->GetPosition().y > most.y)
                most.y = it->GetPosition().y;
        }
    }

    diff.x = most.x - least.x;
    diff.y = most.y - least.y;
    diff /= 2.f;

    least += diff;

    if (least.x - radious.x < this->mapBounds.left)
    {
        if (this->mapBounds.left <= 0)
            least.x += fabs(least.x - radious.x - this->mapBounds.left);
        else
            least.x += least.x - radious.x - this->mapBounds.left;
    }
    if (least.y - radious.y < this->mapBounds.top)
    {
        val = 0 ;
        val = (least.y - radious.y) - this->mapBounds.top;

        if (this->mapBounds.top <= 0)
        {
            val = least.y - radious.y;
            val = radious.y - this->mapBounds.top;
            least.y += fabs(least.y - radious.y - this->mapBounds.top);
        }
        else
            least.y += least.y - radious.y - this->mapBounds.top;
    }
    if (least.x + radious.x > this->mapBounds.width)
        least.x -= least.x + radious.x - this->mapBounds.width;
    if (least.y + radious.y > this->mapBounds.height)
        least.y -= least.y + radious.y - this->mapBounds.height;

    this->view.setCenter(least);
};
const sf::FloatRect Camera::CameraBounds()
{
    sf::FloatRect bounds;

    bounds.left = this->view.getCenter().x - (this->view.getSize().x / 2.f);
    bounds.width = this->view.getCenter().x + (this->view.getSize().x / 2.f);
    bounds.top = this->view.getCenter().y - (this->view.getSize().y / 2.f);
    bounds.height = this->view.getCenter().y + (this->view.getSize().y / 2.f);

    return bounds;
};
std::vector<Entity*> Camera::GetCameraEntities(std::vector<Entity*>* entities)
{
    sf::FloatRect camBounds(this->CameraBounds());
    sf::FloatRect entBounds;
    std::vector<Entity*>::const_iterator cIt;
    std::vector<Entity*> entitiesInCam;

    camBounds.left -= ((this->view.getSize().x / 2.0f) * OFF_CAMERA_EXTRA_SPACE_COEFF);
    camBounds.top -= ((this->view.getSize().y / 2.0f) * OFF_CAMERA_EXTRA_SPACE_COEFF);
    camBounds.width += ((this->view.getSize().x / 2.0f) * OFF_CAMERA_EXTRA_SPACE_COEFF);
    camBounds.height += ((this->view.getSize().y / 2.0f) * OFF_CAMERA_EXTRA_SPACE_COEFF);

    if (entities != nullptr)
    {
        for (cIt = entities->cbegin(); cIt != entities->cend(); cIt++)
        {
            entBounds = (*cIt)->GetHitBoxBounds();

            if (entBounds.left > camBounds.left && entBounds.width < camBounds.width 
                && entBounds.top > camBounds.top && entBounds.height < camBounds.height)
                entitiesInCam.emplace_back((*cIt));
        }
    }

    return entitiesInCam;
};