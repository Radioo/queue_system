#include <map>
#include <ranges>

#include "queue_system/frame/main.hpp"
#include "queue_system/model/data_type_col.hpp"

queue_system::frame::main::main() : wxFrame(nullptr, wxID_ANY, "System kolejkowy M/M/m/FiFo/N/F", wxDefaultPosition,
                                            wxSize(800, 800)) {
    app_panel = new wxPanel(this, wxID_ANY);

    auto* outer_sizer = new wxBoxSizer(wxVERTICAL);
    auto* analysis_sizer = new wxBoxSizer(wxVERTICAL);
    auto* optimization_sizer = new wxBoxSizer(wxVERTICAL);
    auto* top_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* input1_sizer = new wxBoxSizer(wxHORIZONTAL);

    input1_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,
                                  get_float_input_validator(&input1_value));
    input1_input->SetValue("2");
    input1_sizer->Add(input1_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    auto* input1_text = new wxStaticText(app_panel, wxID_ANY,
                                         wxString::FromUTF8("[λ] Intensywność strumienia zgłoszeń"),
                                         wxDefaultPosition, wxDefaultSize, 0);
    input1_text->Wrap(-1);
    input1_sizer->Add(input1_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    analysis_sizer->Add(input1_sizer, 0, wxEXPAND, 5);

    auto* input2_sizer = new wxBoxSizer(wxHORIZONTAL);

    input2_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,
                                  get_float_input_validator(&input2_value));
    input2_input->SetValue("2");
    input2_sizer->Add(input2_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    auto* input2_text = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("[μ] Średnia intensywność obsługi"),
                                         wxDefaultPosition, wxDefaultSize, 0);
    input2_text->Wrap(-1);
    input2_sizer->Add(input2_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    analysis_sizer->Add(input2_sizer, 0, wxEXPAND, 5);

    auto* input3_sizer = new wxBoxSizer(wxHORIZONTAL);

    input3_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,
                                  get_uint_input_validator(&input3_value));
    input3_input->SetValue("2");
    input3_sizer->Add(input3_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    auto* input3_text = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("[m] Liczba kanałów obsługi"),
                                         wxDefaultPosition, wxDefaultSize, 0);
    input3_text->Wrap(-1);
    input3_sizer->Add(input3_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    analysis_sizer->Add(input3_sizer, 0, wxEXPAND, 5);

    auto* input4_sizer = new wxBoxSizer(wxHORIZONTAL);

    input4_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,
                                  get_uint_input_validator(&input4_value));
    input4_input->SetValue("5");
    input4_sizer->Add(input4_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    auto* input4_text = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("[N] Maksymalna liczba zgłoszeń"),
                                         wxDefaultPosition, wxDefaultSize, 0);
    input4_text->Wrap(-1);
    input4_sizer->Add(input4_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    analysis_sizer->Add(input4_sizer, 0, wxEXPAND, 5);

    auto* cost_1_sizer = new wxBoxSizer(wxHORIZONTAL);
    cost_1_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,
                                  get_float_input_validator(&cost_1_value));
    cost_1_input->SetValue("100");
    cost_1_sizer->Add(cost_1_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    auto* cost_1_text = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("Koszt c1"), wxDefaultPosition,
                                         wxDefaultSize, 0);
    cost_1_text->Wrap(-1);
    cost_1_sizer->Add(cost_1_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    analysis_sizer->Add(cost_1_sizer, 0, wxEXPAND, 5);

    auto* cost_2_sizer = new wxBoxSizer(wxHORIZONTAL);
    cost_2_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,
                                  get_float_input_validator(&cost_2_value));
    cost_2_input->SetValue("200");
    cost_2_sizer->Add(cost_2_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    auto* cost_2_text = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("Koszt c2"), wxDefaultPosition,
                                         wxDefaultSize, 0);
    cost_2_sizer->Add(cost_2_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    analysis_sizer->Add(cost_2_sizer, 0, wxEXPAND, 5);

    top_sizer->Add(analysis_sizer, 1, wxEXPAND, 5);

    auto* objective_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* objective_label = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("Wartość funkcji celu:"),
                                             wxDefaultPosition, wxDefaultSize, 0);
    auto font = objective_label->GetFont();
    font.SetWeight(wxFONTWEIGHT_BOLD);
    objective_label->SetFont(font);
    objective_value_label = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("0"),
                                                   wxDefaultPosition, wxDefaultSize, 0);
    objective_sizer->Add(objective_label, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    objective_sizer->Add(objective_value_label, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    auto* max_iterations_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* max_iterations_label = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("Maksymalna liczba iteracji"),
                                             wxDefaultPosition, wxDefaultSize, 0);
    max_iterations_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,
                                  get_uint_input_validator(&max_iterations_value));
    max_iterations_input->SetValue("5000");
    max_iterations_sizer->Add(max_iterations_label, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    max_iterations_sizer->Add(max_iterations_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    auto* firefly_count_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* firefly_count_label = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("Liczba świetlików"),
                                             wxDefaultPosition, wxDefaultSize, 0);
    firefly_count_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,
                                  get_uint_input_validator(&firefly_count_value));
    firefly_count_input->SetValue("40");
    firefly_count_sizer->Add(firefly_count_label, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    firefly_count_sizer->Add(firefly_count_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    // auto* exact_optimization_sizer = new wxBoxSizer(wxHORIZONTAL);
    // auto* exact_optimization_label = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("Dokładna optymalna wartość m:"),
    //                                                   wxDefaultPosition, wxDefaultSize, 0);
    // exact_optimization_value_label = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("0"),
    //                                                   wxDefaultPosition, wxDefaultSize, 0);
    // exact_optimization_sizer->Add(exact_optimization_label, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    // exact_optimization_sizer->Add(exact_optimization_value_label, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    auto* rounded_optimization_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* rounded_optimization_label = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("Optymalna wartość m:"),
                                                      wxDefaultPosition, wxDefaultSize, 0);
    rounded_optimization_value_label = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("0"),
                                                      wxDefaultPosition, wxDefaultSize, 0);
    rounded_optimization_sizer->Add(rounded_optimization_label, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    rounded_optimization_sizer->Add(rounded_optimization_value_label, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    optimization_sizer->Add(objective_sizer, 0, wxEXPAND, 5);
    // optimization_sizer->Add(exact_optimization_sizer, 0, wxEXPAND, 5);
    optimization_sizer->Add(rounded_optimization_sizer, 0, wxEXPAND, 5);
    optimization_sizer->Add(max_iterations_sizer, 0, wxEXPAND, 5);
    optimization_sizer->Add(firefly_count_sizer, 0, wxEXPAND, 5);

    top_sizer->Add(optimization_sizer, 1, wxEXPAND, 5);

    outer_sizer->Add(top_sizer, 0, wxEXPAND, 5);

    auto* buttons_sizer = new wxBoxSizer(wxHORIZONTAL);

    auto* analyze_button = new wxButton(app_panel, wxID_ANY, wxString::FromUTF8("Analizuj"));
    analyze_button->Bind(wxEVT_BUTTON, &main::on_analyze, this);

    auto* optimize_button = new wxButton(app_panel, wxID_ANY, wxString::FromUTF8("Optymalizuj"));
    optimize_button->Bind(wxEVT_BUTTON, &main::on_optimize, this);

    buttons_sizer->Add(analyze_button, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    buttons_sizer->Add(optimize_button, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    outer_sizer->Add(buttons_sizer, 0, wxEXPAND, 5);

    data_view = new wxDataViewListCtrl(app_panel, wxID_ANY);
    auto* name_column = data_view->AppendTextColumn(wxString::FromUTF8("Nazwa"));
    name_column->SetWidth(400);
    data_view->AppendTextColumn(wxString::FromUTF8("Wartość"));

    outer_sizer->Add(data_view, 1, wxEXPAND, 5);

    add_initial_data_values();

    app_panel->SetSizer(outer_sizer);
    app_panel->Layout();
}

wxFloatingPointValidator<float> queue_system::frame::main::get_float_input_validator(float* input) {
    return {6, input, wxNUM_VAL_NO_TRAILING_ZEROES};
}

wxIntegerValidator<std::uint64_t> queue_system::frame::main::get_uint_input_validator(std::uint64_t* input) {
    return {input};
}

void queue_system::frame::main::add_initial_data_values() const {
    static std::map<model::data_type, std::tuple<std::string, std::string>> initial_items = {
            {model::data_type::RELATIVE_SERVICE_INTENSITY,         {"Względna intensywność obsługi",                  "0"}},
            {model::data_type::PROBABILITY_P0,                     {"Prawdopodobieństwo p0",                         "0"}},
            {model::data_type::PROBABILITY_P1,                     {"Prawdopodobieństwo p1",                         "0"}},
            {model::data_type::PROBABILITY_P2,                     {"Prawdopodobieństwo p2",                         "0"}},
            {model::data_type::PROBABILITY_P3,                     {"Prawdopodobieństwo p3",                         "0"}},
            {model::data_type::PROBABILITY_P4,                     {"Prawdopodobieństwo p4",                         "0"}},
            {model::data_type::PROBABILITY_P5,                     {"Prawdopodobieństwo p5",                         "0"}},
            {model::data_type::AVERAGE_QUEUE_LENGTH,               {"Średnia ilość zgłoszeń oczekujących w kolejce", "0"}},
            {model::data_type::AVERAGE_OCCUPIED_SERVICE_CHANNELS,  {"Średnia ilość zajętych kanałów obsługi",        "0"}},
            {model::data_type::ABSOLUTE_ABILITY_TO_OPERATE,        {"Bezwzględną zdolność obsługi systemu",          "0"}},
            {model::data_type::AVERAGE_APPLICATIONS,               {"Średnia ilość zgłoszeń",                        "0"}},
            {model::data_type::AVERAGE_APPLICATION_TIME_IN_SYSTEM, {"Średni czas przebywania zgłoszeń w systemie",   "0"}},
            {model::data_type::AVERAGE_APPLICATION_TIME_IN_QUEUE,  {"Średni czas przebywania zgłoszeń w kolejce",    "0"}},
    };


    for (const auto& value: initial_items | std::views::values) {
        wxVector<wxVariant> data;
        data.push_back(wxVariant(wxString::FromUTF8(std::get<0>(value))));
        data.push_back(wxVariant(wxString::FromUTF8(std::get<1>(value))));

        data_view->AppendItem(data);
    }
}

void queue_system::frame::main::on_analyze(wxCommandEvent& event) {
    queue.set_stream_intensity(std::stof(input1_input->GetValue().ToStdString()));
    queue.set_average_service_intensity(std::stof(input2_input->GetValue().ToStdString()));
    queue.set_service_channels(std::stoull(input3_input->GetValue().ToStdString()));
    queue.set_max_requests(std::stoull(input4_input->GetValue().ToStdString()));
    queue.set_cost_1(std::stod(cost_1_input->GetValue().ToStdString()));
    queue.set_cost_2(std::stod(cost_2_input->GetValue().ToStdString()));

    try {
        queue.calculate();
    }
    catch(std::exception& e) {
        wxMessageBox("Błąd podczas obliczeń: " + wxString::FromUTF8(e.what()), "Błąd", wxICON_ERROR);
        return;
    }

    const auto& probabilities = queue.get_probabilities();
    set_data_value(model::data_type::RELATIVE_SERVICE_INTENSITY, queue.get_relative_service_intensity());
    set_data_value(model::data_type::PROBABILITY_P0, probabilities[0]);
    set_data_value(model::data_type::PROBABILITY_P1, probabilities[1]);
    set_data_value(model::data_type::PROBABILITY_P2, probabilities[2]);
    set_data_value(model::data_type::PROBABILITY_P3, probabilities[3]);
    set_data_value(model::data_type::PROBABILITY_P4, probabilities[4]);
    set_data_value(model::data_type::PROBABILITY_P5, probabilities[5]);
    set_data_value(model::data_type::AVERAGE_QUEUE_LENGTH, queue.get_average_queue_length());
    set_data_value(model::data_type::AVERAGE_OCCUPIED_SERVICE_CHANNELS, queue.get_average_occupied_service_channels());
    set_data_value(model::data_type::ABSOLUTE_ABILITY_TO_OPERATE, queue.get_absolute_ability_to_operate());
    set_data_value(model::data_type::AVERAGE_APPLICATIONS, queue.get_average_applications());
    set_data_value(model::data_type::AVERAGE_APPLICATION_TIME_IN_SYSTEM,
                   queue.get_average_application_time_in_system());
    set_data_value(model::data_type::AVERAGE_APPLICATION_TIME_IN_QUEUE, queue.get_average_application_time_in_queue());

    objective_value_label->SetLabel(std::to_string(queue.get_objective_function_value()));
}

void queue_system::frame::main::on_optimize(wxCommandEvent& event) {
    queue.set_max_iterations(std::stoull(max_iterations_input->GetValue().ToStdString()));
    queue.set_firefly_count(std::stoull(firefly_count_input->GetValue().ToStdString()));

    try {
        queue.optimize();

        // exact_optimization_value_label->SetLabel(wxString::FromUTF8(std::to_string(queue.get_exact_optimized_m()) + " f(m) = " + std::to_string(queue.get_exact_optimized_m_value())));
        rounded_optimization_value_label->SetLabel(wxString::FromUTF8(std::to_string(queue.get_rounded_optimized_m()) + " f(m) = " + std::to_string(queue.get_rounded_optimized_m_value())));
    }
    catch(std::exception& e) {
        wxMessageBox("Błąd podczas optymalizacji: " + wxString::FromUTF8(e.what()), "Błąd", wxICON_ERROR);
    }
}

void queue_system::frame::main::set_data_value(model::data_type data_type, const double value) const {
    const auto row = static_cast<int>(data_type);
    const auto value_str = std::to_string(value);
    data_view->SetValue(value_str, row, static_cast<int>(model::data_type_col::VALUE));
}
