//
// Created by nick on 3/21/16.
//

#ifndef CALC_GUI_SOLVER_H
#define CALC_GUI_SOLVER_H


#include <gtkmm/entry.h>

class Solver {
private:
    Gtk::Entry *target;
    std::string input;
protected:
    void run();
    std::string exec(const char* cmd);
public:
    Solver(Gtk::Entry *target,std::string input);
};


#endif //CALC_GUI_SOLVER_H
