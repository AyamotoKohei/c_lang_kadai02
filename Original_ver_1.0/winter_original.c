/***
744041 綾本 公平
***/

#include <stdio.h>
#include <handy.h>

#define MAZE_SIDE   75     //迷路の横
#define MAZE_LENGTH 75     //迷路の縦
#define MAZE_WIDTH  30     //迷路１ブロックの幅
#define MAZE_HEIGHT 30     //迷路１ブロックの高さ

void EnemyMoveData(double *x, double *y, int flag, int layer2);

typedef struct Player {    //プレイヤーの関数宣言
    double x, y;
    int doorflag, side, leng;
} Player;

typedef struct Enemy {
    double x, y;
    int moveflag, side, leng;
} Enemy;

void MazeDraw(int MazeBlock[MAZE_SIDE][MAZE_LENGTH]){ // 迷路の生成
    int i, t, wid, leng;
    for(i = 0; i < MAZE_SIDE; i++){
    leng = MAZE_LENGTH * 10 - ((i + 1) * MAZE_HEIGHT);
        for(t = 0; t < MAZE_LENGTH; t++){
            wid = t * MAZE_WIDTH;
            if(MazeBlock[i][t] == 1){
                HgSetFillColor(HG_BLACK);
                HgBoxFill(wid, leng, MAZE_WIDTH, MAZE_HEIGHT, 1);
            }else if(MazeBlock[i][t] == 2){
                HgSetFillColor(HG_BLUE);
                HgBoxFill(wid, leng, MAZE_WIDTH, MAZE_HEIGHT, 1);
            }else if(MazeBlock[i][t] == 9){
                HgSetFillColor(HG_RED);
                HgBoxFill(wid, leng, MAZE_WIDTH, MAZE_HEIGHT, 1);
            }
        }
    }
}

void PlayerData(double x, double y, int layer1){
    HgWSetFillColor(layer1, HG_YELLOW);
    HgWCircleFill(layer1, x, y, MAZE_WIDTH / 2, 1);
}

void EnemyData(double x, double y, int layer2){
    HgWSetFillColor(layer2, HG_PURPLE);
    HgWCircleFill(layer2, x, y, MAZE_WIDTH / 2, 1);
}

void EnemyMoveData(double *x, double *y, int flag, int layer2){
    switch(flag){
            case 3:                                          //敵が右に移動
                *x = *x + MAZE_WIDTH;
                EnemyData(*x, *y, layer2);
                break;
            case 4:                                          //敵が左に移動
                *x = *x - MAZE_WIDTH;
                EnemyData(*x, *y, layer2);
                break;
            case 5:
                *y = *y + MAZE_HEIGHT;
                EnemyData(*x, *y, layer2);
                break;
            case 6:
                *y = *y - MAZE_HEIGHT;
                EnemyData(*x, *y, layer2);
                break;
    }
}

int main(void){
    int layer1, layer2;

    hgevent *event;
    
    Player player; // プレイヤーの構造体宣言
    player.x = MAZE_WIDTH / 2;
    player.y = MAZE_HEIGHT / 2;
    player.doorflag = 0;
    
    Enemy enemy01; // 敵の構造体宣言
    enemy01.x = (MAZE_WIDTH / 2) * 5;
    enemy01.y = (MAZE_LENGTH * 10) - 15;
    enemy01.moveflag = 4;

    Enemy enemy02;
    enemy02.x = (MAZE_SIDE * 10) - 15;
    enemy02.y = (MAZE_LENGTH * 10) - 45;
    enemy02.moveflag = 4;

    int MazeData[MAZE_SIDE][MAZE_LENGTH]={ // 迷路のマップデータ
        { 6, 0, 4, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 2 },
        { 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 6, 0, 4 },
        { 0, 1, 5, 0, 4, 1, 0, 1, 0, 0, 1, 6, 0, 0, 0, 0, 0, 0, 4, 1, 0, 1, 0, 1, 0 },
        { 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0 },
        { 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
        { 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
        { 0, 1, 9, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
        { 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 3, 0, 0, 6, 0, 0, 1, 5, 0, 0, 0, 4, 1, 0 },
        { 0, 1, 1, 1, 5, 0, 0, 4, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
        { 3, 0, 6, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 3, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 3, 0, 0, 0, 0, 5, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 5 },
        { 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0 },
        { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0 },
        { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        { 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0 },
        { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };
    
    HgOpen(MAZE_SIDE * 10, MAZE_LENGTH * 10);
    layer1 = HgWAddLayer(0);
    layer2 = HgWAddLayer(0);
    HgSetEventMask(HG_KEY_DOWN);                 //キー入力を扱う設定
    MazeDraw(MazeData);                          //迷路を描画(背景レイヤー)
    PlayerData(player.x, player.y, layer1);      //プレイヤーの描画(layer1)
    EnemyData(enemy01.x, enemy01.y, layer2);
    EnemyData(enemy02.x, enemy02.y, layer2);
    
    while(1){
        player.side = 24 - ((int)player.y / MAZE_HEIGHT);
        player.leng = (int)player.x / MAZE_WIDTH;
        enemy01.side = 24 - ((int)enemy01.y / MAZE_HEIGHT);
        enemy01.leng = (int)enemy01.x / MAZE_WIDTH;
        enemy02.side = 24 - ((int)enemy02.y / MAZE_HEIGHT);
        enemy02.leng = (int)enemy02.x / MAZE_WIDTH;         
        
        if(MazeData[enemy01.side][enemy01.leng] > 0){
            enemy01.moveflag = MazeData[enemy01.side][enemy01.leng];
        }

        if(MazeData[enemy02.side][enemy02.leng] > 0){
            enemy02.moveflag = MazeData[enemy02.side][enemy02.leng];
        }
        
        HgLClear(layer2);
        EnemyMoveData(&enemy01.x, &enemy01.y, enemy01.moveflag, layer2);
        EnemyMoveData(&enemy02.x, &enemy02.y, enemy02.moveflag, layer2);
       
        event = HgEventNonBlocking(); 
        if(event != NULL){
            HgLClear(layer1);                                //プレイヤーのレイヤー初期化
            switch(event->ch){
            case HG_U_ARROW:                                 //キーの上を入力
                if((MazeData[player.side-1][player.leng] != 1)&&(player.y + MAZE_HEIGHT < MAZE_LENGTH * 10))
                    player.y = player.y + MAZE_HEIGHT;
                PlayerData(player.x, player.y, layer1);      //プレイヤーの描画
                break;
            case HG_D_ARROW:                                 //キーの下を入力
                if((MazeData[player.side+1][player.leng] != 1)&&(player.y - MAZE_HEIGHT > 0))
                    player.y = player.y - MAZE_HEIGHT;
                PlayerData(player.x, player.y, layer1);      //プレイヤーの描画
                break;
            case HG_R_ARROW:                                 //キーの右を入力
                if((MazeData[player.side][player.leng+1] != 1)&&(player.x + MAZE_WIDTH < MAZE_SIDE * 10))
                    player.x = player.x + MAZE_WIDTH;
                PlayerData(player.x, player.y, layer1);      //プレイヤーの描画
                break;
            case HG_L_ARROW:                                 //キーの左を入力
                if((MazeData[player.side][player.leng-1] != 1)&&(player.x - MAZE_WIDTH > 0))
                    player.x = player.x - MAZE_WIDTH;
                PlayerData(player.x, player.y, layer1);      //プレイヤーの描画
                break;
            }
        }

        if((player.x - enemy01.x)*(player.x - enemy01.x)+(player.y - enemy01.y)*(player.y - enemy01.y) <= ((MAZE_WIDTH / 2)+(MAZE_WIDTH / 2))*((MAZE_WIDTH / 2)+(MAZE_WIDTH / 2)))
            break;
        if((player.x - enemy02.x)*(player.x - enemy02.x)+(player.y - enemy02.y)*(player.y - enemy02.y) <= ((MAZE_WIDTH / 2)+(MAZE_WIDTH / 2))*((MAZE_WIDTH / 2)+(MAZE_WIDTH / 2)))
            break;
        
        if(MazeData[player.side][player.leng] == 9)
            player.doorflag = 1;
        
        HgSleep(0.15);                                        // 少し待つ
        
        if((player.x < MAZE_SIDE * 10 && player.y < MAZE_LENGTH * 10)&&(player.x > MAZE_SIDE * 10 - MAZE_WIDTH && player.y > MAZE_LENGTH * 10 - MAZE_HEIGHT)&&(player.doorflag == 1))
            break;
         
    }

    return 0;
}