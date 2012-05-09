#include "curseur_texte.h"

using namespace std;

Curseur_Texte::Curseur_Texte(QTextDocument * document) : QTextCursor(document)
{
    this->init();
}

Curseur_Texte::~Curseur_Texte(){

}

void Curseur_Texte::dire_position(){
    cout<<"Position :" << this->position()<<endl;
}
void Curseur_Texte::init(){

    this->movePosition(QTextCursor::MoveOperation(1),QTextCursor::MoveMode(0),1);

    dire_position();

}

void Curseur_Texte::selectionner_mot(){
    this->select(QTextCursor::SelectionType(0));
    dire_position();
}
void Curseur_Texte::selectionner_ligne(){

    this->select(QTextCursor::SelectionType(1));
    dire_position();
}

