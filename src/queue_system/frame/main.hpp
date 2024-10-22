#pragma once

#include <wx/wx.h>
#include <wx/valnum.h>
#include <wx/dataview.h>

#include "queue_system/calc/queue.hpp"

namespace queue_system::frame {
    class main final : public wxFrame {
    public:
        main();

    private:
        wxPanel* app_panel;

        wxTextCtrl* input1_input;
        wxTextCtrl* input2_input;
        wxTextCtrl* input3_input;
        wxTextCtrl* input4_input;

        wxDataViewListCtrl* data_view;

        float input1_value = 0;
        float input2_value = 0;
        float input3_value = 0;
        float input4_value = 0;

        calc::queue queue = {0, 0, 0, 0};

        static wxFloatingPointValidator<float> get_input_validator(float* input);

        void add_initial_data_values() const;
        void on_analyze(wxCommandEvent& event);
    };
}