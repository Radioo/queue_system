#include <wx/wx.h>

namespace queue_system {
    class app final : public wxApp {
    public:
        bool OnInit() override;
    };
}