#include <iostream>
#include<queue>
#include <graphics.h>
#include <time.h>

bool game[15][15];
int map[15][15];
bool pressedflag[15][15];
bool visited[15][15];
int life = 1;

void initmap() {
    memset(map, 0, sizeof(map));
    memset(game, 0, sizeof(game));
    memset(pressedflag, 0, sizeof(pressedflag));
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < 10; i++) {
        int x = rand() % 9 + 1;
        int y = rand() % 9 + 1;
        if (game[x][y] == 1) {
            i--;
            continue;
        }
        game[x][y] = 1;
    }
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            map[i][j] = game[i - 1][j + 1] + game[i][j + 1] + game[i + 1][j + 1] + game[i - 1][j] + game[i + 1][j] + game[i - 1][j - 1] + game[i][j - 1] + game[i + 1][j - 1];
        }
    }
    return;
}
void initgame() {
    settextcolor(BLACK);
    outtextxy(0, 0, _T("Coding by Kesoft"));
    IMAGE img,smile;
    loadimage(&smile, _T("src\\smile.png"));
    putimage(150, 20, &smile);
    loadimage(&img, _T("src\\map.png"));
    for (int i = 18; i < 342; i+=36) {
        for (int j = 118; j < 442; j+=36) {
            putimage(i, j, &img);
        }
    }
    life = 1;
    return;
}
int main()
{
    srand((unsigned)time(NULL));    //随机数种子
    initgraph(360,460);
    setbkcolor(RGB(198,198,198));
    cleardevice();
    initgame(); //初始化界面
    initmap();  //初始化地图
    IMAGE flag,empty,boomed,boom,dead;
    loadimage(&flag, _T("src\\flag.png"));
    loadimage(&empty, _T("src\\map.png"));
    loadimage(&boom, _T("src\\boom.png"));
    loadimage(&boomed, _T("src\\boomed.png"));
    loadimage(&dead, _T("src\\dead.png"));
    IMAGE number[10];
    loadimage(&number[0], _T("src\\0.png"));
    loadimage(&number[1], _T("src\\1.png"));
    loadimage(&number[2], _T("src\\2.png"));
    loadimage(&number[3], _T("src\\3.png"));
    loadimage(&number[4], _T("src\\4.png"));
    loadimage(&number[5], _T("src\\5.png"));
    loadimage(&number[6], _T("src\\6.png"));
    loadimage(&number[7], _T("src\\7.png"));
    loadimage(&number[8], _T("src\\8.png"));
    while (1) {
        ExMessage nowcheck;
        nowcheck = getmessage(EM_MOUSE);
        if (nowcheck.x >= 150 && nowcheck.x <= 210 && nowcheck.y >= 20 && nowcheck.y <= 80&&nowcheck.lbutton) {
            initgame();
            initmap();
        }
        if (life == 0) continue;
        if (nowcheck.x > 18 && nowcheck.x < 342 && nowcheck.y>118 && nowcheck.y < 442) {
            int x = (nowcheck.x - 18) / 36 + 1;
            int y = (nowcheck.y - 118) / 36 + 1;
            if (nowcheck.rbutton&&!(visited[x][y])) {
                if(pressedflag[x][y])   putimage(18 + (x - 1) * 36, 118 + (y - 1) * 36, &empty);
                else putimage(18 + (x - 1) * 36, 118 + (y - 1) * 36, &flag);
                pressedflag[x][y] = !pressedflag[x][y];
            }
            if (nowcheck.lbutton&&!visited[x][y]&&pressedflag[x][y]==0) {
                if (game[x][y]) {
                    putimage(18 + (x - 1) * 36, 118 + (y - 1) * 36, &boomed);   //游戏结束
                    putimage(150, 20, &dead);
                    for (int i = 1; i <= 9; i++) {
                        for (int j = 1; j <= 9; j++) {
                            if (game[i][j] && i != x && j != y) {
                                putimage(18 + (i - 1) * 36, 118 + (j - 1) * 36, &boom);
                            }
                        }
                    }
                    life = 0;
                }
                else {
                    std::queue<std::pair<int, int>>q;
                    q.push({x,y});
                    while (q.size()) {
                        int nx = q.front().first, ny = q.front().second;
                        q.pop();
                        if (nx >= 1 && nx <= 9 && ny >= 1 && ny <= 9&&visited[nx][ny]==0&&game[nx][ny]==0) {
                            visited[nx][ny] = 1;
                            if (map[nx][ny] == 0) {
                                q.push({ nx - 1,ny }); q.push({ nx + 1,ny }); q.push({ nx - 1,ny - 1 }); q.push({ nx + 1 ,ny - 1 }); q.push({ nx ,ny - 1 }); q.push({ nx + 1,ny + 1 }); q.push({ nx - 1,ny + 1 }); q.push({ nx ,ny + 1 });
                                putimage(18 + (nx - 1) * 36, 118 + (ny - 1) * 36, &number[0]);
                            }
                            else putimage(18 + (nx - 1) * 36, 118 + (ny - 1) * 36, &number[map[nx][ny]]);
                        }
                    }
                }
            }
        }
        int temp = 1;
        for (int i = 1; i <= 9; i++) {
            for (int j = 1; j <= 9; j++) {
                if (visited[i][j] == 0 && game[i][j] == 0) temp = 0;
            }
        }
        if (temp) {
            settextcolor(BLACK);
            RECT r = { 0, 0, 359, 459 };
            drawtext(_T("You Win"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            life = 0;
        }
        
    }
    return 0;
}
