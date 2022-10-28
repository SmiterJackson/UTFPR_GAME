#include "camera.h"

#define OFF_CAMERA_EXTRA_SPACE_COEFF 0.5f

Camera::Camera() :
    Ente(Type::CAMERA), 
    Collidable(true), 
    originalSize(), players(),
    view(), zoom(1.f),
    lock_x(true), loack_y(true), bar_x(true), bar_y(true)
{
    this->Execute(0.f);
};
Camera::Camera(const sf::Vector2f _center, const sf::Vector2f _size, float _zoom,
               std::list<Characters::Player>* _pEntities, sf::FloatRect* _mapBounds,
               bool _lock_x, bool _lock_y, bool _bar_x, bool _bar_y) :
    Ente(Type::CAMERA),
    Collidable(true),
    originalSize(_size), players(),
    view(_center, _size), zoom(_zoom),
    lock_x(_lock_x), loack_y(_lock_y), bar_x(_bar_x), bar_y(_bar_y)
{
    std::list<Characters::Player>::iterator it;
    
    if(_pEntities != nullptr)
    {
        for (it = _pEntities->begin(); it != _pEntities->end(); it++)
        {
            this->players.emplace_back(&(*it));
        }
    }
    
    if (this->zoom == 0.f)
        this->zoom = 1.f;

    this->Execute(0.f);
};
Camera::~Camera()
{};

const sf::Vector2f const Camera::GetPosition()
{
    return this->view.getCenter();
};
void Camera::MovePosition(const sf::Vector2f _newPosition)
{
    this->view.setCenter(_newPosition);
};
void Camera::MovePosition(const float X_axis, const float Y_axis)
{
    this->view.setCenter(X_axis, Y_axis);
};

const const sf::FloatRect const Camera::GetBounds()
{
    sf::FloatRect bounds;

    bounds.left = this->view.getCenter().x - (this->view.getSize().x / 2.f);
    bounds.width = this->view.getCenter().x + (this->view.getSize().x / 2.f);
    bounds.top = this->view.getCenter().y - (this->view.getSize().y / 2.f);
    bounds.height = this->view.getCenter().y + (this->view.getSize().y / 2.f);

    return bounds;
};
const std::vector<Entity*> Camera::GetCameraEntities(const std::vector<Entity*>* entities)
{
    sf::FloatRect camBounds(this->GetBounds());
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
            entBounds = (*cIt)->GetBounds();

            if (entBounds.left > camBounds.left && entBounds.width < camBounds.width
                && entBounds.top > camBounds.top && entBounds.height < camBounds.height)
                entitiesInCam.emplace_back((*cIt));
        }
    }

    return entitiesInCam;
};
void Camera::WindowResized(const sf::RenderWindow& window)
{
    sf::FloatRect newPort(0.f, 0.f, 1.f, 1.f);
    sf::Vector2f newSize(this->originalSize.x, this->originalSize.y);

    // Proporção do novo tamanho de tela em função do tamanho anterior
    sf::Vector2f ratio(
        window.getSize().x / this->zoom / this->originalSize.x,
        window.getSize().y / this->zoom / this->originalSize.y
    );

    if (this->lock_x)
    {
        if (this->bar_x)
        {
            if (ratio.x > 1.f)
            {
                ratio.x = 1.f / ratio.x;
                ratio.x = 1.f - ratio.x;

                newPort.left += ratio.x / 2.f;
                newPort.width -= ratio.x;
            }
        }
    }
    else
        newSize.x = this->originalSize.x * ratio.x;

    if (this->loack_y)
    {
        if (this->bar_y)
        {
            if (ratio.y > 1.f)
            {
                ratio.y = 1.f / ratio.y;
                ratio.y = 1.f - ratio.y;

                newPort.top += ratio.y / 2.f;
                newPort.height -= ratio.y;
            }
        }
    }
    else
        newSize.y = this->originalSize.y * ratio.y;

    this->view.setSize(newSize);
    this->view.setViewport(newPort);
};

void Camera::AddPlayer(Characters::Player* pPlayer)
{
    if (pPlayer != nullptr)
    {
        this->players.emplace_back(pPlayer);
        this->Execute(0.f);
    }
};
void Camera::AddPlayerRange(std::list<Characters::Player*>* pPlayerList)
{
    std::list<Characters::Player*>::iterator it;
    if (pPlayerList != nullptr)
    {
        for (it = (*pPlayerList).begin(); it != (*pPlayerList).end(); it++)
            this->players.emplace_back((*it));
        this->Execute(0.f);
    }
};
void Camera::RemovePlayer(unsigned long long int id)
{
    std::list<Characters::Player*>::iterator it;
    for (it = this->players.begin(); it != this->players.end(); it++)
    {
        if ((*it)->GetId() == id)
            this->players.erase(it);
    }
    this->Execute(0.f);
};

void Camera::Execute(const float& pElapsedTime)
{
    std::list<Characters::Player*>::iterator it;
    sf::Vector2f diff, radious(this->view.getSize() / 2.f);
    sf::Vector2f least, most;
    float val = 0.f;

    constexpr float max = std::numeric_limits<float>::max();
    constexpr float min = std::numeric_limits<float>::lowest();

    // Retira o centro entre todas as intâncias de Player
    if (this->players.size() > 0)
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

    this->MovePosition(least);
};

// Método anterior para manter a camera no limites do mapa
/*    
if (this->mapBounds != nullptr)
{
    if (this->mapBounds->left != this->mapBounds->width &&
        this->mapBounds->top != this->mapBounds->height)
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
}
*/