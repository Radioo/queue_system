#include <wx/wx.h>

namespace queue_system::frame {
    class main final : public wxFrame {
    public:
        main();

    private:
        wxPanel* app_panel;
    };
}