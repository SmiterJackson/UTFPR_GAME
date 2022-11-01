#include "graphic_manager.h"
using namespace Manager;

#define FONT_PATH "Proj_Game/Resources/fonts/EquipmentPro.ttf"

#define CAMERA_ZOOM 2.f

#define VIEW_SIZE sf::Vector2f(1440.f / CAMERA_ZOOM, 810.f / CAMERA_ZOOM)
#define WINDOW_SIZE sf::Vector2i(1440, 810)

#define DISTORTION_X true
#define DISTORTION_Y true
#define BLCK_BAR_X true
#define BLCK_BAR_Y true

#define OFF_CAMERA_EXTRA_SPACE_COEFF 0.5f

GraphicManager*     GraphicManager::instance    =   nullptr;
sf::RenderWindow*   GraphicManager::window      =   nullptr;
Interfaces*         GraphicManager::pInterfaces =   nullptr;
unsigned short int* GraphicManager::pGameState  =   nullptr;
sf::Font*           GraphicManager::font        =   nullptr;
sf::View            GraphicManager::view        =   sf::View(sf::Vector2f(), VIEW_SIZE);
sf::FloatRect       GraphicManager::cameraLim   =   sf::FloatRect();
TextureMap          GraphicManager::textures = TextureMap();

GraphicManager* GraphicManager::GetGraphicInstance(float& _elapsedTimeRef, Interfaces* _pInterfaces)
{
    if (instance == nullptr)
    {
        instance = new GraphicManager(_elapsedTimeRef, _pInterfaces);
        if (instance == nullptr)
            std::cerr << "Nao foi possivel alocar um gerenciador grafico" << std::endl;
    }

    return instance;
};
void GraphicManager::DesconstructGraphicInstance()
{
    if (instance != nullptr)
        delete instance;
};

GraphicManager::GraphicManager(float& _elapsedTimeRef, Interfaces* _pInterfaces) :
    originalSize(VIEW_SIZE),
    zoom(CAMERA_ZOOM), elapsedTimeRef(_elapsedTimeRef),
    lock_x(DISTORTION_X), lock_y(DISTORTION_Y),
    bar_x(BLCK_BAR_X), bar_y(BLCK_BAR_Y)
{
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "JANELA DE CONTEXTO");

    window->setFramerateLimit(60);
    window->setKeyRepeatEnabled(false);

    pInterfaces = _pInterfaces;

    if (font == nullptr)
    {
        font = new sf::Font();

        if (font != nullptr)
            font->loadFromFile(FONT_PATH);
        else
            std::cerr << "Nao foi possivel alocar uma fonte de texto." << std::endl;
    }
};
GraphicManager::~GraphicManager()
{};

void GraphicManager::InvertDistortion_X()
{
    this->lock_x = !this->lock_x;
    if (!this->lock_x && this->bar_x)
        this->bar_x = false;
};
void GraphicManager::InvertDistortion_Y()
{
    this->lock_y = !this->lock_y;
    if (!this->lock_y && this->bar_y)
        this->bar_y = false;
};
void GraphicManager::InvertBar_X()
{
    this->bar_x = !this->bar_x;
    if (this->bar_x && !this->lock_x)
        this->lock_x = true;
};
void GraphicManager::InvertBar_Y()
{
    this->bar_y = !this->bar_y;
    if (this->bar_y && !this->lock_y)
        this->lock_y = true;
};

void GraphicManager::UpdateCamera()
{
    std::list<Characters::Player*>::iterator it;
    std::list<Characters::Player*> pList = Characters::Player::GetPlayerList();
    sf::Vector2f diff, radious(view.getSize() / 2.f);
    sf::Vector2f least, most;
    float val = 0.f;

    constexpr float max = std::numeric_limits<float>::max();
    constexpr float min = std::numeric_limits<float>::lowest();

    // Retira o centro entre todas as intâncias de Player
    if (pList.size() > 0)
    {
        least = sf::Vector2f(max, max);
        most = sf::Vector2f(min, min);

        for (it = pList.begin(); it != pList.end(); it++)
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

    view.setCenter(least);
};
void GraphicManager::WindowResize()
{
    sf::FloatRect newPort(0.f, 0.f, 1.f, 1.f);
    sf::Vector2f newSize(this->originalSize.x, this->originalSize.y);

    // Proporção do novo tamanho de tela em função do tamanho anterior
    sf::Vector2f ratio(
        window->getSize().x / this->zoom / this->originalSize.x,
        window->getSize().y / this->zoom / this->originalSize.y
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

    if (this->lock_y)
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

    view.setSize(newSize);
    view.setViewport(newPort);
};

const ColisonVector GraphicManager::GetCameraEntities(const ColisonVector& entities)
{
    Manager::ColisonVector::const_iterator cIt;
    Manager::ColisonVector entitiesInCam;

    sf::FloatRect camBounds(GetViewBounds());
    sf::FloatRect entBounds;

    camBounds.left      -= ((view.getSize().x / 2.0f) * OFF_CAMERA_EXTRA_SPACE_COEFF);
    camBounds.top       -= ((view.getSize().y / 2.0f) * OFF_CAMERA_EXTRA_SPACE_COEFF);
    camBounds.width     += ((view.getSize().x / 2.0f) * OFF_CAMERA_EXTRA_SPACE_COEFF);
    camBounds.height    += ((view.getSize().y / 2.0f) * OFF_CAMERA_EXTRA_SPACE_COEFF);

    for (cIt = entities.cbegin(); cIt != entities.cend(); cIt++)
    {
        entBounds = (*cIt)->GetBounds();

        if (    entBounds.left  >   camBounds.left  && entBounds.width  < camBounds.width
            &&  entBounds.top   >   camBounds.top   && entBounds.height < camBounds.height)
            entitiesInCam.emplace_back((*cIt));
    }

    return entitiesInCam;
};
const sf::FloatRect GraphicManager::GetViewBounds()
{
    return sf::FloatRect(
        view.getCenter().x - view.getSize().x,
        view.getCenter().y - view.getSize().y,
        view.getCenter().x + view.getSize().x,
        view.getCenter().y + view.getSize().y
    );
};

sf::Texture* GraphicManager::LoadTexture(std::string texturePath)
{
    TextureMap::iterator it;
    sf::Texture* newTexture = nullptr;

    for (it = textures.begin(); it != textures.end(); it++)
    {
        if (it->first == texturePath)
            return it->second;
    }
    
    newTexture = new sf::Texture();
    if(newTexture == nullptr)
    {
        std::cerr << "Nao foi possivel abrir a nova texture: " << texturePath << std::endl;
        return newTexture;
    }

    newTexture->loadFromFile(texturePath);
    textures.insert(std::pair<std::string, sf::Texture*>(texturePath, newTexture));

    return newTexture;
};
void GraphicManager::Draw()
{
	std::list<Ente*>::const_iterator cIt;

    window->clear();

	pInterfaces->top()->SelfPrint(*window, elapsedTimeRef);

    window->setView(view);
    window->display();
};