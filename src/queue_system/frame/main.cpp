#include <map>
#include <ranges>

#include <wx/statline.h>
#include <queue_system/lib/fireflyalgorithm.hpp>
#include "queue_system/frame/main.hpp"
#include "queue_system/model/data_type_col.hpp"

queue_system::frame::main::main() : wxFrame(nullptr, wxID_ANY, "System kolejkowy M/M/m/FiFo/N/F", wxDefaultPosition,
                                            wxSize(600, 800)) {
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


    auto* function_value_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* function_value_text = new wxStaticText(app_panel, wxID_ANY,wxString::FromUTF8("Wartość funkcji celu:"),wxDefaultPosition, wxDefaultSize, 0);
    function_value_text->Wrap(-1);
    function_value_sizer->Add(function_value_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    function_value = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,get_float_input_validator(&float_function_value));
    function_value->SetValue("10");
    function_value_sizer->Add(function_value, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    right_vsizer->Add(function_value_sizer, 0, wxEXPAND, 5);


    auto* title_text = new wxStaticText(app_panel, wxID_ANY,wxString::FromUTF8("Parametry algorytmu świetlika:"),wxDefaultPosition, wxDefaultSize, 0);
    right_vsizer->Add(title_text, 0, wxALL, 5);

    auto* population_size_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* population_size_text = new wxStaticText(app_panel, wxID_ANY,wxString::FromUTF8("population_size"),wxDefaultPosition, wxDefaultSize, 0);
    population_size_text->Wrap(-1);
    population_size = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,get_float_input_validator(&population_size_value));
    population_size->SetValue("0");
    population_size_sizer->Add(population_size, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    population_size_sizer->Add(population_size_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    right_vsizer->Add(population_size_sizer, 0, wxEXPAND, 5);

    auto* subpopulation_size_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* subpopulation_size_text = new wxStaticText(app_panel, wxID_ANY,wxString::FromUTF8("subpopulation_size"),wxDefaultPosition, wxDefaultSize, 0);
    subpopulation_size_text->Wrap(-1);
    subpopulation_size = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,get_float_input_validator(&subpopulation_size_value));
    subpopulation_size->SetValue("0");
    subpopulation_size_sizer->Add(subpopulation_size, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    subpopulation_size_sizer->Add(subpopulation_size_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    right_vsizer->Add(subpopulation_size_sizer, 0, wxEXPAND, 5);

    auto* mutation_factor_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* mutation_factor_text = new wxStaticText(app_panel, wxID_ANY,wxString::FromUTF8("mutation_factor"),wxDefaultPosition, wxDefaultSize, 0);
    mutation_factor_text->Wrap(-1);
    mutation_factor = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,get_float_input_validator(&mutation_factor_value));
    mutation_factor->SetValue("0");
    mutation_factor_sizer->Add(mutation_factor, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    mutation_factor_sizer->Add(mutation_factor_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    right_vsizer->Add(mutation_factor_sizer, 0, wxEXPAND, 5);

    auto* crossover_factor_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* crossover_factor_text = new wxStaticText(app_panel, wxID_ANY,wxString::FromUTF8("crossover_factor"),wxDefaultPosition, wxDefaultSize, 0);
    crossover_factor_text->Wrap(-1);
    crossover_factor = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,get_float_input_validator(&crossover_factor_value));
    crossover_factor->SetValue("0");
    crossover_factor_sizer->Add(crossover_factor, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    crossover_factor_sizer->Add(crossover_factor_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    right_vsizer->Add(crossover_factor_sizer, 0, wxEXPAND, 5);

    auto* random_seed_sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* random_seed_text = new wxStaticText(app_panel, wxID_ANY,wxString::FromUTF8("random_seed"),wxDefaultPosition, wxDefaultSize, 0);
    random_seed_text->Wrap(-1);
    random_seed = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT,get_float_input_validator(&random_seed_value));
    random_seed->SetValue("0");
    random_seed_sizer->Add(random_seed, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    random_seed_sizer->Add(random_seed_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    right_vsizer->Add(random_seed_sizer, 0, wxEXPAND, 5);



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

double objectiveFunction(queue_system::calc::queue& queue, double target) {
    queue.calculate();
    double averageWaitTime = queue.get_average_application_time_in_queue();
    return std::abs(averageWaitTime - target);
}

void queue_system::frame::main::on_optimize(wxCommandEvent& event) {
    progress_bar->SetValue(0);

    QuantLib::Size M = 50;
    QuantLib::Real beta0 = 1.0;
    QuantLib::Real betaMin = 0.2;
    QuantLib::Real gamma = 0.5;

    auto intensity = QuantLib::ext::make_shared<QuantLib::ExponentialIntensity>(beta0, betaMin, gamma);
    QuantLib::Real sigma = 0.1;
    auto randomWalk = QuantLib::ext::make_shared<QuantLib::GaussianWalk>(sigma);
    QuantLib::FireflyAlgorithm firefly(M, intensity, randomWalk);

    wxString valueStr = function_value->GetValue();
    double value;
    if (!valueStr.ToDouble(&value)) {
        value = 1;
    }

    auto func = [&](int m) {
        queue.set_service_channels(static_cast<std::uint64_t>(m));

        queue.set_stream_intensity(std::stof(input1_input->GetValue().ToStdString()));
        queue.set_average_service_intensity(std::stof(input2_input->GetValue().ToStdString()));
        queue.set_max_requests(std::stoull(input4_input->GetValue().ToStdString()));

        return objectiveFunction(queue, value);
    };

    int minM = 1;
    int maxM = 100;
    int optimalM = minM;
    double bestObjectiveValue = func(optimalM);

    for (int m = minM + 1; m <= maxM; ++m) {
        double currentObjectiveValue = func(m);
        if (currentObjectiveValue < bestObjectiveValue) {
            bestObjectiveValue = currentObjectiveValue;
            optimalM = m;
        }
    }

    std::cout << "Optimal number (m): " << optimalM << std::endl;
    //result_text->SetLabel(wxString::FromUTF8(function_value->GetValue()));
    progress_bar->SetValue(100);
}



void queue_system::frame::main::set_data_value(model::data_type data_type, const double value) const {
    const auto row = static_cast<int>(data_type);
    const auto value_str = std::to_string(value);
    data_view->SetValue(value_str, row, static_cast<int>(model::data_type_col::VALUE));
}
