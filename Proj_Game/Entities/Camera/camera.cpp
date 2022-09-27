#include "camera.h"

#define OFF_CAMERA_EXTRA_SPACE_COEFF 0.5f

Camera::Camera() :
    Ente(Ente::CAMERA, nullptr), players(), mapBounds(nullptr), view()
{
    this->Execute();
};
Camera::Camera(const sf::Vector2f _center, const sf::Vector2f _size, std::list<Characters::Player>* _pEntities, sf::FloatRect* _mapBounds):
    Ente(Ente::CAMERA, nullptr), players(), mapBounds(_mapBounds), view(_center, _size)
{
    std::list<Characters::Player>::iterator it;
    
    if(_pEntities != nullptr)
    {
        for (it = _pEntities->begin(); it != _pEntities->end(); it++)
        {
            if (it->GetType() == Ente::CHARACTER)
            {
                this->players.emplace_back(&(*it));
            }
        }
    }
    
    this->Execute();
};
Camera::~Camera()
{};

void Camera::Execute()
{
    std::list<Characters::Player*>::iterator it;
    sf::Vector2f diff, radious(this->view.getSize().x / 2.f, this->view.getSize().y / 2.f);
    sf::Vector2f least, most;
    float val = 0.f;

    constexpr float max = std::numeric_limits<float>::max();
    constexpr float min = std::numeric_limits<float>::lowest();

    if(this->players.size() > 0)
    {
        least = sf::Vector2f(max, max);
        most = sf::Vector2f(min, min);

        for (it = this->players.begin(); it != this->players.end(); it++)
        {
            if ((*it)->GetPosition().x < least.x)
                least.x = (*it)->GetPosition().x;
            if ((*it)->GetPosition().y < least.y)
                least.y = (*it)->GetPosition().y;

            if ((*it)->GetPosition().x > most.x)
                most.x = (*it)->GetPosition().x;
            if ((*it)->GetPosition().y > most.y)
                most.y = (*it)->GetPosition().y;
        }

        diff.x = most.x - least.x;
        diff.y = most.y - least.y;
        diff /= 2.f;

        least += diff;
    }

    if(this->mapBounds != nullptr && (this->mapBounds->left != this->mapBounds->width &&
        this->mapBounds->top != this->mapBounds->height)
      )
    {
        if (least.x - radious.x < this->mapBounds->left)
        {
            if (this->mapBounds->left <= 0)
                least.x += fabs(least.x - radious.x - this->mapBounds->left);
            else
                least.x += least.x - radious.x - this->mapBounds->left;
        }
        if (least.y - radious.y < this->mapBounds->top)
        {
            val = 0;
            val = (least.y - radious.y) - this->mapBounds->top;

            if (this->mapBounds->top <= 0)
            {
                val = least.y - radious.y;
                val = radious.y - this->mapBounds->top;
                least.y += fabs(least.y - radious.y - this->mapBounds->top);
            }
            else
                least.y += least.y - radious.y - this->mapBounds->top;
        }
        if (least.x + radious.x > this->mapBounds->width)
            least.x -= least.x + radious.x - this->mapBounds->width;
        if (least.y + radious.y > this->mapBounds->height)
            least.y -= least.y + radious.y - this->mapBounds->height;
    }

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

void Camera::AddPlayer(Characters::Player* pPlayer)
{
    if(pPlayer != nullptr)
    {
        this->players.emplace_back(pPlayer);
        this->Execute();
    }
};
void Camera::AddPlayerRange(std::list<Characters::Player*>* pPlayerList)
{
    std::list<Characters::Player*>::iterator it;
    if(pPlayerList != nullptr)
    {
        for (it = (*pPlayerList).begin(); it != (*pPlayerList).end(); it++)
            this->players.emplace_back((*it));
        this->Execute();
    }
};
void Camera::RemovePlayer(unsigned long long int id)
{
    std::list<Characters::Player*>::iterator it;
    for(it = this->players.begin(); it != this->players.end(); it++)
    {
        if ((*it)->GetId() == id)
            this->players.erase(it);
    }
    this->Execute();
};

// Versão com -std::List<Characters::Player>* players- da func execute;
/*
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
*/

// Versão com -Lista<Ente*>* pEntities- da func execute;
/*
    Lista<Ente*>::iterador it2;
    Entity* aux = nullptr;
for (it2 = this->pEntities->begin(); it2 != this->pEntities->end(); it2++)
    {
        if((*it2)->GetType() == Ente::CHARACTER)
        {
            aux = static_cast<Entity*>(*it2);

            if (aux->GetPosition().x < least.x)
                least.x = aux->GetPosition().x;
            if (aux->GetPosition().y < least.y)
                least.y = aux->GetPosition().y;

            if (aux->GetPosition().x > most.x)
                most.x = aux->GetPosition().x;
            if (aux->GetPosition().y > most.y)
                most.y = aux->GetPosition().y;
        }

    }
*/