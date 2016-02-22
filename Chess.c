/*
Neon Chess
Made by: Shivam Shekhar
*/
///Headers and Macros
#include"alphabet2.h"
#include"NChess.h"
///main function
int main()
{
    HANDLE in,out;  //input and output handles
    DWORD info;
    CONSOLE_SCREEN_BUFFER_INFO scrinfo;
    INPUT_RECORD inp;
    COORD pos={25,17};
    int i,j; //loop variables
    SetConsoleTitle("Neon Chess"); //console title
    in=GetStdHandle(STD_INPUT_HANDLE);
    out=GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(out,&scrinfo);
    printstr(14,8,"neon chess",219,_GREEN); //prints the title screen. defined in alphabet2.h
    printsign();
    SetConsoleCursorPosition(out,pos);
    system("pause");
    SetConsoleCursorPosition(out,zerozero);
    initializechessboard(); //initializes chess board
    while(1) //beginning the game
    {
        SetConsoleMode(in,ENABLE_MOUSE_INPUT); //Enables mouse input
        ReadConsoleInput(in,&inp,1,&info); //Reads mouse input
        if(inp.EventType==MOUSE_EVENT) //checks if mouse is used
        {
            if(inp.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED) //checks if user pressed the left mouse button
            {
                if(inp.Event.MouseEvent.dwMousePosition.X<34 && inp.Event.MouseEvent.dwMousePosition.X>29 && inp.Event.MouseEvent.dwMousePosition.Y==2)
                {
                    save(); //saves the game
                    initializechessboard();
                }
                else if(inp.Event.MouseEvent.dwMousePosition.X<42 && inp.Event.MouseEvent.dwMousePosition.X>37 && inp.Event.MouseEvent.dwMousePosition.Y==2)
                {
                    load(); //loads the game
                    initializechessboard();
                }
                else if(inp.Event.MouseEvent.dwMousePosition.X<51 && inp.Event.MouseEvent.dwMousePosition.X>45 && inp.Event.MouseEvent.dwMousePosition.Y==2)
                    reset(); //resets the game
                else if(inp.Event.MouseEvent.dwMousePosition.X<58 && inp.Event.MouseEvent.dwMousePosition.X>54 && inp.Event.MouseEvent.dwMousePosition.Y==2)
                {
                    help(); //prints help
                    initializechessboard();
                }
                else
                {
                    if(ispiecepick==FALSE) //if no piece is picked
                        piecepick(MOUSEPOSX(inp.Event.MouseEvent.dwMousePosition.X),MOUSEPOSY(inp.Event.MouseEvent.dwMousePosition.Y)); //picks a piece
                    else if(ispiecepick==TRUE)
                    {
                        if(MOUSEPOSX(inp.Event.MouseEvent.dwMousePosition.X)>-1 && MOUSEPOSX(inp.Event.MouseEvent.dwMousePosition.X)<8 && MOUSEPOSY(inp.Event.MouseEvent.dwMousePosition.Y)>-1 && MOUSEPOSY(inp.Event.MouseEvent.dwMousePosition.Y)<8)
                            piecemove(MOUSEPOSX(inp.Event.MouseEvent.dwMousePosition.X),MOUSEPOSY(inp.Event.MouseEvent.dwMousePosition.Y)); //moves a picked piece
                    }
                }
            }
        }
        if(checkwin()==1) //checks for winning condition. Breaks if either player wins
            break;
    }
    getch();
    return 0; //end of program
}
