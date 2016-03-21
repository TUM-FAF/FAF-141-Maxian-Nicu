//
// Created by nick on 3/21/16.
//

#include <glibmm/thread.h>
#include "Solver.h"

Solver::Solver(Gtk::Entry *target,std::string input) {
    Glib::Thread *thread = Glib::Thread::create(sigc::mem_fun(*this,&Solver::run), true);
    this->target = target;
    this->input = input;
}

void Solver::run() {
    std::string command ="./bin/calculator \""+input+"\"";
    std::string output = exec(command.c_str());
    target->set_text(output);
}

std::string Solver::exec(const char* cmd) {
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    return result;
}