///////////////////////////////////////////////////////////////////////////////////////
// ONE PENDING WINDOW
// Shows a list of pending applications for one course, sorted by applicant's major GPA

#ifndef ONEPENDINGUI_H 
#define ONEPENDINGUI_H

#include "Types.h"
#include <gtkmm.h>

class GradAppQueue;
class UGradAppQueue;

class OnePendingUI : public Gtk::Window {
  public:
    OnePendingUI(Manager*, string);
    ~OnePendingUI();

    Manager* manager;

  private:
    void on_backButton(const Glib::ustring& data);
    void on_cancelButton(const Glib::ustring& data);
    void on_saveButton(const Glib::ustring& data);
    void fillSummary();
    int  fillUGradSummary(UGradAppQueue*, int);
    void fillGradSummary(GradAppQueue*, int);
    void saveDialog();

    Gtk::Table          aTable;
    Gtk::Label	        aLabel;
    Gtk::Button	        backButton, cancelButton, saveButton;
    Gtk::ListViewText   summary;
    Gtk::ScrolledWindow scrolledWindow;

    string course;
};

#endif
