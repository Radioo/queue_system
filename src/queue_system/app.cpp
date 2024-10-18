#include "queue_system/app.hpp"
#include "queue_system/frame/main.hpp"

bool queue_system::app::OnInit() {
    auto* frame = new frame::main();
    frame->Show();
    return true;
}
