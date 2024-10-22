#include <map>

#include "queue_system/frame/main.hpp"

#include <ranges>
#include <queue_system/model/data_type.hpp>

queue_system::frame::main::main() : wxFrame(nullptr, wxID_ANY, "System kolejkowy M/M/m/FiFo/N/F", wxDefaultPosition,
                                            wxSize(600, 800)) {
    app_panel = new wxPanel(this, wxID_ANY);

    auto* outer_sizer = new wxBoxSizer(wxVERTICAL);

    auto* input1_sizer = new wxBoxSizer(wxHORIZONTAL);

    auto* input1_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0,
                                        get_input_validator(&input1_value));
    input1_sizer->Add(input1_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    auto* input1_text = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("[λ] Intensywność strumienia zgłoszeń"),
                                         wxDefaultPosition, wxDefaultSize, 0);
    input1_text->Wrap(-1);
    input1_sizer->Add(input1_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    outer_sizer->Add(input1_sizer, 0, wxEXPAND, 5);

    auto* input2_sizer = new wxBoxSizer(wxHORIZONTAL);

    auto* input2_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0,
                                        get_input_validator(&input2_value));
    input2_sizer->Add(input2_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    auto* input2_text = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("[μ] Średnia intensywność obsługi"),
                                         wxDefaultPosition, wxDefaultSize, 0);
    input2_text->Wrap(-1);
    input2_sizer->Add(input2_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    outer_sizer->Add(input2_sizer, 0, wxEXPAND, 5);

    auto* input3_sizer = new wxBoxSizer(wxHORIZONTAL);

    auto* input3_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0,
                                        get_input_validator(&input3_value));
    input3_sizer->Add(input3_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    auto* input3_text = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("[m] Liczba kanałów obsługi"),
                                         wxDefaultPosition, wxDefaultSize, 0);
    input3_text->Wrap(-1);
    input3_sizer->Add(input3_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    outer_sizer->Add(input3_sizer, 0, wxEXPAND, 5);

    auto* input4_sizer = new wxBoxSizer(wxHORIZONTAL);

    auto* input4_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0,
                                        get_input_validator(&input4_value));
    input4_sizer->Add(input4_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    auto* input4_text = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("[N] Maksymalna liczba zgłoszeń"),
                                         wxDefaultPosition, wxDefaultSize, 0);
    input4_text->Wrap(-1);
    input4_sizer->Add(input4_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    outer_sizer->Add(input4_sizer, 0, wxEXPAND, 5);

    data_view = new wxDataViewListCtrl(app_panel, wxID_ANY);
    auto* name_column = data_view->AppendTextColumn(wxString::FromUTF8("Nazwa"));
    name_column->SetWidth(400);
    data_view->AppendTextColumn(wxString::FromUTF8("Wartość"));

    outer_sizer->Add(data_view, 1, wxEXPAND, 5);

    add_initial_data_values();

    app_panel->SetSizer(outer_sizer);
    app_panel->Layout();
}

wxFloatingPointValidator<float> queue_system::frame::main::get_input_validator(float* input) {
    return {6, input, wxNUM_VAL_NO_TRAILING_ZEROES};
}

void queue_system::frame::main::add_initial_data_values() const {
    static std::map<model::data_type, std::tuple<std::string, std::string>> initial_items = {
        {model::data_type::LOAD_FACTOR, {"Współczynnik obciążenia stanowiska obsługi", "0"}},
        {model::data_type::PROBABILITY_P0, {"Prawdopodobieństwo p0", "0"}},
        {model::data_type::PROBABILITY_P1, {"Prawdopodobieństwo p1", "0"}},
        {model::data_type::PROBABILITY_P2, {"Prawdopodobieństwo p2", "0"}},
    };


    for(const auto& value : initial_items | std::views::values) {
        wxVector<wxVariant> data;
        data.push_back(wxVariant(wxString::FromUTF8(std::get<0>(value))));
        data.push_back(wxVariant(wxString::FromUTF8(std::get<1>(value))));

        data_view->AppendItem(data);
    }
}
