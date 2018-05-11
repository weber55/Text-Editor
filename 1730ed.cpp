#include <unistd.h>
#include <string>
#include <cstdlib>
#include <ncurses.h>
#include <fcntl.h>
#include "Textfile.h"
using namespace std;

void displayContents(Textfile &);
void menuAction(int);
void myOpen();
void mySave();
void mySaveAs();
void myExit();

/**
 * Class for Menu (should probably be moved to different file)
 */
class Menu{
  char const *options[4] = {"Open", "Save", "Save As", "Exit"};

public:

  /**
   * Shows the menu and options and allows selection
   * returns int representing choice that was selected
   */
  int showMenu(){
    WINDOW *menu;
    int selected = 1;
    int ch;
    noecho();
    cbreak();
    int x, y;
    getmaxyx(stdscr, y, x);
    menu = newwin(10, 40, y/2-5, x/2-20);
    keypad(menu, TRUE);
    updateMenu(menu, selected);
    curs_set(0);
    while ((ch = wgetch(menu)) != KEY_F(1)){
      switch(ch){
      case KEY_UP:
	selected--;
	if (selected < 1 ) selected = 4;
	updateMenu(menu, selected);
	break;
      case KEY_DOWN:
	selected++;
	if(selected > 4) selected = 1;
	updateMenu(menu, selected);
	break;
      case 10: // ENTER key
	switch (selected){
	case 1: // open
	  return 1;
	  break;
	case 2: // save
	  return 2;
	  break;
	case 3: // save as
	  return 3;
	  break;
	case 4: // exit
	  return 4;
	  break;
	}
      }
    }
    return 0;
  } //showMenu

    /**
     * Highlights the choice that is selected
     */
  void updateMenu(WINDOW *menu, int selected){
    int x = 5;
    int y = 4;
    box(menu, 0, 0);
    mvwprintw(menu, 2, 4, "%s", "MENU:");
    for(int i = 0; i < 4; i++){
      if(selected == i + 1){
	wattron(menu, A_REVERSE);
	mvwprintw(menu, y, x, "%s", options[i]);
	wattroff(menu, A_REVERSE);
      }
      else{
	mvwprintw(menu, y, x, "%s", options[i]);
      }
      y++;
    }
    wrefresh(menu);
  } //updateMenu

}; // Menu class


/**
 * Entry point of program. Takes a file name given by user and
 * displays its contents in a window if the file exists.
 */
int main(int argc, const char** argv){
  initscr();
  keypad(stdscr, TRUE);
  scrollok(stdscr, TRUE);
  if (argc == 2){
    Textfile myFile(argv[1]);
    if (myFile.isAvailable()){
      displayContents(myFile);
      Menu menu;
      menuAction(menu.showMenu());
    }
    else endwin();
  }
  return EXIT_SUCCESS;
}

void menuAction(int choice){
  switch(choice){
  case 1:
    myOpen();
    break;
  case 2:
    mySave();
    break;
  case 3:
    mySaveAs();
    break;
  case 4:
    myExit();
    break;
  }
}

/**
 * Prompts user to type in a file name to open
 */
void myOpen(){
  int x, y;
  getmaxyx(stdscr, y, x);
  WINDOW *prompt;
  prompt = newwin(10, 40, y/2-5, x/2-20);
  box(prompt, 0, 0);
  keypad(prompt, TRUE);
  mvwprintw(prompt, 2, 2, "%s", "OPEN");
  mvwprintw(prompt, 3, 2, "%s", "Enter a file name:");
  mvwprintw(prompt, 4, 2, "%s", "");
  wrefresh(prompt);
  echo();
  char input[80];
  wgetstr(prompt, input);
  noecho();
  Textfile opened(input);
  if (opened.isAvailable()){
    displayContents(opened);
    Menu menu;
    menuAction(menu.showMenu());
  }
  else{
    mvwprintw(prompt, 5, 2, "%s", "File is not available.");
    wgetch(prompt);
    Menu menu;
    menuAction(menu.showMenu());
  }
} // open

void mySave(){
  int x, y;
  getmaxyx(stdscr, y, x);
  WINDOW *prompt = newwin(10, 40, y/2-5, x/2-20);
  box(prompt, 0, 0);
  keypad(prompt, TRUE);
  mvwprintw(prompt, 2, 2, "%s", "SAVE");
  mvwprintw(prompt, 4, 2, "%s", "This file will be saved.");
  wrefresh(prompt);
  endwin(); // idk for now
  // say saved success
}

void mySaveAs(){
  int x, y;
  getmaxyx(stdscr, y, x);
  WINDOW *prompt;
  prompt = newwin(10, 40, y/2-5, x/2-20);
  box(prompt, 0, 0);
  keypad(prompt, TRUE);
  mvwprintw(prompt, 2, 4, "%s", "SAVE AS");
  mvwprintw(prompt, 4, 2, "%s", "Enter a new file name:");
  mvwprintw(prompt, 5, 2, "%s", "");
  wrefresh(prompt);
  echo();
  char input[80];
  wgetstr(prompt, input);
  noecho();
  endwin(); // for now
}

void myExit(){
  int x, y;
  getmaxyx(stdscr, y, x);
  WINDOW *prompt = newwin(10, 40, y/2-5, x/2-20);
  box(prompt, 0, 0);
  keypad(prompt, TRUE);
  //mvwprintw(prompt, 2, 2,
}
