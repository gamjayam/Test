#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include"MoveObject.h"
#include "Utils.h"
#include "InputMgr.h"
#include <iostream>
#include "Branch.h"
#include "Player.h"
#include <SFML/Audio.hpp>
#include "ResourceMgr.h"


using namespace std;
using namespace sf;                 //sfml 에서 사용되는 네임스페이스


void UpdateBranches(vector<Branch*>& branches, int& current, vector<Vector2f>& posArr)
{
    current = (current + 1) % branches.size();

    for (int i = 0; i < branches.size(); ++i)
    {
        int index = (current + i) % branches.size();
        branches[index]->SetPosition(posArr[i]);
        if (i == branches.size() - 1)
        {
            branches[index]->SetSide((Sides)Utils::RandomRange(0, 2));
        }
    }
}

int main()
{
    VideoMode vm(1920, 1080);           //(가로 세로)픽셀 해상도
    RenderWindow window(vm, "Timber!!", Style::Default);
    
    auto resourceMgr = ResourceMgr::GetInstance();

    Sound timeOutSound;
    timeOutSound.setBuffer(*resourceMgr->GetSoundBuffer("sound/out_of_time.wav"));

    SoundBuffer DeathBuffer;
    DeathBuffer.loadFromFile("sound/death.wav");

    SoundBuffer ChopBuffer;
    ChopBuffer.loadFromFile("sound/chop.wav");



    ////////////////////////////////////////////////////////////


    Texture texBackground;                      //그림담는 데이터
    texBackground.loadFromFile("graphics/background.png");

    Texture texTree;                      
    texTree.loadFromFile("graphics/tree.png");
    Texture texBranch;
    texBranch.loadFromFile("graphics/branch.png");

    Texture texBee;                      
    texBee.loadFromFile("graphics/bee.png");
    Texture texCloud;                      
    texCloud.loadFromFile("graphics/cloud.png");


    Texture texPlayer;
    texPlayer.loadFromFile("graphics/player.png");
    Texture texRip;
    texRip.loadFromFile("graphics/rip.png");
    Texture texAxe;
    texAxe.loadFromFile("graphics/axe.png");


    ////////////////////////////////////////////////////////////

    std::list<SpriteGameObject*> gameObjectList;
    gameObjectList.push_back(new SpriteGameObject(texBackground));

    std::vector<float> startVector = { 2000, -300 };
    std::vector<float> endVector = { -300, 2000 };
    for (int i = 0; i < 3; i++)
    {
        auto movingObj = new MoveObject(texCloud);
        auto index = Utils::RandomRange(0,2);
        movingObj->Set({ 200,400 }, { 100,400 }, { startVector[index],0 }, { endVector[index], 0 });
        gameObjectList.push_back(movingObj);
    }


    vector<Branch*> branches(6);
    int currentBranch = 0 ;
    Vector2u size = window.getSize();
    
    SpriteGameObject* tree = new SpriteGameObject(texTree, Vector2f(size.x * 0.5f, 910));
    tree->SetOrigin(Origins::BC);
    gameObjectList.push_back(tree);

    for (int i = 0; i < branches.size(); ++i)
    {
        branches[i] = new Branch(texBranch, tree);
        branches[i]->SetSide((Sides)Utils::RandomRange(0, 2));
        gameObjectList.push_back(branches[i]);
    }
    

    auto movingObj = new MoveObject(texBee);
    movingObj->Set({ 200,400 }, { 500,1000 }, { 2000,0 }, { -100, 0 });
    
    //Vector2f startPos, endPos;
    //startPos.x = 2000;
    //startPos.y = (rand() % 500) + 300;
    //endPos.x = -100;
    //endPos.y = startPos.y;

    //movingObj->Set(Vector2i(200, 400), Vector2i(500, 1000), startPos, endPos);

    gameObjectList.push_back(movingObj);

    Player* player = new Player(texPlayer, texRip, texAxe, ChopBuffer, DeathBuffer);
    gameObjectList.push_back(player);

    player->Set(tree->GetPosition());

    for (auto go : gameObjectList)
    {
        go->Init();
    }

    vector<Vector2f> branchPosArr(branches.size());
    float x = branches[0]->GetPosition().x;
    float y = 800;
    float offset = branches[0]->GetSize().y;
    offset += 100;
    for (int i = 0; i < branches.size(); ++i)
    {
        branchPosArr[i] = Vector2f(x, y);
        y -= offset;
    }
    UpdateBranches(branches, currentBranch, branchPosArr);

   

    //gameObjectList.push_back(new MoveObject(texBee, Object::Bee));
    //gameObjectList.push_back(new MoveObject(texCloud, Object::Cloud));
    //gameObjectList.push_back(new MoveObject(texCloud, Object::Cloud));
    //gameObjectList.push_back(new MoveObject(texCloud, Object::Cloud));


    ////////////////////////////////////////////////////////////


    //Sprite spriteBackground;
    //spriteBackground.setTexture(texBackground);

    //Sprite spriteTree;
    //spriteTree.setTexture(texTree);
    //spriteTree.setPosition(810, 10.f);

    //std::vector<Sprite> bee(2);
    //for (int i = 0; i < bee.size(); i++)
    //{
    //    bee[i].setTexture(texBee);
    //    bee[i].setPosition(0, i * 250);
    //}

    //bool beeActive = false;
    //float beeSpeed = 0.f;

    //bool beeActive1 = false;
    //float beeSpeed1 = 0.f;


    //std::vector<Sprite> clouds(3);
    //
    //for (int i = 0; i < clouds.size(); i++)
    //{
    //    clouds[i].setTexture(texCloud);
    //    clouds[i].setPosition(0, i * 250);
    //}

    //bool cloudActive = false;
    //float cloudSpeed = 0.f;

    //bool cloudActive1 = false;
    //float cloudSpeed1 = 0.f;

    //bool cloudActive2 = false;
    //float cloudSpeed2 = 0.f;


    //////////////////////////////////////////////////////////


    // Font Resorce
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");


    // Ui Object Creates
    Text messeageText;
    messeageText.setFont(font);
    messeageText.setCharacterSize(75);
    messeageText.setFillColor(Color::White);
    messeageText.setString("Press Enter to start!");


    Utils::SetOrigin(messeageText, Origins::MC);


    //FloatRect rect = messeageText.getLocalBounds();
    //messeageText.setOrigin(
    //    rect.width * 0.5f,
    //    rect.height * 0.5f
    //);

    messeageText.setPosition(
        size.x * 0.5f,
        size.y * 0.5f
    );




    Text scoreText;
    int scorecount = 0;
    scoreText.setFont(font);
    scoreText.setCharacterSize(60);
    messeageText.setFillColor(Color::White);
    string str = "Score = " + to_string(scorecount);
    scoreText.setString(str);
    scoreText.setPosition(20, 20);


    Vector2f timerBarSize(400, 80);
    
    RectangleShape timerBar;

    timerBar.setSize(timerBarSize);
    timerBar.setFillColor(Color::Red);
    timerBar.setPosition(size.x * 0.5f - timerBarSize.x * 0.5f, size.y - 100);

    float duration = 4.0f;
    float timer = duration;

    bool isPause = true;


    //////////////////////////////////////////////////////////



    Clock clock;

    while (window.isOpen())
    {
        Time dt = clock.restart();
        Event ev;
        InputMgr::ClearInput();
        while (window.pollEvent(ev))
        {
            InputMgr::UpdateInput(ev);
        }


        if (InputMgr::GetKey(Keyboard::A))
        {
            //std::cout << "GetEky A" << endl;
        }

        if (InputMgr::GetKeyUp(Keyboard::A))
        {
            //std::cout << "GetEkyup A" << endl;
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
            continue;
        }

        if (InputMgr::GetKeyDown(Keyboard::Return))
        {
            if (timer > 0.f)
            {
                isPause = !isPause;
            }
            else
            {
                player->Release();
                messeageText.setString("Press Enter to start!");
                Utils::SetOrigin(messeageText, Origins::MC);
                scorecount = 0;
                timer = duration;
                for (auto go : gameObjectList)
                {
                    go->Init();
                }
                UpdateBranches(branches, currentBranch, branchPosArr);
                str = "Score = 0";
                scoreText.setString(str);
            }


            
        }






        size = window.getSize();
        float deltaTime = isPause ? 0.f : dt.asSeconds();

        //UI Update
        timer -= deltaTime;
        if (timer < 0.f || !player->GetAlive() )
        {
            if (!isPause)
            {
                timeOutSound.play();
            }

            timer = 0.f;
            isPause = true;
            messeageText.setString("Game Over! Press Enter");
            Utils::SetOrigin(messeageText, Origins::MC);
            player->Die();

        }

        float normTime = timer / duration;
        float timerSizeX = timerBarSize.x * normTime;


        timerBar.setSize({ timerSizeX, timerBarSize.y });
        timerBar.setPosition(size.x * 0.5f - timerSizeX * 0.5f, size.y - 100);

        

        //Update

        for (auto go : gameObjectList)
        {
            go->Updata(deltaTime);
        }

        if (InputMgr::GetKeyDown(Keyboard::Left) || InputMgr::GetKeyDown(Keyboard::A))
        {
            if (isPause || timerBar.getSize().x <= 0)
                continue;
            player->Chop(Sides::Left);
            timer += 0.1f;
            scorecount += 10;
            scoreText.setString("Score = " + to_string(scorecount));
            UpdateBranches(branches, currentBranch, branchPosArr);

        }
        if (InputMgr::GetKeyDown(Keyboard::Right) || InputMgr::GetKeyDown(Keyboard::D))
        {
            if (isPause || timerBar.getSize().x <= 0)
                continue;
            player->Chop(Sides::Right);
            timer += 0.1f;
            scorecount += 10;
            scoreText.setString("Score = " + to_string(scorecount));
            UpdateBranches(branches, currentBranch, branchPosArr);
        }
        if (InputMgr::GetKey(Keyboard::Key::Right) || InputMgr::GetKey(Keyboard::Key::Left))
        {
            if (isPause || timerBar.getSize().x <= 0)
                continue;
            player->isChopping = true;
        }
        else
        {
            player->isChopping = false;
        }


        if (player->GetPos() == branches[currentBranch]->GetPos())
        {
            player->Die();
        }

        //if (!cloudActive)
        //{
        //    cloudSpeed = (rand() % 200) + 200;
        //    cloudSpeed *= -1;
        //    float y = (rand() & 200) + 10;
        //    clouds[0].setPosition(2000, y);
        //    cloudActive = true;
        //}
        //else
        //{
        //    Vector2f pos = clouds[0].getPosition();
        //    pos.x += cloudSpeed * dt.asSeconds();
        //    clouds[0].setPosition(pos);
        //    if (pos.x < -300)
        //    {
        //        cloudActive = false;
        //    }
        //}

        //if (!cloudActive1)
        //{
        //    cloudSpeed1 = (rand() % 200) + 200;
        //    cloudSpeed1 *= -1;
        //    float y = (rand() & 200) + 100;
        //    clouds[1].setPosition(2000, y);
        //    cloudActive1 = true;
        //}
        //else
        //{
        //    Vector2f pos = clouds[1].getPosition();
        //    pos.x += cloudSpeed1 * dt.asSeconds();
        //    clouds[1].setPosition(pos);
        //    if (pos.x < -300)
        //    {
        //        cloudActive1 = false;
        //    }
        //}

        //if (!cloudActive2)
        //{
        //    cloudSpeed2 = (rand() % 200) + 200;
        //    cloudSpeed2 *= -1;
        //    float y = (rand() & 200) + 200;
        //    clouds[2].setPosition(2000, y);
        //    cloudActive2 = true;
        //}
        //else
        //{
        //    Vector2f pos = clouds[2].getPosition();
        //    pos.x += cloudSpeed2 * dt.asSeconds();
        //    clouds[2].setPosition(pos);
        //    if (pos.x < -300)
        //    {
        //        cloudActive2 = false;
        //    }
        //}


        //if (!beeActive)
        //{
        //    beeSpeed = (rand() % 200) + 200;
        //    beeSpeed *= -1;
        //    float y = (rand() & 500) + 300;
        //    bee[0].setPosition(2000, y);
        //    beeActive = true;
        //}
        //else
        //{
        //    Vector2f pos = bee[0].getPosition();
        //    pos.x += beeSpeed * dt.asSeconds();
        //    bee[0].setPosition(pos);
        //    if (pos.x < -100)
        //    {
        //        beeActive = false;
        //    }
        //}

        //if (!beeActive1)
        //{
        //    beeSpeed1 = (rand() % 200) + 200;
        //    beeSpeed1 *= -1;
        //    float y = (rand() & 500) + 300;
        //    bee[1].setPosition(2000, y);
        //    beeActive1 = true;
        //}
        //else
        //{
        //    Vector2f pos = bee[1].getPosition();
        //    pos.x += beeSpeed1 * dt.asSeconds();
        //    bee[1].setPosition(pos);
        //    if (pos.x < -100)
        //    {
        //        beeActive1 = false;
        //    }
        //}



        //Vector2f pos = spriteBee.getPosition();
        //pos.x += 200 * dt.asSeconds();
        //spriteBee.setPosition(pos);


        //Draw
        window.clear();

        for (auto go : gameObjectList)
        {
            go->Draw(window);
        }
        
        if (isPause)
        {
            window.draw(messeageText);
        }

        window.draw(scoreText);
        window.draw(timerBar);

       // window.draw(spriteBackground);

        //for (auto& cloud : clouds)
        //{
        //    window.draw(cloud);
        //}

        //window.draw(spriteTree);

        //for (auto& bees : bee)
        //{
        //    window.draw(bees);
        //}
         window.display();
    }


    for (auto go : gameObjectList)
    {
        go->Release();
        delete go;
    }
    gameObjectList.clear();





    return 0;
}