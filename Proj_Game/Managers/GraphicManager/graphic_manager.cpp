#include "graphic_manager.h"
#include "../game/game.h"
using namespace Manager;

#define FONT_PATH "Proj_Game/Resources/fonts/EquipmentPro.ttf"

#define CAMERA_ZOOM 2.f
#define GAME_GRID_SIZE 32.f

#define VIEW_SIZE sf::Vector2f(1440.f / CAMERA_ZOOM, 810.f / CAMERA_ZOOM)
#define WINDOW_SIZE sf::Vector2i(1440, 810)

#define DISTORTION_X true
#define DISTORTION_Y true
#define BLCK_BAR_X true
#define BLCK_BAR_Y true

#define OFF_CAMERA_EXTRA_SPACE_COEFF 0.5f

float               GraphicManager::gridSize    =   GAME_GRID_SIZE;
sf::Font*           GraphicManager::font        =   nullptr;
GraphicManager*     GraphicManager::instance    =   nullptr;
sf::RenderWindow*   GraphicManager::window      =   nullptr;
sf::FloatRect       GraphicManager::cameraLim   =   sf::FloatRect();
TextureMap          GraphicManager::textures    =   TextureMap();
sf::View            GraphicManager::view        =   sf::View(sf::Vector2f(), VIEW_SIZE);

GraphicManager* GraphicManager::GetInstance(Interfaces* _pInterfaces)
{
    if (instance == nullptr)
    {
        instance = new GraphicManager(_pInterfaces);
        if (instance == nullptr)
            std::cerr << "Nao foi possivel instanciar um gerenciador grafico: graphic_manager." << std::endl;
    }

    return instance;
};
void GraphicManager::DesconstructInstance()
{
    if (instance != nullptr)
        delete instance;
};

GraphicManager::GraphicManager(Interfaces* _pInterfaces) :
    originalSize(VIEW_SIZE), pInterfaces(_pInterfaces),
    zoom(CAMERA_ZOOM), elapsedTimeRef(Game::GetElapsedTime()),
    distort_x(DISTORTION_X), distort_y(DISTORTION_Y),
    bar_x(BLCK_BAR_X), bar_y(BLCK_BAR_Y)
{
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "JANELA DE CONTEXTO");
    window->setKeyRepeatEnabled(false);

    if (font == nullptr)
    {
        font = new sf::Font();

        if (font != nullptr)
            font->loadFromFile(FONT_PATH);
        else
            std::cerr << "Nao foi possivel alocar uma fonte de texto: graphic_manager." << std::endl;
    }
};
GraphicManager::~GraphicManager()
{
    if (window != nullptr)
        delete window;

    if (font != nullptr)
        delete font;
};

void GraphicManager::UpdateCamera()
{
    std::list<Characters::Player*>::iterator it;
    std::list<Characters::Player*> pList = Characters::Player::GetPlayerList();
    sf::Vector2f diff, radious(view.getSize() / 2.f);
    sf::Vector2f least, most;

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

    if (cameraLim.left  != cameraLim.width &&
        cameraLim.top   != cameraLim.height)
    {
        if (least.x - radious.x < cameraLim.left)
        {
            if (cameraLim.left <= 0)
                least.x += fabs(least.x - radious.x - cameraLim.left);
            else
                least.x += least.x - radious.x - cameraLim.left;
        }
        if (least.y - radious.y < cameraLim.top)
        {
            if (cameraLim.top <= 0)
                least.y += fabs(least.y - radious.y - cameraLim.top);
            else
                least.y += least.y - radious.y - cameraLim.top;
        }
        if (least.x + radious.x > cameraLim.width)
            least.x -= least.x + radious.x - cameraLim.width;
        if (least.y + radious.y > cameraLim.height)
            least.y -= least.y + radious.y - cameraLim.height;
    }

    view.setCenter(least);
};
void GraphicManager::WindowResize() const
{
    sf::FloatRect newPort(0.f, 0.f, 1.f, 1.f);
    sf::Vector2f newSize(this->originalSize.x, this->originalSize.y);

    // Proporção do novo tamanho de tela em função do tamanho anterior
    sf::Vector2f ratio(
        window->getSize().x / this->zoom / this->originalSize.x,
        window->getSize().y / this->zoom / this->originalSize.y
    );

    if (this->distort_x)
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

    if (this->distort_y)
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

const Entities GraphicManager::GetCameraEntities(const Entities& entities)
{
    Entities::const_iterator cIt;
    Entities entitiesInCam;

    sf::Vector2f entSize;
    float delta_X = 0;

    for (cIt = entities.cbegin(); cIt != entities.cend(); cIt++)
    {
        entSize = (*cIt)->GetSize() / 2.f;
        delta_X = fabs(GetViewPosition().x - (*cIt)->GetPosition().x);

        if (delta_X <= (GetViewSize().x / 2.f * (1.f + OFF_CAMERA_EXTRA_SPACE_COEFF)) + entSize.x)
            entitiesInCam.emplace_back((*cIt));
    }

    return entitiesInCam;
};

void GraphicManager::Draw(const sf::RectangleShape& drawTarget)
{
    window->draw(drawTarget);
};
void GraphicManager::Draw(const sf::CircleShape& drawTarget)
{
    window->draw(drawTarget);
};
void GraphicManager::Draw(const sf::Sprite& drawTarget)
{
    window->draw(drawTarget);
};
void GraphicManager::Draw(const sf::Text& drawTarget)
{
    window->draw(drawTarget);
};

sf::Texture* GraphicManager::LoadTexture(std::string texturePath, sf::IntRect sheetCut)
{
    TextureMap::iterator it;
    std::stringstream sstring;
    sf::Texture* newTexture = nullptr;

    sstring << texturePath << sheetCut.left << 'x' << sheetCut.top;

    for (it = textures.begin(); it != textures.end(); it++)
    {
        if (it->first == texturePath || it->first == sstring.str())
            return it->second;
    }
    
    newTexture = new sf::Texture();
    if(newTexture == nullptr)
    {
        std::cerr << "Nao foi possivel instanciar um novo texture: " << texturePath << std::endl;
        return newTexture;
    }

    if(sheetCut.width != 0 && sheetCut.height != 0)
    {
        newTexture->loadFromFile(texturePath, sheetCut);
        textures.insert(std::pair<std::string, sf::Texture*>(sstring.str(), newTexture));
    }
    else
    {
        newTexture->loadFromFile(texturePath);
        textures.insert(std::pair<std::string, sf::Texture*>(texturePath, newTexture));
    }

    return newTexture;
};
void GraphicManager::Update()
{
	std::list<Ente*>::const_iterator cIt;

    window->clear();
    
    pInterfaces->top()->SelfPrint(elapsedTimeRef);

    window->setView(view);
    window->display();
};