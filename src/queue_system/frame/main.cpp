#include "queue_system/frame/main.hpp"

queue_system::frame::main::main(): wxFrame(nullptr, wxID_ANY, "System kolejkowy", wxDefaultPosition, wxSize(600, 800)) {
    app_panel = new wxPanel(this, wxID_ANY);

    auto* outer_sizer = new wxBoxSizer(wxVERTICAL );

    auto* input1_sizer = new wxBoxSizer(wxHORIZONTAL );

    auto* input1_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    input1_sizer->Add(input1_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );

    auto* input1_text = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("Intensywność strumienia zgłoszeń"), wxDefaultPosition, wxDefaultSize, 0 );
    input1_text->Wrap(-1 );
    input1_sizer->Add(input1_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );

    outer_sizer->Add(input1_sizer, 0, wxEXPAND, 5 );

    auto* input2_sizer = new wxBoxSizer(wxHORIZONTAL );

    auto* input2_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    input2_sizer->Add(input2_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );

    auto* input2_text = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("Średnia intensywność obsługi"), wxDefaultPosition, wxDefaultSize, 0 );
    input2_text->Wrap(-1 );
    input2_sizer->Add(input2_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );

    outer_sizer->Add(input2_sizer, 0, wxEXPAND, 5 );

    auto* input3_sizer = new wxBoxSizer(wxHORIZONTAL );

    auto* input3_input = new wxTextCtrl(app_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    input3_sizer->Add(input3_input, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );

    auto* input3_text = new wxStaticText(app_panel, wxID_ANY, wxString::FromUTF8("Liczba kanałów obsługi"), wxDefaultPosition, wxDefaultSize, 0 );
    input3_text->Wrap(-1 );
    input3_sizer->Add(input3_text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );

    outer_sizer->Add(input3_sizer, 0, wxEXPAND, 5 );

    app_panel->SetSizer(outer_sizer );
    app_panel->Layout();
}
