#include "champ_saisie.h"
#include <iostream>

using namespace std;

Champ_Saisie::Champ_Saisie(QWidget *parent) : QLineEdit(parent){

    validationAction = new QAction("Valider",this);
    validationAction->setEnabled(true);
    validationAction->setShortcut(tr("Ctrl+P"));

    QObject::connect(validationAction,SIGNAL(QLineEdit::returnPressed()), this, SLOT(validationMot()));
}

Champ_Saisie::~Champ_Saisie(){
}

void Champ_Saisie::validationMot(){

    cout << "Position curseur: " << this->cursorPosition() << endl;
    this->selectAll();
    cout << "Position curseur (après selection): " << this->cursorPosition() << endl;
    cout << "[Le mot tapé est: " << selectedText().toStdString() << "]" << endl;
}
