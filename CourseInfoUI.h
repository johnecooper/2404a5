//////////////////////////////////////////////////////////////////////////
// CREATE COURSES INFORMATION WINDOW
// Prompts user to give more information about related courses

#ifndef COURSEINFOUI_H
#define COURSEINFOUI_H

#include <gtkmm.h>

#include "Types.h"
#include "TakenCourse.h"
#include "TACourse.h"

class CourseInfoUI : public Gtk::Window {
  public:
    CourseInfoUI(Manager*, int);
    ~CourseInfoUI();

    Manager*  manager;

    // 0 = TakenCourse
    // 1 = TACourse
    int whichCourse;

  private:
    void initWindow(Manager*);
    void on_nextButton(const Glib::ustring& data);
    void on_backButton(const Glib::ustring& data);
    void on_courseButton(const Glib::ustring& data);

    // Widgets
    Gtk::Table         createTable;
    Gtk::Label         aLabel, yearLabel, termLabel, finalLabel;
    Gtk::ComboBoxText  yearCombo, termCombo, finalCombo, courseCombo;
    Gtk::Button        nextButton, backButton, courseButton;
};

#endif

