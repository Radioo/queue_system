#include <wx/wx.h>
#include <wx/valnum.h>

namespace queue_system::frame {
    class main final : public wxFrame {
    public:
        main();

    private:
        wxPanel* app_panel;

        float input1_value;
        float input2_value;
        float input3_value;

        static wxFloatingPointValidator<float> get_input_validator(float* input);
    };
}