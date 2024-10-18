#include "PongGameMod.h"

#include <set>

#include "TickAll.h"

PongGameMod::PongGameMod()
{
    SetName("PongGame");
    PointsPlayer = 0;
    PointsEnemy = 0;
    AmountOfBalls = 1;


    PlayerOne = std::make_shared<BaseRectangle>();
    PlayerTwo = std::make_shared<BaseRectangle>();
    Ball = std::make_shared<BaseCircle>();

    //PlayerOne
    PlayerOne->RestrictAxis('Y');
    PlayerOne->SetUseGravity(false);
    PlayerOne->SetIsControllable(true);
    PlayerOne->SetDimensions(Vector2{50,150});
    PlayerOne->SetColor(GREEN);
    PlayerOne->SetPosition(Vector2{50,0});
    PlayerOne->SetIsBoundByScreen(true);

    // Player Two 
    PlayerTwo->RestrictAxis('Y');
    PlayerTwo->SetUseGravity(false);
    PlayerTwo->SetIsControllable(false);
    PlayerTwo->SetDimensions(Vector2{50, 150});
    PlayerTwo->SetColor(GREEN);
    float StartPosPT = GetScreenWidth() - 100;
    PlayerTwo->SetPosition(Vector2{StartPosPT, 0});
    PlayerTwo->SetIsBoundByScreen(true);
    Ball->SetUseGravity(false);

    // Ball
    Ball->SetUseGravity(false);
    Ball->SetIsBoundByScreen(true);
    Ball->UseDrag(false);
    Vector2 BallPos;
    BallPos.x = GetScreenWidth()/2;
    BallPos.y = GetScreenHeight()/2;
    Ball->SetPosition(BallPos);
    Ball->SetStartVelocity(Vector2{-400,0});

     TempContainer = {PlayerOne,PlayerTwo};
    
}

PongGameMod::~PongGameMod()
{
}

void PongGameMod::Update()
{
    ClearBackground(GRAY);
    DrawFPS(200,200);
    m_DeltaTime = GetFrameTime();
    TickAll(m_DeltaTime);


    for (const auto& Rec : TempContainer)
    {
        if (CheckCollisionRecs(Rec->GetBBox(), Ball->GetBBox()))
        {
            Ball->CalculateCollision(Rec);
        }
    }
    
    
}

void PongGameMod::SetName(std::string NewName)
{
    GameMode::SetName(NewName);
}

std::string PongGameMod::GetName()
{
    return GameMode::GetName();
}
