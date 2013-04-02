//////////////////////////////////////////////////////////////////////////
// CREATE WORK EXPERIENCE UI
// Prompts user to give more information about related work experience

#ifndef WORKEXPUI_H
#define WORKEXPUI_H

#include <gtkmm.h>

#include "Types.h"
#include "WorkExp.h"

class WorkExpUI : public Gtk::Window {
  public:
    WorkExpUI(Manager*, WorkExp*);
    ~WorkExpUI();

    Manager*     manager;
    WorkExp*     workExp;

  private:
    void on_nextOrOtherButton(const Glib::ustring& data);
    void on_backButton(const Glib::ustring& data);
    void on_skipButton(const Glib::ustring& data);

    // Widgets
    Gtk::Table         createTable;
    Gtk::Label         aLabel, durationLabel, startLabel, endLabel, respLabel;
    Gtk::ComboBoxText  monthCombo, year1Combo, month1Combo, day1Combo, year2Combo, month2Combo, day2Combo;
    Gtk::Entry         respEntry;
    Gtk::Button        nextButton, backButton, otherButton, skipButton;
};

#endif
