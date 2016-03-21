#include <gtkmm-3.0/gtkmm/application.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/entry.h>
#include <gtkmm/builder.h>
#include <string>
#include <iostream>
#include <thread>
#include <glibmm/threads.h>
#include <glibmm/thread.h>
#include "Solver.h"

std::string input;
Gtk::Entry *inputEntry;

void updateInput(){
	inputEntry->set_text(input);
}

extern "C" G_MODULE_EXPORT void digit_1_button_handler(Gtk::Object* caller, gpointer data)
{
	input += "1";
	updateInput();
}

extern "C" G_MODULE_EXPORT void digit_0_button_handler(Gtk::Object* caller, gpointer data)
{
	input += "0";
	updateInput();
}

extern "C" G_MODULE_EXPORT void digit_2_button_handler(Gtk::Object* caller, gpointer data)
{
	input += "2";
	updateInput();
}

extern "C" G_MODULE_EXPORT void digit_3_button_handler(Gtk::Object* caller, gpointer data)
{
	input += "3";
	updateInput();
}

extern "C" G_MODULE_EXPORT void digit_4_button_handler(Gtk::Object* caller, gpointer data)
{
	input += "4";
	updateInput();
}

extern "C" G_MODULE_EXPORT void digit_5_button_handler(Gtk::Object* caller, gpointer data)
{
	input += "5";
	updateInput();
}

extern "C" G_MODULE_EXPORT void digit_6_button_handler(Gtk::Object* caller, gpointer data)
{
	input += "6";
	updateInput();
}

extern "C" G_MODULE_EXPORT void digit_7_button_handler(Gtk::Object* caller, gpointer data)
{
	input += "7";
	updateInput();
}

extern "C" G_MODULE_EXPORT void digit_8_button_handler(Gtk::Object* caller, gpointer data)
{
	input += "8";
	updateInput();
}

extern "C" G_MODULE_EXPORT void digit_9_button_handler(Gtk::Object* caller, gpointer data)
{
	input += "9";
	updateInput();
}

extern "C" G_MODULE_EXPORT void digit_10_button_handler(Gtk::Object* caller, gpointer data)
{
	input += "0";
	updateInput();
}

extern "C" G_MODULE_EXPORT void plus(Gtk::Object* caller, gpointer data)
{
	input += "+";
	updateInput();
}

extern "C" G_MODULE_EXPORT void minus(Gtk::Object* caller, gpointer data)
{
	input += "-";
	updateInput();
}

extern "C" G_MODULE_EXPORT void multiply(Gtk::Object* caller, gpointer data)
{
	input += "*";
	updateInput();
}

extern "C" G_MODULE_EXPORT void divide(Gtk::Object* caller, gpointer data)
{
	input += "/";
	updateInput();
}

void run(){
	new Solver(inputEntry,input);
}

extern "C" G_MODULE_EXPORT void compute(Gtk::Object* caller, gpointer data)
{
	run();
}

extern "C" G_MODULE_EXPORT void clear(Gtk::Object* caller, gpointer data)
{
	input = "";
	updateInput();
}

extern "C" G_MODULE_EXPORT void undo(Gtk::Object* caller, gpointer data)
{
	input = input.substr(0,input.length()-1);
	updateInput();
}


extern "C" G_MODULE_EXPORT void sign(Gtk::Object* caller, gpointer data)
{
	input += "signinv(0)";
	updateInput();
}

extern "C" G_MODULE_EXPORT void max(Gtk::Object* caller, gpointer data)
{
	input += "max(0)";
	updateInput();
}

extern "C" G_MODULE_EXPORT void power(Gtk::Object* caller, gpointer data)
{
	input += "power(0,0)";
	updateInput();
}

extern "C" G_MODULE_EXPORT void sqrt_fun(Gtk::Object* caller, gpointer data)
{
	input += "sqrt(0)";
	updateInput();
}

extern "C" G_MODULE_EXPORT void dot(Gtk::Object* caller, gpointer data)
{
	input += ".";
	updateInput();
}


int main(int argc,char** argv){
	if(!Glib::thread_supported()) Glib::thread_init();

	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc,argv,
																  Glib::ustring("com.maxiannicu.calculator.gui"));
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("layout.glade");

	Gtk::Window *window;
	builder->get_widget("mainwindow",window);
	builder->get_widget("input",inputEntry);
	gtk_builder_connect_signals(builder->gobj(),NULL);

	return app->run(*window);
}

