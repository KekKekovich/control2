
#include "../include/Action.hh"
#include "../include/PrimaryPat.hh"


Action::Action(){


}

Action::~Action(){

    delete scoring;
}

void Action::Build()const {
    SetUserAction(new PrimaryPat);

}

