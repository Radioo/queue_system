#include <map>
#include <ranges>

#include <ql/experimental/math/fireflyalgorithm.hpp>
#include "queue_system/frame/main.hpp"
#include "queue_system/model/data_type_col.hpp"

queue_system::frame::main::main() : wxFrame(nullptr, wxID_ANY, "System kolejkowy M/M/m/FiFo/N/F", wxDefaultPosition,
                                            wxSize(1200, 800)) {
    app_panel = new wxPanel(this, wxID_ANY);

    auto* main_sizer = new wxBoxSizer(wxHORIZONTAL);

    auto* outer_sizer = new wxBoxSizer(wxVERTICAL);
    auto* right_vsizer = new wxBoxSizer(wxVERTICAL);

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

    outer_sizer->Add(input1_sizer, 0, wxEXPAND, 5);

    auto* input2_sizer = new wxBoxSizer(wxHORIZONTAL);

    input2_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,
                                  get_float_input_validator(&input2_value));
    input2_input->SetValue("2");
    input2_sizer->Add(input2_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    auto* input2_text = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("[μ] Średnia intensywność obsługi"),
                                         wxDefaultPosition, wxDefaultSize, 0);
    input2_text->Wrap(-1);
    input2_sizer->Add(input2_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    outer_sizer->Add(input2_sizer, 0, wxEXPAND, 5);

    auto* input3_sizer = new wxBoxSizer(wxHORIZONTAL);

    input3_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,
                                  get_uint_input_validator(&input3_value));
    input3_input->SetValue("2");
    input3_sizer->Add(input3_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    auto* input3_text = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("[m] Liczba kanałów obsługi"),
                                         wxDefaultPosition, wxDefaultSize, 0);
    input3_text->Wrap(-1);
    input3_sizer->Add(input3_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    outer_sizer->Add(input3_sizer, 0, wxEXPAND, 5);

    auto* input4_sizer = new wxBoxSizer(wxHORIZONTAL);

    input4_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,
                                  get_uint_input_validator(&input4_value));
    input4_input->SetValue("5");
    input4_sizer->Add(input4_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    auto* input4_text = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("[N] Maksymalna liczba zgłoszeń"),
                                         wxDefaultPosition, wxDefaultSize, 0);
    input4_text->Wrap(-1);
    input4_sizer->Add(input4_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    outer_sizer->Add(input4_sizer, 0, wxEXPAND, 5);

    auto* buttons_sizer = new wxBoxSizer(wxHORIZONTAL);

    auto* analyze_button = new wxButton(app_panel, wxID_ANY, wxString::FromUTF8("Analizuj"));
    analyze_button->Bind(wxEVT_BUTTON, &main::on_analyze, this);
    buttons_sizer->Add(analyze_button, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    outer_sizer->Add(buttons_sizer, 0, wxEXPAND, 5);

    data_view = new wxDataViewListCtrl(app_panel, wxID_ANY);
    auto* name_column = data_view->AppendTextColumn(wxString::FromUTF8("Nazwa"));
    name_column->SetWidth(400);
    data_view->AppendTextColumn(wxString::FromUTF8("Wartość"));

    outer_sizer->Add(data_view, 1, wxEXPAND, 5);

    add_initial_data_values();



    auto* title_text = new wxStaticText(app_panel, wxID_ANY,wxString::FromUTF8("Parametry algorytmu świetlika:"),wxDefaultPosition, wxDefaultSize, 0);
    right_vsizer->Add(title_text, 0, wxALL, 5);

    auto* population_size_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* population_size_text = new wxStaticText(app_panel, wxID_ANY,wxString::FromUTF8("Liczba świetlików"),wxDefaultPosition, wxDefaultSize, 0);
    population_size_text->Wrap(-1);
    population_size = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,get_float_input_validator(&population_size_value));
    population_size->SetValue("50");
    population_size_sizer->Add(population_size, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    population_size_sizer->Add(population_size_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    right_vsizer->Add(population_size_sizer, 0, wxEXPAND, 5);

    auto* InitialAttractiveness_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* InitialAttractiveness_text = new wxStaticText(app_panel, wxID_ANY,wxString::FromUTF8("Początkowa atrakcyjność"),wxDefaultPosition, wxDefaultSize, 0);
    InitialAttractiveness_text->Wrap(-1);
    InitialAttractiveness = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,get_float_input_validator(&subpopulation_size_value));
    InitialAttractiveness->SetValue("1");
    InitialAttractiveness_sizer->Add(InitialAttractiveness, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    InitialAttractiveness_sizer->Add(InitialAttractiveness_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    right_vsizer->Add(InitialAttractiveness_sizer, 0, wxEXPAND, 5);

    auto* MinimumAttractiveness_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* MinimumAttractiveness_text = new wxStaticText(app_panel, wxID_ANY,wxString::FromUTF8("Minimalna atrakcyjność"),wxDefaultPosition, wxDefaultSize, 0);
    MinimumAttractiveness_text->Wrap(-1);
    MinimumAttractiveness = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,get_float_input_validator(&mutation_factor_value));
    MinimumAttractiveness->SetValue("0.2");
    MinimumAttractiveness_sizer->Add(MinimumAttractiveness, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    MinimumAttractiveness_sizer->Add(MinimumAttractiveness_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    right_vsizer->Add(MinimumAttractiveness_sizer, 0, wxEXPAND, 5);

    auto* LightAbsorptionCoefficient_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* LightAbsorptionCoefficient_text = new wxStaticText(app_panel, wxID_ANY,wxString::FromUTF8("Współczynnik pochłaniania światła"),wxDefaultPosition, wxDefaultSize, 0);
    LightAbsorptionCoefficient_text->Wrap(-1);
    LightAbsorptionCoefficient = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,get_float_input_validator(&crossover_factor_value));
    LightAbsorptionCoefficient->SetValue("0.5");
    LightAbsorptionCoefficient_sizer->Add(LightAbsorptionCoefficient, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    LightAbsorptionCoefficient_sizer->Add(LightAbsorptionCoefficient_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    right_vsizer->Add(LightAbsorptionCoefficient_sizer, 0, wxEXPAND, 5);

    auto* StandardDeviationForTheGaussianWalk_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* StandardDeviationForTheGaussianWalk_text = new wxStaticText(app_panel, wxID_ANY,wxString::FromUTF8("Odchylenie standardowe dla chodu gaussowskiego"),wxDefaultPosition, wxDefaultSize, 0);
    StandardDeviationForTheGaussianWalk_text->Wrap(-1);
    StandardDeviationForTheGaussianWalk = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,get_float_input_validator(&random_seed_value));
    StandardDeviationForTheGaussianWalk->SetValue("0.1");
    StandardDeviationForTheGaussianWalk_sizer->Add(StandardDeviationForTheGaussianWalk, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    StandardDeviationForTheGaussianWalk_sizer->Add(StandardDeviationForTheGaussianWalk_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    right_vsizer->Add(StandardDeviationForTheGaussianWalk_sizer, 0, wxEXPAND, 5);


    auto* MinM_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* MinM_text = new wxStaticText(app_panel, wxID_ANY,wxString::FromUTF8("Minimalny m"),wxDefaultPosition, wxDefaultSize, 0);
    MinM_text->Wrap(-1);
    MinM = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,get_float_input_validator(&random_seed_value));
    MinM->SetValue("1");
    MinM_sizer->Add(MinM, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    MinM_sizer->Add(MinM_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    right_vsizer->Add(MinM_sizer, 0, wxEXPAND, 5);

    auto* MaxM_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* MaxM_text = new wxStaticText(app_panel, wxID_ANY,wxString::FromUTF8("Maksymalnie m"),wxDefaultPosition, wxDefaultSize, 0);
    MaxM_text->Wrap(-1);
    MaxM = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,get_float_input_validator(&random_seed_value));
    MaxM->SetValue("100");
    MaxM_sizer->Add(MaxM, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    MaxM_sizer->Add(MaxM_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    right_vsizer->Add(MaxM_sizer, 0, wxEXPAND, 5);


    auto* optimize_button = new wxButton(app_panel, wxID_ANY, wxString::FromUTF8("Optymalizuj m"));
    optimize_button->Bind(wxEVT_BUTTON, &main::on_optimize, this);
    right_vsizer->Add(optimize_button, 0, wxEXPAND , 5);

    progress_bar = new wxGauge(app_panel, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
    right_vsizer->Add(progress_bar, 0, wxEXPAND | wxALL, 5);
    progress_bar->SetValue(0);

    auto* result_optimize_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* text_optimize = new wxStaticText(app_panel, wxID_ANY,wxString::FromUTF8("m ="),wxDefaultPosition, wxDefaultSize, 0);
    result_text = new wxStaticText(app_panel, wxID_ANY,wxString::FromUTF8(""),wxDefaultPosition, wxDefaultSize, 0);

    result_optimize_sizer->Add(text_optimize, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    result_optimize_sizer->Add(result_text, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    right_vsizer->Add(result_optimize_sizer, 0, wxEXPAND, 5);

    main_sizer->Add(outer_sizer, 1, wxEXPAND, 0);
    main_sizer->Add(right_vsizer, 1, wxEXPAND, 0);

    app_panel->SetSizer(main_sizer);
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

    queue.calculate();

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
}


void queue_system::frame::main::on_optimize(wxCommandEvent& event) {
    progress_bar->SetValue(0);

    double population_size_value;
    double initial_attractiveness_value;
    double minimum_attractiveness_value;
    double light_absorption_coefficient_value;
    double standard_deviation_value;

    long minM_value;
    long maxM_value;

    if (!population_size->GetValue().ToCDouble(&population_size_value)) {
        population_size_value = 0;
    }

    if (!InitialAttractiveness->GetValue().ToCDouble(&initial_attractiveness_value)) {
        initial_attractiveness_value = 0;
    }

    if (!MinimumAttractiveness->GetValue().ToCDouble(&minimum_attractiveness_value)) {
        minimum_attractiveness_value = 0;
    }

    if (!LightAbsorptionCoefficient->GetValue().ToCDouble(&light_absorption_coefficient_value)) {
        light_absorption_coefficient_value = 0;
    }

    if (!StandardDeviationForTheGaussianWalk->GetValue().ToCDouble(&standard_deviation_value)) {
        standard_deviation_value = 0;
    }

    if (!MinM->GetValue().ToLong(&minM_value)) {
        minM_value = 0;
    }

    if (!MaxM->GetValue().ToLong(&maxM_value)) {
        maxM_value = 1;
    }

    firefly.setPopulationSize(static_cast<float>(population_size_value));
    firefly.setInitialAttractiveness(static_cast<float>(initial_attractiveness_value));
    firefly.setMinimumAttractiveness(static_cast<float>(minimum_attractiveness_value));
    firefly.setLightAbsorptionCoefficient(static_cast<float>(light_absorption_coefficient_value));
    firefly.setStandardDeviationForTheGaussianWalk(static_cast<float>(standard_deviation_value));
    firefly.setMinM(static_cast<int>(minM_value));
    firefly.setMaxM(static_cast<int>(maxM_value));

    queue.set_stream_intensity(std::stof(input1_input->GetValue().ToStdString()));
    queue.set_average_service_intensity(std::stof(input2_input->GetValue().ToStdString()));
    queue.set_service_channels(std::stoull(input3_input->GetValue().ToStdString()));
    queue.set_max_requests(std::stoull(input4_input->GetValue().ToStdString()));
    queue.calculate();

    firefly.optimize(queue);
    progress_bar->SetValue(100);
}



void queue_system::frame::main::set_data_value(model::data_type data_type, const double value) const {
    const auto row = static_cast<int>(data_type);
    const auto value_str = std::to_string(value);
    data_view->SetValue(value_str, row, static_cast<int>(model::data_type_col::VALUE));
}
