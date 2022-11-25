#include "./../include/inspection_utilities.h"
#include <fcntl.h>

#define r "/tmp/fifoWI"

int fd_read;

int main(int argc, char const *argv[])
{
    // Utility variable to avoid trigger resize event on launch
    int first_resize = TRUE;

    // End-effector coordinates
    float ee_x, ee_y;

    // Initialize User Interface 
    init_console_ui();

    //aprire pipe WI in lettura
    if((fd_read = open(r, O_RDONLY)) ==0 ) {
            perror("Can't open /tmp/fifoWI");
            exit(-1);
    }

    // Infinite loop
    while(TRUE)
	{	
        // Get mouse/resize commands in non-blocking mode...
        int cmd = getch();

        // If user resizes screen, re-draw UI
        if(cmd == KEY_RESIZE) {
            if(first_resize) {
                first_resize = FALSE;
            }
            else {
                reset_console_ui();
            }
        }
        // Else if mouse has been pressed
        else if(cmd == KEY_MOUSE) {

            // Check which button has been pressed...
            if(getmouse(&event) == OK) {

                // STOP button pressed
                if(check_button_pressed(stp_button, &event)) {
                    mvprintw(LINES - 1, 1, "STP button pressed");
                    refresh();
                    sleep(1);
                    for(int j = 0; j < COLS; j++) {
                        mvaddch(LINES - 1, j, ' ');
                    }
                    //signal to STOP everything send to every proccess
                }

                // RESET button pressed
                else if(check_button_pressed(rst_button, &event)) {
                    mvprintw(LINES - 1, 1, "RST button pressed");
                    refresh();
                    sleep(1);
                    for(int j = 0; j < COLS; j++) {
                        mvaddch(LINES - 1, j, ' ');
                    }
                    //comand console unable to use untill reached the original position
                    //motor X and motor Z V=0 then Vx Vz negative untill reach 0,0

                }
            }
        }
        
        // To be commented in final version...
        /*switch (cmd)
        {
            case KEY_LEFT:
                ee_x--;
                break;
            case KEY_RIGHT:
                ee_x++;
                break;
            case KEY_UP:
                ee_y--;
                break;
            case KEY_DOWN:
                ee_y++;
                break;
            default:
                break;
        }
        
        // Update UI
        update_console_ui(&ee_x, &ee_y);*/
	}

    // Terminate
    endwin();
    return 0;
}
