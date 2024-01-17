// SnakeGame.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <ConsoleEngine/EngineCore.h>
#include "Head.h"
#include "Wall.h"
#include "BodyManager.h"
#include "GlobalValue.h"
#include "SnakeGameEnum.h"

enum class SnakeOrder
{
    Body,
    Head,
};

int main()
{
    EngineCore EngineCore;

    const int ScreenX = 20;
    const int ScreenY = 20;

    EngineCore.Init({ ScreenX, ScreenY });

    {
        // Player* NewObject = new Player();
        GBodyManager = EngineCore.CreateManager<BodyManager>(0);
    }

    {
        // Player* NewObject = new Player();
        Head* NewPlayer = EngineCore.CreateObject<Head>(SnakeGameObjectType::Part);
        NewPlayer->SetPos({ ScreenX / 2, ScreenY - 2 });
    }

    {
        // 가로벽 생성
        for (int x = 0; x < ScreenX; ++x)
        {
            Wall* NewWall0 = EngineCore.CreateObject<Wall>(SnakeGameObjectType::Wall);
            NewWall0->SetPos({x, 0});
            NewWall0->SetRenderChar('W');

            Wall* NewWall1 = EngineCore.CreateObject<Wall>(SnakeGameObjectType::Wall);
            NewWall1->SetPos({ x, ScreenY - 1 });
            NewWall1->SetRenderChar('W');
        }

        // 세로벽 생성
        for (int y = 1; y < ScreenY - 1; ++y)
        {
            Wall* NewWall0 = EngineCore.CreateObject<Wall>(SnakeGameObjectType::Wall);
            NewWall0->SetPos({ 0, y });
            NewWall0->SetRenderChar('W');
 
            Wall* NewWall1 = EngineCore.CreateObject<Wall>(SnakeGameObjectType::Wall);
            NewWall1->SetPos({ ScreenX - 1, y });
            NewWall1->SetRenderChar('W');
        }
    }

    EngineCore.Start();
}
