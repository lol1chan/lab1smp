#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Handler {
public:
    virtual Handler* SetNext(Handler* handler) = 0;
    virtual string Handle(string request) = 0;
};

class AbstractHandler : public Handler {
private:
    Handler* next_handler_;

public:
    AbstractHandler() : next_handler_(nullptr) {
    }
    Handler* SetNext(Handler* handler) override {
        this->next_handler_ = handler;
        return handler;
    }
    string Handle(string request) override {
        if (this->next_handler_) {
            return this->next_handler_->Handle(request);
        }
        return {}; 
    }
};

class WizardHandler : public AbstractHandler {
public:
    string Handle(string request) override {
        if (request == "Staff" || request == "Grimoire") {  
            return "Wizard: I will protect your back with this " + request + ".\n";  
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};

class AssassinHandler : public AbstractHandler {
public:
    string Handle(string request) override {
        if (request == "Kunai" || request == "Blade") {  
            return "Assassin: I will kill your enemies with this " + request + ".\n";  
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};

class KnightHandler : public AbstractHandler {
public:
    string Handle(string request) override {
        if (request == "Sword" || request == "Shield") {  
            return "Knight: I will fight for your glory with this " + request + ".\n";  
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};

class ArcherHandler : public AbstractHandler {
public:
    string Handle(string request) override {
        if (request == "Bow" || request == "Crossbow") {  
            return "Archer: I will snipe anybody for you with this " + request + ".\n";  
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};

void ClientCode(Handler& handler) {
    vector<string> weapons = { "Staff", "Grimoire", "Kunai", "Blade", "Sword", "Shield", "Bow", "Crossbow", "Pan", "Broom" }; //u can change the strings
    for (const string& w : weapons) {
        cout << "King: Who would fight for me with this " << w << "?\n";
        const string result = handler.Handle(w);
        if (!result.empty()) {
            cout << "  " << result;
        }
        else {
            cout << "  " << w << " was left untouched.\n";
        }
    }
}

int main() {
    WizardHandler* wizard = new WizardHandler;
    AssassinHandler* assassin = new AssassinHandler;
    KnightHandler* knight = new KnightHandler;
    ArcherHandler* archer = new ArcherHandler;
    wizard->SetNext(assassin)->SetNext(knight)->SetNext(archer);

    cout << "Chain: Wizard > Assassin > Knight > Archer\n\n";
    ClientCode(*wizard);
    cout << "\n";
    cout << "Subchain: Assassin > Knight > Archer\n\n";
    ClientCode(*assassin);

    delete wizard;
    delete assassin;
    delete knight;
    delete archer;

    return 0;
}