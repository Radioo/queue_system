#pragma once

#include <wx/wx.h>
#include <wx/valnum.h>
#include <wx/dataview.h>

namespace queue_system::frame {
    class main final : public wxFrame {
    public:
        main();

    private:
        wxPanel* app_panel;

        wxDataViewListCtrl* data_view;

        float input1_value = 0;
        float input2_value = 0;
        float input3_value = 0;
        float input4_value = 0;

        static wxFloatingPointValidator<float> get_input_validator(float* input);

        void add_initial_data_values() const;
    };
}