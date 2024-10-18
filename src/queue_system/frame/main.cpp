#include "queue_system/frame/main.hpp"

queue_system::frame::main::main(): wxFrame(nullptr, wxID_ANY, "System kolejkowy", wxDefaultPosition, wxSize(600, 800)) {
    app_panel = new wxPanel(this, wxID_ANY);
}
