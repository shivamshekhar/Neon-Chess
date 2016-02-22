/*
Neon Chess header
Made by: Shivam Shekhar
*/
///Macros
#define CHESSGRID(x) (2*x + 1) //determines chess pieces position on chess board
#define MOUSEPOSX(x) ((x-33)/2) //determines x coord of chess pieces on mouse clicks
#define MOUSEPOSY(y) ((y-5)/2) //determines y coord of chess pieces on mouse clicks
#define PAWN 24
#define ROOK 4
#define KNIGHT 5
#define BISHOP 235
#define KING 11
#define QUEEN 12
#define _B 10 //color green for p2
#define _W 14 //color yellow for p1
#define HIGHLIGHTW 207 //highlights p1
#define HIGHLIGHTB 192 //highlights p2
int chessboardmap[17][17]=    //our chessboard map
                        {
                            {218,196,194,196,194,196,194,196,194,196,194,196,194,196,194,196,191},
                            {179,0,179,0,179,0,179,0,179,0,179,0,179,0,179,0,179},
                            {195,196,197,196,197,196,197,196,197,196,197,196,197,196,197,196,180},
                            {179,0,179,0,179,0,179,0,179,0,179,0,179,0,179,0,179},
                            {195,196,197,196,197,196,197,196,197,196,197,196,197,196,197,196,180},
                            {179,0,179,0,179,0,179,0,179,0,179,0,179,0,179,0,179},
                            {195,196,197,196,197,196,197,196,197,196,197,196,197,196,197,196,180},
                            {179,0,179,0,179,0,179,0,179,0,179,0,179,0,179,0,179},
                            {195,196,197,196,197,196,197,196,197,196,197,196,197,196,197,196,180},
                            {179,0,179,0,179,0,179,0,179,0,179,0,179,0,179,0,179},
                            {195,196,197,196,197,196,197,196,197,196,197,196,197,196,197,196,180},
                            {179,0,179,0,179,0,179,0,179,0,179,0,179,0,179,0,179},
                            {195,196,197,196,197,196,197,196,197,196,197,196,197,196,197,196,180},
                            {179,0,179,0,179,0,179,0,179,0,179,0,179,0,179,0,179},
                            {195,196,197,196,197,196,197,196,197,196,197,196,197,196,197,196,180},
                            {179,0,179,0,179,0,179,0,179,0,179,0,179,0,179,0,179},
                            {192,196,193,196,193,196,193,196,193,196,193,196,193,196,193,196,217},
                        };
    int chesspieces[8][8]= //chess pieces
                            {
                                {ROOK,KNIGHT,BISHOP,KING,QUEEN,BISHOP,KNIGHT,ROOK},
                                {PAWN,PAWN,PAWN,PAWN,PAWN,PAWN,PAWN,PAWN},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {PAWN,PAWN,PAWN,PAWN,PAWN,PAWN,PAWN,PAWN},
                                {ROOK,KNIGHT,BISHOP,KING,QUEEN,BISHOP,KNIGHT,ROOK}
                            };
    int chesspiecescolor[8][8]= //color of chess pieces
                                {
                                    {_B,_B,_B,_B,_B,_B,_B,_B},
                                    {_B,_B,_B,_B,_B,_B,_B,_B},
                                    {0,0,0,0,0,0,0,0},
                                    {0,0,0,0,0,0,0,0},
                                    {0,0,0,0,0,0,0,0},
                                    {0,0,0,0,0,0,0,0},
                                    {_W,_W,_W,_W,_W,_W,_W,_W},
                                    {_W,_W,_W,_W,_W,_W,_W,_W}
                                };
    int ispiecepick=FALSE /*determines whether a piece is picked or not*/,playerturn=_W /*determines whose turn it is*/,hasWkingmoved=FALSE,hasBkingmoved=FALSE /*Determines whether black or white kings have moved*/;
    SMALL_RECT chessboardrect={32,4,49,21}; //chess board rectangle
    CHAR_INFO chessboard[289]; //chess board
    COORD chessboardsz={17,17},zerozero={0,0},pickedpiece,buttonpos; /*chess board size, origin, determines coordinates of the piece which is picked*/
///function declarations
void printchessboard(void);
void initializechessboard(void);
void piecepick(int,int);
void piecemove(int,int);
void printsign(void);
void printbuttons(void);
void reset(void);
void save(void);
void load(void);
void help(void);
int checkwin(void);
void pawnpromotion(int,int);
int iskingcheck(void);
///function definitions
void printchessboard() //prints chess board
{
    int i,j;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            chessboard[CHESSGRID(j)+17*CHESSGRID(i)].Char.AsciiChar=chesspieces[i][j];
            chessboard[CHESSGRID(j)+17*CHESSGRID(i)].Attributes=chesspiecescolor[i][j];
        }
    }
    WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE),chessboard,chessboardsz,zerozero,&chessboardrect);
}
//
void initializechessboard() //initializes chess board for the first time
{
    int i,j;
    system("cls");
    for(i=0;i<17;i++)
    {
        for(j=0;j<17;j++)
        {
            chessboard[j+17*i].Char.AsciiChar=chessboardmap[i][j];
            chessboard[j+17*i].Attributes=15;

        }
    }
    printchessboard();
    printbuttons();
    printsign();
}
//
void piecepick(int x,int y) //picks up a piece
{
    int i,j;
    if(playerturn==_W && chesspiecescolor[y][x]==_W && chesspieces[y][x]!=0)
    {
        pickedpiece.X=x;
        pickedpiece.Y=y;
        ispiecepick=TRUE;
        chesspiecescolor[y][x]=HIGHLIGHTW;
        printchessboard();
    }
    if(playerturn==_B && chesspiecescolor[y][x]==_B && chesspieces[y][x]!=0)
    {
       pickedpiece.X=x;
       pickedpiece.Y=y;
       ispiecepick=TRUE;
       chesspiecescolor[y][x]=HIGHLIGHTB;
       printchessboard();
    }
}
//
void piecemove(int x,int y) //moves the picked piece to (x,y)
{
    int i,j,rookmove=FALSE,bishopmove=FALSE,queenmove=FALSE;
    if(playerturn==_W) //white's turn
    {
        switch(chesspieces[pickedpiece.Y][pickedpiece.X])
        {
        case PAWN: //pawn's moves
            if(chesspieces[pickedpiece.Y - 1][pickedpiece.X]==0 && x==pickedpiece.X && y==pickedpiece.Y - 1)
            {
                if(y==0)
                {
                    pawnpromotion(x,y);
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_W;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_B;
                }
                else
                {
                    chesspieces[y][x]=PAWN;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_W;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_B;
                }
                printchessboard();
            }
            else if(chesspiecescolor[pickedpiece.Y - 1][pickedpiece.X - 1]==_B && x==pickedpiece.X - 1 && y==pickedpiece.Y - 1)
            {
                chesspieces[y][x]=PAWN;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else if(chesspiecescolor[pickedpiece.Y - 1][pickedpiece.X + 1]==_B && x==pickedpiece.X + 1 && y==pickedpiece.Y - 1)
            {
                chesspieces[y][x]=PAWN;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else if(chesspieces[pickedpiece.Y - 2][pickedpiece.X]==0 && pickedpiece.Y==6 && x==pickedpiece.X && y==pickedpiece.Y - 2)
            {
                chesspieces[y][x]=PAWN;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else
            {
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                ispiecepick=FALSE;
                printchessboard();
            }
            break;
        case KING: //king's moves
            if((chesspieces[pickedpiece.Y - 1][pickedpiece.X]==0 || chesspiecescolor[pickedpiece.Y - 1][pickedpiece.X]==_B) && x==pickedpiece.X && y==pickedpiece.Y - 1)
            {
                if(hasWkingmoved==FALSE)
                    hasWkingmoved=TRUE;
                chesspieces[y][x]=KING;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y + 1][pickedpiece.X]==0 || chesspiecescolor[pickedpiece.Y + 1][pickedpiece.X]==_B) && x==pickedpiece.X && y==pickedpiece.Y + 1)
            {
                if(hasWkingmoved==FALSE)
                    hasWkingmoved=TRUE;
                chesspieces[y][x]=KING;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y][pickedpiece.X + 1]==0 || chesspiecescolor[pickedpiece.Y][pickedpiece.X + 1]==_B) && x==pickedpiece.X + 1 && y==pickedpiece.Y)
            {
                if(hasWkingmoved==FALSE)
                    hasWkingmoved=TRUE;
                chesspieces[y][x]=KING;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y][pickedpiece.X - 1]==0 || chesspiecescolor[pickedpiece.Y][pickedpiece.X - 1]==_B) && x==pickedpiece.X - 1 && y==pickedpiece.Y)
            {
                if(hasWkingmoved==FALSE)
                    hasWkingmoved=TRUE;
                chesspieces[y][x]=KING;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y + 1][pickedpiece.X + 1]==0 || chesspiecescolor[pickedpiece.Y + 1][pickedpiece.X + 1]==_B) && x==pickedpiece.X + 1 && y==pickedpiece.Y + 1)
            {
                if(hasWkingmoved==FALSE)
                    hasWkingmoved=TRUE;
                chesspieces[y][x]=KING;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y + 1][pickedpiece.X - 1]==0 || chesspiecescolor[pickedpiece.Y + 1][pickedpiece.X - 1]==_B) && x==pickedpiece.X - 1 && y==pickedpiece.Y + 1)
            {
                if(hasWkingmoved==FALSE)
                    hasWkingmoved=TRUE;
                chesspieces[y][x]=KING;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y - 1][pickedpiece.X - 1]==0 || chesspiecescolor[pickedpiece.Y - 1][pickedpiece.X - 1]==_B) && x==pickedpiece.X - 1 && y==pickedpiece.Y - 1)
            {
                if(hasWkingmoved==FALSE)
                    hasWkingmoved=TRUE;
                chesspieces[y][x]=KING;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y - 1][pickedpiece.X + 1]==0 || chesspiecescolor[pickedpiece.Y - 1][pickedpiece.X + 1]==_B) && x==pickedpiece.X + 1 && y==pickedpiece.Y - 1)
            {
                if(hasWkingmoved==FALSE)
                    hasWkingmoved=TRUE;
                chesspieces[y][x]=KING;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else
            {
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                ispiecepick=FALSE;
                printchessboard();
            }
            break;
        case KNIGHT: //Knight's moves
            if((chesspieces[pickedpiece.Y - 2][pickedpiece.X - 1]==0 || chesspiecescolor[pickedpiece.Y - 2][pickedpiece.X - 1]==_B) && x==pickedpiece.X - 1 && y==pickedpiece.Y - 2)
            {
                chesspieces[y][x]=KNIGHT;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y - 2][pickedpiece.X + 1]==0 || chesspiecescolor[pickedpiece.Y - 2][pickedpiece.X + 1]==_B) && x==pickedpiece.X + 1 && y==pickedpiece.Y - 2)
            {
                chesspieces[y][x]=KNIGHT;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y - 1][pickedpiece.X - 2]==0 || chesspiecescolor[pickedpiece.Y - 1][pickedpiece.X - 2]==_B) && x==pickedpiece.X - 2 && y==pickedpiece.Y - 1)
            {
                chesspieces[y][x]=KNIGHT;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y - 1][pickedpiece.X + 2]==0 || chesspiecescolor[pickedpiece.Y - 1][pickedpiece.X + 2]==_B) && x==pickedpiece.X + 2 && y==pickedpiece.Y - 1)
            {
                chesspieces[y][x]=KNIGHT;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y + 1][pickedpiece.X + 2]==0 || chesspiecescolor[pickedpiece.Y + 1][pickedpiece.X + 2]==_B) && x==pickedpiece.X + 2 && y==pickedpiece.Y + 1)
            {
                chesspieces[y][x]=KNIGHT;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y + 1][pickedpiece.X - 2]==0 || chesspiecescolor[pickedpiece.Y + 1][pickedpiece.X - 2]==_B) && x==pickedpiece.X - 2 && y==pickedpiece.Y + 1)
            {
                chesspieces[y][x]=KNIGHT;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y + 2][pickedpiece.X - 1]==0 || chesspiecescolor[pickedpiece.Y + 2][pickedpiece.X - 1]==_B) && x==pickedpiece.X - 1 && y==pickedpiece.Y + 2)
            {
                chesspieces[y][x]=KNIGHT;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y + 2][pickedpiece.X + 1]==0 || chesspiecescolor[pickedpiece.Y + 2][pickedpiece.X + 1]==_B) && x==pickedpiece.X + 1 && y==pickedpiece.Y + 2)
            {
                chesspieces[y][x]=KNIGHT;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_W;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_B;
                printchessboard();
            }
            else
            {
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                ispiecepick=FALSE;
                printchessboard();
            }
            break;
        case ROOK: //rook's moves
            if(y==pickedpiece.Y)
            {
                if(x > pickedpiece.X)
                {
                    for(i=pickedpiece.X + 1;i<x;i++)
                    {
                        if(chesspieces[y][i]!=0)
                        {
                            rookmove=FALSE;
                            i--;
                            break;
                        }
                    }
                    if(i==x && (chesspiecescolor[y][i]==_B || chesspiecescolor[y][i]==0))
                        rookmove=TRUE;
                    switch(rookmove)
                    {
                    case TRUE:
                        chesspieces[y][x]=ROOK;
                        chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                        chesspiecescolor[y][x]=_W;
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                        ispiecepick=FALSE;
                        playerturn=_B;
                        printchessboard();
                        break;
                    case FALSE:
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                        ispiecepick=FALSE;
                        printchessboard();
                        break;
                    }
                }
                else if(x < pickedpiece.X)
                {
                    for(i=pickedpiece.X - 1;i>x;i--)
                    {
                        if(chesspieces[y][i]!=0)
                        {
                            rookmove=FALSE;
                            i++;
                            break;
                        }
                    }
                    if(i==x && (chesspiecescolor[y][i]==_B || chesspiecescolor[y][i]==0))
                        rookmove=TRUE;
                    switch(rookmove)
                    {
                    case TRUE:
                        chesspieces[y][x]=ROOK;
                        chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                        chesspiecescolor[y][x]=_W;
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                        ispiecepick=FALSE;
                        playerturn=_B;
                        printchessboard();
                        break;
                    case FALSE:
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                        ispiecepick=FALSE;
                        printchessboard();
                        break;
                    }
                }
                else
                {
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                    ispiecepick=FALSE;
                    printchessboard();
                }
            }
            else if(x==pickedpiece.X)
            {
                if(y > pickedpiece.Y)
                {
                    for(i=pickedpiece.Y + 1;i<y;i++)
                    {
                        if(chesspieces[i][x]!=0)
                        {
                            rookmove=FALSE;
                            i--;
                            break;
                        }
                    }
                    if(i==y && (chesspiecescolor[i][x]==_B || chesspiecescolor[i][x]==0))
                        rookmove=TRUE;
                    switch(rookmove)
                    {
                    case TRUE:
                        chesspieces[y][x]=ROOK;
                        chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                        chesspiecescolor[y][x]=_W;
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                        ispiecepick=FALSE;
                        playerturn=_B;
                        printchessboard();
                        break;
                    case FALSE:
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                        ispiecepick=FALSE;
                        printchessboard();
                        break;
                    }
                }
                else if(y < pickedpiece.Y)
                {
                    for(i=pickedpiece.Y - 1;i>y;i--)
                    {
                        if(chesspieces[i][x]!=0)
                        {
                            rookmove=FALSE;
                            i++;
                            break;
                        }
                    }
                    if(i==y && (chesspiecescolor[i][x]==_B || chesspiecescolor[i][x]==0))
                        rookmove=TRUE;
                    switch(rookmove)
                    {
                    case TRUE:
                        chesspieces[y][x]=ROOK;
                        chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                        chesspiecescolor[y][x]=_W;
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                        ispiecepick=FALSE;
                        playerturn=_B;
                        printchessboard();
                        break;
                    case FALSE:
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                        ispiecepick=FALSE;
                        printchessboard();
                        break;
                    }
                }
                else
                {
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                    ispiecepick=FALSE;
                    printchessboard();
                }
            }
            else
            {
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                ispiecepick=FALSE;
                printchessboard();
            }
            break;
        case BISHOP: //bishop's moves
            if(x>pickedpiece.X && y>pickedpiece.Y)
            {
                j=pickedpiece.Y + 1;
                for(i=pickedpiece.X + 1;i<x;i++)
                {
                    if(chesspieces[j][i]!=0)
                    {
                        bishopmove=FALSE;
                        i--;
                        j--;
                        break;
                    }
                    j++;
                }
                if(i==x && j==y && (chesspieces[y][x]==0 || chesspiecescolor[y][x]==_B))
                    bishopmove=TRUE;
                switch(bishopmove)
                {
                case TRUE:
                    chesspieces[y][x]=BISHOP;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_W;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_B;
                    printchessboard();
                    break;
                case FALSE:
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                    ispiecepick=FALSE;
                    printchessboard();
                    break;
                }
            }
            else if(x<pickedpiece.X && y<pickedpiece.Y)
            {
                j=pickedpiece.Y - 1;
                for(i=pickedpiece.X - 1;i>x;i--)
                {
                    if(chesspieces[j][i]!=0)
                    {
                        bishopmove=FALSE;
                        i++;
                        j++;
                        break;
                    }
                    j--;
                }
                if(i==x && j==y && (chesspieces[y][x]==0 || chesspiecescolor[y][x]==_B))
                    bishopmove=TRUE;
                switch(bishopmove)
                {
                case TRUE:
                    chesspieces[y][x]=BISHOP;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_W;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_B;
                    printchessboard();
                    break;
                case FALSE:
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                    ispiecepick=FALSE;
                    printchessboard();
                    break;
                }
            }
            else if(x<pickedpiece.X && y>pickedpiece.Y)
            {
                j=pickedpiece.Y + 1;
                for(i=pickedpiece.X - 1;i>x;i--)
                {
                    if(chesspieces[j][i]!=0)
                    {
                        bishopmove=FALSE;
                        i++;
                        j--;
                        break;
                    }
                    j++;
                }
                if(i==x && j==y && (chesspieces[y][x]==0 || chesspiecescolor[y][x]==_B))
                    bishopmove=TRUE;
                switch(bishopmove)
                {
                case TRUE:
                    chesspieces[y][x]=BISHOP;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_W;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_B;
                    printchessboard();
                    break;
                case FALSE:
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                    ispiecepick=FALSE;
                    printchessboard();
                    break;
                }
            }
            else if(x>pickedpiece.X && y<pickedpiece.Y)
            {
                j=pickedpiece.Y - 1;
                for(i=pickedpiece.X + 1;i<x;i++)
                {
                    if(chesspieces[j][i]!=0)
                    {
                        bishopmove=FALSE;
                        i--;
                        j++;
                        break;
                    }
                    j--;
                }
                if(i==x && j==y && (chesspieces[y][x]==0 || chesspiecescolor[y][x]==_B))
                    bishopmove=TRUE;
                switch(bishopmove)
                {
                case TRUE:
                    chesspieces[y][x]=BISHOP;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_W;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_B;
                    printchessboard();
                    break;
                case FALSE:
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                    ispiecepick=FALSE;
                    printchessboard();
                    break;
                }
            }
            else
            {
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                ispiecepick=FALSE;
                printchessboard();
            }
            break;
        case QUEEN: //Queen's moves
            if(y==pickedpiece.Y)
            {
                if(x > pickedpiece.X)
                {
                    for(i=pickedpiece.X + 1;i<x;i++)
                    {
                        if(chesspieces[y][i]!=0)
                        {
                            queenmove=FALSE;
                            i--;
                            break;
                        }
                    }
                    if(i==x && (chesspiecescolor[y][i]==_B || chesspiecescolor[y][i]==0))
                        queenmove=TRUE;
                    switch(queenmove)
                    {
                    case TRUE:
                        chesspieces[y][x]=QUEEN;
                        chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                        chesspiecescolor[y][x]=_W;
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                        ispiecepick=FALSE;
                        playerturn=_B;
                        printchessboard();
                        break;
                    case FALSE:
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                        ispiecepick=FALSE;
                        printchessboard();
                        break;
                    }
                }
                else if(x < pickedpiece.X)
                {
                    for(i=pickedpiece.X - 1;i>x;i--)
                    {
                        if(chesspieces[y][i]!=0)
                        {
                            queenmove=FALSE;
                            i++;
                            break;
                        }
                    }
                    if(i==x && (chesspiecescolor[y][i]==_B || chesspiecescolor[y][i]==0))
                        queenmove=TRUE;
                    switch(queenmove)
                    {
                    case TRUE:
                        chesspieces[y][x]=QUEEN;
                        chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                        chesspiecescolor[y][x]=_W;
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                        ispiecepick=FALSE;
                        playerturn=_B;
                        printchessboard();
                        break;
                    case FALSE:
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                        ispiecepick=FALSE;
                        printchessboard();
                        break;
                    }
                }
                else
                {
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                    ispiecepick=FALSE;
                    printchessboard();
                }
            }
            else if(x==pickedpiece.X)
            {
                if(y > pickedpiece.Y)
                {
                    for(i=pickedpiece.Y + 1;i<y;i++)
                    {
                        if(chesspieces[i][x]!=0)
                        {
                            queenmove=FALSE;
                            i--;
                            break;
                        }
                    }
                    if(i==y && (chesspiecescolor[i][x]==_B || chesspiecescolor[i][x]==0))
                        queenmove=TRUE;
                    switch(queenmove)
                    {
                    case TRUE:
                        chesspieces[y][x]=QUEEN;
                        chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                        chesspiecescolor[y][x]=_W;
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                        ispiecepick=FALSE;
                        playerturn=_B;
                        printchessboard();
                        break;
                    case FALSE:
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                        ispiecepick=FALSE;
                        printchessboard();
                        break;
                    }
                }
                else if(y < pickedpiece.Y)
                {
                    for(i=pickedpiece.Y - 1;i>y;i--)
                    {
                        if(chesspieces[i][x]!=0)
                        {
                            queenmove=FALSE;
                            i++;
                            break;
                        }
                    }
                    if(i==y && (chesspiecescolor[i][x]==_B || chesspiecescolor[i][x]==0))
                        queenmove=TRUE;
                    switch(queenmove)
                    {
                    case TRUE:
                        chesspieces[y][x]=QUEEN;
                        chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                        chesspiecescolor[y][x]=_W;
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                        ispiecepick=FALSE;
                        playerturn=_B;
                        printchessboard();
                        break;
                    case FALSE:
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                        ispiecepick=FALSE;
                        printchessboard();
                        break;
                    }
                }
                else
                {
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                    ispiecepick=FALSE;
                    printchessboard();
                }
            }
            else if(x>pickedpiece.X && y>pickedpiece.Y)
            {
                j=pickedpiece.Y + 1;
                for(i=pickedpiece.X + 1;i<x;i++)
                {
                    if(chesspieces[j][i]!=0)
                    {
                        queenmove=FALSE;
                        i--;
                        j--;
                        break;
                    }
                    j++;
                }
                if(i==x && j==y && (chesspieces[y][x]==0 || chesspiecescolor[y][x]==_B))
                    queenmove=TRUE;
                switch(queenmove)
                {
                case TRUE:
                    chesspieces[y][x]=QUEEN;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_W;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_B;
                    printchessboard();
                    break;
                case FALSE:
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                    ispiecepick=FALSE;
                    printchessboard();
                    break;
                }
            }
            else if(x<pickedpiece.X && y<pickedpiece.Y)
            {
                j=pickedpiece.Y - 1;
                for(i=pickedpiece.X - 1;i>x;i--)
                {
                    if(chesspieces[j][i]!=0)
                    {
                        queenmove=FALSE;
                        i++;
                        j++;
                        break;
                    }
                    j--;
                }
                if(i==x && j==y && (chesspieces[y][x]==0 || chesspiecescolor[y][x]==_B))
                    queenmove=TRUE;
                switch(queenmove)
                {
                case TRUE:
                    chesspieces[y][x]=QUEEN;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_W;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_B;
                    printchessboard();
                    break;
                case FALSE:
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                    ispiecepick=FALSE;
                    printchessboard();
                    break;
                }
            }
            else if(x<pickedpiece.X && y>pickedpiece.Y)
            {
                j=pickedpiece.Y + 1;
                for(i=pickedpiece.X - 1;i>x;i--)
                {
                    if(chesspieces[j][i]!=0)
                    {
                        queenmove=FALSE;
                        i++;
                        j--;
                        break;
                    }
                    j++;
                }
                if(i==x && j==y && (chesspieces[y][x]==0 || chesspiecescolor[y][x]==_B))
                    queenmove=TRUE;
                switch(queenmove)
                {
                case TRUE:
                    chesspieces[y][x]=QUEEN;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_W;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_B;
                    printchessboard();
                    break;
                case FALSE:
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                    ispiecepick=FALSE;
                    printchessboard();
                    break;
                }
            }
            else if(x>pickedpiece.X && y<pickedpiece.Y)
            {
                j=pickedpiece.Y - 1;
                for(i=pickedpiece.X + 1;i<x;i++)
                {
                    if(chesspieces[j][i]!=0)
                    {
                        queenmove=FALSE;
                        i--;
                        j++;
                        break;
                    }
                    j--;
                }
                if(i==x && j==y && (chesspieces[y][x]==0 || chesspiecescolor[y][x]==_B))
                    queenmove=TRUE;
                switch(queenmove)
                {
                case TRUE:
                    chesspieces[y][x]=QUEEN;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_W;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_B;
                    printchessboard();
                    break;
                case FALSE:
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                    ispiecepick=FALSE;
                    printchessboard();
                    break;
                }
            }
            else
            {
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_W;
                ispiecepick=FALSE;
                printchessboard();
            }
            break;
        }
    }


    else //black's turn
    {
        switch(chesspieces[pickedpiece.Y][pickedpiece.X])
        {
        case PAWN: //pawn's moves
            if(chesspieces[pickedpiece.Y + 1][pickedpiece.X]==0 && x==pickedpiece.X && y==pickedpiece.Y + 1)
            {
                if(y==7)
                {
                    pawnpromotion(x,y);
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_B;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_W;
                }
                else
                {
                    chesspieces[y][x]=PAWN;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_B;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_W;
                }
                printchessboard();
            }
            else if(chesspiecescolor[pickedpiece.Y + 1][pickedpiece.X - 1]==_W && x==pickedpiece.X - 1 && y==pickedpiece.Y + 1)
            {
                chesspieces[y][x]=PAWN;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else if(chesspiecescolor[pickedpiece.Y + 1][pickedpiece.X + 1]==_W && x==pickedpiece.X + 1 && y==pickedpiece.Y + 1)
            {
                chesspieces[y][x]=PAWN;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else if(chesspieces[pickedpiece.Y + 2][pickedpiece.X]==0 && pickedpiece.Y==1 && x==pickedpiece.X && y==pickedpiece.Y + 2)
            {
                chesspieces[y][x]=PAWN;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else
            {
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                ispiecepick=FALSE;
                printchessboard();
            }
            break;
        case KING: //king's moves
            if((chesspieces[pickedpiece.Y - 1][pickedpiece.X]==0 || chesspiecescolor[pickedpiece.Y - 1][pickedpiece.X]==_W) && x==pickedpiece.X && y==pickedpiece.Y - 1)
            {
                if(hasBkingmoved==FALSE)
                    hasBkingmoved=TRUE;
                chesspieces[y][x]=KING;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y + 1][pickedpiece.X]==0 || chesspiecescolor[pickedpiece.Y + 1][pickedpiece.X]==_W) && x==pickedpiece.X && y==pickedpiece.Y + 1)
            {
                if(hasBkingmoved==FALSE)
                    hasBkingmoved=TRUE;
                chesspieces[y][x]=KING;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y][pickedpiece.X + 1]==0 || chesspiecescolor[pickedpiece.Y][pickedpiece.X + 1]==_W) && x==pickedpiece.X + 1 && y==pickedpiece.Y)
            {
                if(hasBkingmoved==FALSE)
                    hasBkingmoved=TRUE;
                chesspieces[y][x]=KING;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y][pickedpiece.X - 1]==0 || chesspiecescolor[pickedpiece.Y][pickedpiece.X - 1]==_W) && x==pickedpiece.X - 1 && y==pickedpiece.Y)
            {
                if(hasBkingmoved==FALSE)
                    hasBkingmoved=TRUE;
                chesspieces[y][x]=KING;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y + 1][pickedpiece.X + 1]==0 || chesspiecescolor[pickedpiece.Y + 1][pickedpiece.X + 1]==_W) && x==pickedpiece.X + 1 && y==pickedpiece.Y + 1)
            {
                if(hasBkingmoved==FALSE)
                    hasBkingmoved=TRUE;
                chesspieces[y][x]=KING;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y + 1][pickedpiece.X - 1]==0 || chesspiecescolor[pickedpiece.Y + 1][pickedpiece.X - 1]==_W) && x==pickedpiece.X - 1 && y==pickedpiece.Y + 1)
            {
                if(hasBkingmoved==FALSE)
                    hasBkingmoved=TRUE;
                chesspieces[y][x]=KING;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y - 1][pickedpiece.X - 1]==0 || chesspiecescolor[pickedpiece.Y - 1][pickedpiece.X - 1]==_W) && x==pickedpiece.X - 1 && y==pickedpiece.Y - 1)
            {
                if(hasBkingmoved==FALSE)
                    hasBkingmoved=TRUE;
                chesspieces[y][x]=KING;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y - 1][pickedpiece.X + 1]==0 || chesspiecescolor[pickedpiece.Y - 1][pickedpiece.X + 1]==_W) && x==pickedpiece.X + 1 && y==pickedpiece.Y - 1)
            {
                if(hasBkingmoved==FALSE)
                    hasBkingmoved=TRUE;
                chesspieces[y][x]=KING;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else
            {
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                ispiecepick=FALSE;
                printchessboard();
            }
            break;
        case KNIGHT: //Knight's moves
            if((chesspieces[pickedpiece.Y - 2][pickedpiece.X - 1]==0 || chesspiecescolor[pickedpiece.Y - 2][pickedpiece.X - 1]==_W) && x==pickedpiece.X - 1 && y==pickedpiece.Y - 2)
            {
                chesspieces[y][x]=KNIGHT;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y - 2][pickedpiece.X + 1]==0 || chesspiecescolor[pickedpiece.Y - 2][pickedpiece.X + 1]==_W) && x==pickedpiece.X + 1 && y==pickedpiece.Y - 2)
            {
                chesspieces[y][x]=KNIGHT;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y - 1][pickedpiece.X - 2]==0 || chesspiecescolor[pickedpiece.Y - 1][pickedpiece.X - 2]==_W) && x==pickedpiece.X - 2 && y==pickedpiece.Y - 1)
            {
                chesspieces[y][x]=KNIGHT;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y - 1][pickedpiece.X + 2]==0 || chesspiecescolor[pickedpiece.Y - 1][pickedpiece.X + 2]==_W) && x==pickedpiece.X + 2 && y==pickedpiece.Y - 1)
            {
                chesspieces[y][x]=KNIGHT;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y + 1][pickedpiece.X + 2]==0 || chesspiecescolor[pickedpiece.Y + 1][pickedpiece.X + 2]==_W) && x==pickedpiece.X + 2 && y==pickedpiece.Y + 1)
            {
                chesspieces[y][x]=KNIGHT;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y + 1][pickedpiece.X - 2]==0 || chesspiecescolor[pickedpiece.Y + 1][pickedpiece.X - 2]==_W) && x==pickedpiece.X - 2 && y==pickedpiece.Y + 1)
            {
                chesspieces[y][x]=KNIGHT;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y + 2][pickedpiece.X - 1]==0 || chesspiecescolor[pickedpiece.Y + 2][pickedpiece.X - 1]==_W) && x==pickedpiece.X - 1 && y==pickedpiece.Y + 2)
            {
                chesspieces[y][x]=KNIGHT;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else if((chesspieces[pickedpiece.Y + 2][pickedpiece.X + 1]==0 || chesspiecescolor[pickedpiece.Y + 2][pickedpiece.X + 1]==_W) && x==pickedpiece.X + 1 && y==pickedpiece.Y + 2)
            {
                chesspieces[y][x]=KNIGHT;
                chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                chesspiecescolor[y][x]=_B;
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                ispiecepick=FALSE;
                playerturn=_W;
                printchessboard();
            }
            else
            {
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                ispiecepick=FALSE;
                printchessboard();
            }
            break;
        case ROOK: //rook's moves
            if(y==pickedpiece.Y)
            {
                if(x > pickedpiece.X)
                {
                    for(i=pickedpiece.X + 1;i<x;i++)
                    {
                        if(chesspieces[y][i]!=0)
                        {
                            rookmove=FALSE;
                            i--;
                            break;
                        }
                    }
                    if(i==x && (chesspiecescolor[y][i]==_W || chesspiecescolor[y][i]==0))
                        rookmove=TRUE;
                    switch(rookmove)
                    {
                    case TRUE:
                        chesspieces[y][x]=ROOK;
                        chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                        chesspiecescolor[y][x]=_B;
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                        ispiecepick=FALSE;
                        playerturn=_W;
                        printchessboard();
                        break;
                    case FALSE:
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                        ispiecepick=FALSE;
                        printchessboard();
                        break;
                    }
                }
                else if(x < pickedpiece.X)
                {
                    for(i=pickedpiece.X - 1;i>x;i--)
                    {
                        if(chesspieces[y][i]!=0)
                        {
                            rookmove=FALSE;
                            i++;
                            break;
                        }
                    }
                    if(i==x && (chesspiecescolor[y][i]==_W || chesspiecescolor[y][i]==0))
                        rookmove=TRUE;
                    switch(rookmove)
                    {
                    case TRUE:
                        chesspieces[y][x]=ROOK;
                        chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                        chesspiecescolor[y][x]=_B;
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                        ispiecepick=FALSE;
                        playerturn=_W;
                        printchessboard();
                        break;
                    case FALSE:
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                        ispiecepick=FALSE;
                        printchessboard();
                        break;
                    }
                }
                else
                {
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                    ispiecepick=FALSE;
                    printchessboard();
                }
            }
            else if(x==pickedpiece.X)
            {
                if(y > pickedpiece.Y)
                {
                    for(i=pickedpiece.Y + 1;i<y;i++)
                    {
                        if(chesspieces[i][x]!=0)
                        {
                            rookmove=FALSE;
                            i--;
                            break;
                        }
                    }
                    if(i==y && (chesspiecescolor[i][x]==_W || chesspiecescolor[i][x]==0))
                        rookmove=TRUE;
                    switch(rookmove)
                    {
                    case TRUE:
                        chesspieces[y][x]=ROOK;
                        chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                        chesspiecescolor[y][x]=_B;
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                        ispiecepick=FALSE;
                        playerturn=_W;
                        printchessboard();
                        break;
                    case FALSE:
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                        ispiecepick=FALSE;
                        printchessboard();
                        break;
                    }
                }
                else if(y < pickedpiece.Y)
                {
                    for(i=pickedpiece.Y - 1;i>y;i--)
                    {
                        if(chesspieces[i][x]!=0)
                        {
                            rookmove=FALSE;
                            i++;
                            break;
                        }
                    }
                    if(i==y && (chesspiecescolor[i][x]==_W || chesspiecescolor[i][x]==0))
                        rookmove=TRUE;
                    switch(rookmove)
                    {
                    case TRUE:
                        chesspieces[y][x]=ROOK;
                        chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                        chesspiecescolor[y][x]=_B;
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                        ispiecepick=FALSE;
                        playerturn=_W;
                        printchessboard();
                        break;
                    case FALSE:
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                        ispiecepick=FALSE;
                        printchessboard();
                        break;
                    }
                }
                else
                {
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                    ispiecepick=FALSE;
                    printchessboard();
                }
            }
            else
            {
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                ispiecepick=FALSE;
                printchessboard();
            }
            break;
        case BISHOP: //bishop's moves
            if(x>pickedpiece.X && y>pickedpiece.Y)
            {
                j=pickedpiece.Y + 1;
                for(i=pickedpiece.X + 1;i<x;i++)
                {
                    if(chesspieces[j][i]!=0)
                    {
                        bishopmove=FALSE;
                        i--;
                        j--;
                        break;
                    }
                    j++;
                }
                if(i==x && j==y && (chesspieces[y][x]==0 || chesspiecescolor[y][x]==_W))
                    bishopmove=TRUE;
                switch(bishopmove)
                {
                case TRUE:
                    chesspieces[y][x]=BISHOP;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_B;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_W;
                    printchessboard();
                    break;
                case FALSE:
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                    ispiecepick=FALSE;
                    printchessboard();
                    break;
                }
            }
            else if(x<pickedpiece.X && y<pickedpiece.Y)
            {
                j=pickedpiece.Y - 1;
                for(i=pickedpiece.X - 1;i>x;i--)
                {
                    if(chesspieces[j][i]!=0)
                    {
                        bishopmove=FALSE;
                        i++;
                        j++;
                        break;
                    }
                    j--;
                }
                if(i==x && j==y && (chesspieces[y][x]==0 || chesspiecescolor[y][x]==_W))
                    bishopmove=TRUE;
                switch(bishopmove)
                {
                case TRUE:
                    chesspieces[y][x]=BISHOP;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_B;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_W;
                    printchessboard();
                    break;
                case FALSE:
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                    ispiecepick=FALSE;
                    printchessboard();
                    break;
                }
            }
            else if(x<pickedpiece.X && y>pickedpiece.Y)
            {
                j=pickedpiece.Y + 1;
                for(i=pickedpiece.X - 1;i>x;i--)
                {
                    if(chesspieces[j][i]!=0)
                    {
                        bishopmove=FALSE;
                        i++;
                        j--;
                        break;
                    }
                    j++;
                }
                if(i==x && j==y && (chesspieces[y][x]==0 || chesspiecescolor[y][x]==_W))
                    bishopmove=TRUE;
                switch(bishopmove)
                {
                case TRUE:
                    chesspieces[y][x]=BISHOP;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_B;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_W;
                    printchessboard();
                    break;
                case FALSE:
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                    ispiecepick=FALSE;
                    printchessboard();
                    break;
                }
            }
            else if(x>pickedpiece.X && y<pickedpiece.Y)
            {
                j=pickedpiece.Y - 1;
                for(i=pickedpiece.X + 1;i<x;i++)
                {
                    if(chesspieces[j][i]!=0)
                    {
                        bishopmove=FALSE;
                        i--;
                        j++;
                        break;
                    }
                    j--;
                }
                if(i==x && j==y && (chesspieces[y][x]==0 || chesspiecescolor[y][x]==_W))
                    bishopmove=TRUE;
                switch(bishopmove)
                {
                case TRUE:
                    chesspieces[y][x]=BISHOP;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_B;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_W;
                    printchessboard();
                    break;
                case FALSE:
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                    ispiecepick=FALSE;
                    printchessboard();
                    break;
                }
            }
            else
            {
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                ispiecepick=FALSE;
                printchessboard();
            }
            break;
        case QUEEN: //Queen's moves
            if(y==pickedpiece.Y)
            {
                if(x > pickedpiece.X)
                {
                    for(i=pickedpiece.X + 1;i<x;i++)
                    {
                        if(chesspieces[y][i]!=0)
                        {
                            queenmove=FALSE;
                            i--;
                            break;
                        }
                    }
                    if(i==x && (chesspiecescolor[y][i]==_W || chesspiecescolor[y][i]==0))
                        queenmove=TRUE;
                    switch(queenmove)
                    {
                    case TRUE:
                        chesspieces[y][x]=QUEEN;
                        chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                        chesspiecescolor[y][x]=_B;
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                        ispiecepick=FALSE;
                        playerturn=_W;
                        printchessboard();
                        break;
                    case FALSE:
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                        ispiecepick=FALSE;
                        printchessboard();
                        break;
                    }
                }
                else if(x < pickedpiece.X)
                {
                    for(i=pickedpiece.X - 1;i>x;i--)
                    {
                        if(chesspieces[y][i]!=0)
                        {
                            queenmove=FALSE;
                            i++;
                            break;
                        }
                    }
                    if(i==x && (chesspiecescolor[y][i]==_W || chesspiecescolor[y][i]==0))
                        queenmove=TRUE;
                    switch(queenmove)
                    {
                    case TRUE:
                        chesspieces[y][x]=QUEEN;
                        chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                        chesspiecescolor[y][x]=_B;
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                        ispiecepick=FALSE;
                        playerturn=_W;
                        printchessboard();
                        break;
                    case FALSE:
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                        ispiecepick=FALSE;
                        printchessboard();
                        break;
                    }
                }
                else
                {
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                    ispiecepick=FALSE;
                    printchessboard();
                }
            }
            else if(x==pickedpiece.X)
            {
                if(y > pickedpiece.Y)
                {
                    for(i=pickedpiece.Y + 1;i<y;i++)
                    {
                        if(chesspieces[i][x]!=0)
                        {
                            queenmove=FALSE;
                            i--;
                            break;
                        }
                    }
                    if(i==y && (chesspiecescolor[i][x]==_W || chesspiecescolor[i][x]==0))
                        queenmove=TRUE;
                    switch(queenmove)
                    {
                    case TRUE:
                        chesspieces[y][x]=QUEEN;
                        chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                        chesspiecescolor[y][x]=_B;
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                        ispiecepick=FALSE;
                        playerturn=_W;
                        printchessboard();
                        break;
                    case FALSE:
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                        ispiecepick=FALSE;
                        printchessboard();
                        break;
                    }
                }
                else if(y < pickedpiece.Y)
                {
                    for(i=pickedpiece.Y - 1;i>y;i--)
                    {
                        if(chesspieces[i][x]!=0)
                        {
                            queenmove=FALSE;
                            i++;
                            break;
                        }
                    }
                    if(i==y && (chesspiecescolor[i][x]==_W || chesspiecescolor[i][x]==0))
                        queenmove=TRUE;
                    switch(queenmove)
                    {
                    case TRUE:
                        chesspieces[y][x]=QUEEN;
                        chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                        chesspiecescolor[y][x]=_B;
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                        ispiecepick=FALSE;
                        playerturn=_W;
                        printchessboard();
                        break;
                    case FALSE:
                        chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                        ispiecepick=FALSE;
                        printchessboard();
                        break;
                    }
                }
                else
                {
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                    ispiecepick=FALSE;
                    printchessboard();
                }
            }
            else if(x>pickedpiece.X && y>pickedpiece.Y)
            {
                j=pickedpiece.Y + 1;
                for(i=pickedpiece.X + 1;i<x;i++)
                {
                    if(chesspieces[j][i]!=0)
                    {
                        queenmove=FALSE;
                        i--;
                        j--;
                        break;
                    }
                    j++;
                }
                if(i==x && j==y && (chesspieces[y][x]==0 || chesspiecescolor[y][x]==_W))
                    queenmove=TRUE;
                switch(queenmove)
                {
                case TRUE:
                    chesspieces[y][x]=QUEEN;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_B;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_W;
                    printchessboard();
                    break;
                case FALSE:
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                    ispiecepick=FALSE;
                    printchessboard();
                    break;
                }
            }
            else if(x<pickedpiece.X && y<pickedpiece.Y)
            {
                j=pickedpiece.Y - 1;
                for(i=pickedpiece.X - 1;i>x;i--)
                {
                    if(chesspieces[j][i]!=0)
                    {
                        queenmove=FALSE;
                        i++;
                        j++;
                        break;
                    }
                    j--;
                }
                if(i==x && j==y && (chesspieces[y][x]==0 || chesspiecescolor[y][x]==_W))
                    queenmove=TRUE;
                switch(queenmove)
                {
                case TRUE:
                    chesspieces[y][x]=QUEEN;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_B;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_W;
                    printchessboard();
                    break;
                case FALSE:
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                    ispiecepick=FALSE;
                    printchessboard();
                    break;
                }
            }
            else if(x<pickedpiece.X && y>pickedpiece.Y)
            {
                j=pickedpiece.Y + 1;
                for(i=pickedpiece.X - 1;i>x;i--)
                {
                    if(chesspieces[j][i]!=0)
                    {
                        queenmove=FALSE;
                        i++;
                        j--;
                        break;
                    }
                    j++;
                }
                if(i==x && j==y && (chesspieces[y][x]==0 || chesspiecescolor[y][x]==_W))
                    queenmove=TRUE;
                switch(queenmove)
                {
                case TRUE:
                    chesspieces[y][x]=QUEEN;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_B;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_W;
                    printchessboard();
                    break;
                case FALSE:
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                    ispiecepick=FALSE;
                    printchessboard();
                    break;
                }
            }
            else if(x>pickedpiece.X && y<pickedpiece.Y)
            {
                j=pickedpiece.Y - 1;
                for(i=pickedpiece.X + 1;i<x;i++)
                {
                    if(chesspieces[j][i]!=0)
                    {
                        queenmove=FALSE;
                        i--;
                        j++;
                        break;
                    }
                    j--;
                }
                if(i==x && j==y && (chesspieces[y][x]==0 || chesspiecescolor[y][x]==_W))
                    queenmove=TRUE;
                switch(queenmove)
                {
                case TRUE:
                    chesspieces[y][x]=QUEEN;
                    chesspieces[pickedpiece.Y][pickedpiece.X]=0;
                    chesspiecescolor[y][x]=_B;
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=0;
                    ispiecepick=FALSE;
                    playerturn=_W;
                    printchessboard();
                    break;
                case FALSE:
                    chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                    ispiecepick=FALSE;
                    printchessboard();
                    break;
                }
            }
            else
            {
                chesspiecescolor[pickedpiece.Y][pickedpiece.X]=_B;
                ispiecepick=FALSE;
                printchessboard();
            }
            break;
        }
    }
}
//
void printsign() //prints my signature
{
    COORD signpos={50,23};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),signpos);
    printf("Written By: Shivam Shekhar");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),zerozero);
}
//
void printbuttons() //prints menu buttons
{
    buttonpos.X=30;
    buttonpos.Y=2;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),143);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),buttonpos);
    printf("save");
    buttonpos.X=38;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),buttonpos);
    printf("load");
    buttonpos.X=46;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),buttonpos);
    printf("reset");
    buttonpos.X=55;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),buttonpos);
    printf("help");
    buttonpos.X=0;
    buttonpos.Y=0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),buttonpos);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
//
void reset() //resets the game
{
    system("cls");
    system("Chess.exe");
}
//
void save() //save the game
{
    FILE *savefile;
    char filename[100];
    system("cls");
    printf("Enter the name of the file(without spaces): ");
    scanf("%s", &filename);
    strcat(filename,".sav");
    savefile=fopen(filename,"wb");
    fwrite(chesspieces,sizeof(int),64,savefile);
    fwrite(chesspiecescolor,sizeof(int),64,savefile);
    ispiecepick=FALSE;
    fwrite(&ispiecepick,sizeof(int),1,savefile);
    fwrite(&playerturn,sizeof(int),1,savefile);
    fwrite(&hasWkingmoved,sizeof(int),1,savefile);
    fwrite(&hasBkingmoved,sizeof(int),1,savefile);
    fclose(savefile);
    printf("\n\nFile saved successfully! ");
    system("pause");
}
//
void load() //loads the game
{
    FILE *savefile;
    char filename[100];
    system("cls");
    system("dir *.sav");
    printf("Filename of file to be opened: ");
    scanf("%s",filename);
    strcat(filename,".sav");
    savefile=fopen(filename,"rb");
    if(savefile==NULL)
    {
        system("cls");
        printf("File not found. Make sure your file is in the current working directory\n");
        system("pause");
    }
    else
    {
        fread(chesspieces,sizeof(int),64,savefile);
        fread(chesspiecescolor,sizeof(int),64,savefile);
        fread(&ispiecepick,sizeof(int),1,savefile);
        fread(&playerturn,sizeof(int),1,savefile);
        fread(&hasWkingmoved,sizeof(int),1,savefile);
        fread(&hasBkingmoved,sizeof(int),1,savefile);
    }
    fclose(savefile);
}
//
void help() //prints help
{
    system("cls");
    printf("Welcome to the game of Neon chess\n\n");
    printf("This is a basic chess game which can be played by two players. P1(yellow) and P2(green)\n\n");
    printf("The rules of the chess remains same. The player who defeats the other's king, wins!\n\n");
    printf("Use your mouse to pick a piece and move it to its desired location\n\n");
    printf("You can also save your file for future play or load a previously saved file\n\n");
    printf("There are 6 pieces in the game. They are:\n");
    printf("Pawn: %c\nRook: %c\nBishop: %c\nKnight: %c\nQueen: %c\nKing: %c\n\n",24,4,235,5,12,11);
    system("pause");
}
//
int checkwin() //checks whether either player has won
{
    int i,j,wkalive=0,bkalive=0;
    COORD textpos={35,21};
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            if(chesspieces[i][j]==KING && (chesspiecescolor[i][j]==_B || chesspiecescolor[i][j]==HIGHLIGHTB))
                bkalive=1;
            if(chesspieces[i][j]==KING && (chesspiecescolor[i][j]==_W || chesspiecescolor[i][j]==HIGHLIGHTW))
                wkalive=1;
        }
    }
    if(bkalive==0)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
            printf("checkmate!");
        textpos.Y++;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
            printf("P1 wins!");
        return 1;
    }
    else if(wkalive==0)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
            printf("checkmate!");
        textpos.Y++;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
            printf("P2 wins!");
        return 1;
    }
    else return 0;
}
//
void pawnpromotion(int x, int y) //promotes a pawn
{
    int i;
    COORD textpos={5,5},clearsz={20,10};
    INPUT_RECORD input;
    DWORD info;
    SMALL_RECT clearrect={4,4,24,14};
    CHAR_INFO clearscr[200];
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
    printf("Promote pawn to:");
    textpos.Y+=2;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),143);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
    printf("ROOK");
    textpos.Y+=2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
    printf("QUEEN");
    textpos.Y+=2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
    printf("KNIGHT");
    textpos.Y+=2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
    printf("BISHOP");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),zerozero);
    while(1)
    {
        SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),ENABLE_MOUSE_INPUT);
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE),&input,1,&info);
        if(input.EventType==MOUSE_EVENT)
        {
            if(input.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                if(input.Event.MouseEvent.dwMousePosition.X>4 && input.Event.MouseEvent.dwMousePosition.X<9 && input.Event.MouseEvent.dwMousePosition.Y==7)
                {
                    chesspieces[y][x]=ROOK;
                    break;
                }
                else if(input.Event.MouseEvent.dwMousePosition.X>4 && input.Event.MouseEvent.dwMousePosition.X<10 && input.Event.MouseEvent.dwMousePosition.Y==9)
                {
                    chesspieces[y][x]=QUEEN;
                    break;
                }
                else if(input.Event.MouseEvent.dwMousePosition.X>4 && input.Event.MouseEvent.dwMousePosition.X<11 && input.Event.MouseEvent.dwMousePosition.Y==11)
                {
                    chesspieces[y][x]=KNIGHT;
                    break;
                }
                else if(input.Event.MouseEvent.dwMousePosition.X>4 && input.Event.MouseEvent.dwMousePosition.X<11 && input.Event.MouseEvent.dwMousePosition.Y==13)
                {
                    chesspieces[y][x]=BISHOP;
                    break;
                }
            }
        }
    }
    for(i=0;i<200;i++)
    {
        clearscr[i].Char.AsciiChar=' ';
        clearscr[i].Attributes=15;
    }
    WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE),clearscr,clearsz,zerozero,&clearrect);
}
//
int iskingcheck()
{
    int i,j,x,y;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            if(chesspieces[i][j]==KING && chesspiecescolor[i][j]==playerturn)
            {
                y=i;
                x=j;
                i=9;
                break;
            }
        }
    }
    //
   /* for(i=y;i<8;i++)
    {
        if()
    }*/
}
