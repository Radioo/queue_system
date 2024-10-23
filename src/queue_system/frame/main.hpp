#pragma once

#include <wx/wx.h>
#include <wx/valnum.h>
#include <wx/dataview.h>

#include "queue_system/calc/queue.hpp"
#include "queue_system/model/data_type.hpp"

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
        std::uint64_t input3_value = 0;
        std::uint64_t input4_value = 0;

        calc::queue queue = {0, 0, 0, 0};

        static wxFloatingPointValidator<float> get_float_input_validator(float* input);
        static wxIntegerValidator<std::uint64_t> get_uint_input_validator(std::uint64_t* input);

        void add_initial_data_values() const;
        void on_analyze(wxCommandEvent& event);
        void set_data_value(model::data_type data_type, double value) const;
    };
}