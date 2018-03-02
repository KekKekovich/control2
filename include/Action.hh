//
// Created by idalov on 10.05.17.
//

#ifndef FINAL_ACTION_HH
#define FINAL_ACTION_HH

#include <G4VUserActionInitialization.hh>


class Scoring;

class Action: public G4VUserActionInitialization{
public:
    Action();
    ~Action() override;

    void Build() const override;

private:
    Scoring* scoring;
};

#endif //FINAL_ACTION_HH
