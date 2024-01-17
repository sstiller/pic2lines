// generated by Fast Light User Interface Designer (fluid) version 1.0308

#ifndef fltkgui_hpp
#define fltkgui_hpp
#include <FL/Fl.H>
#include "../gui.hpp"
#include <atomic>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Spinner.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Clock.H>

class FltkGui : public Gui {
public:
  FltkGui();
private:
  Fl_Window *mainWindow;
  static unsigned char menu__i18n_done;
  static Fl_Menu_Item menu_[];
  static Fl_Menu_Item *fileOpen;
  inline void cb_fileOpen_i(Fl_Menu_*, void*);
  static void cb_fileOpen(Fl_Menu_*, void*);
  inline void cb_Quit_i(Fl_Menu_*, void*);
  static void cb_Quit(Fl_Menu_*, void*);
  static unsigned char menu_Unit_i18n_done;
  static Fl_Menu_Item menu_Unit[];
public:
  Fl_Input *outputFileNameInput;
private:
  Fl_Button *generateGcodeButton;
  inline void cb_generateGcodeButton_i(Fl_Button*, void*);
  static void cb_generateGcodeButton(Fl_Button*, void*);
  Fl_Box *loadedImageBox;
  std::atomic<bool> quit{false}; 
public:
  void runEventLoop(int argc, char** argv);
  void stopEventLoop();
private:
  void openJpegImage();
protected:
  void displayErrorMessage(const std::string& message);
};
#endif
