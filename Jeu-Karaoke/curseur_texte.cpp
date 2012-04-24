#include "curseur_texte.h"

using namespace std;

Curseur_Texte::Curseur_Texte(QTextDocument * document) : QTextCursor(document)
{
}

Curseur_Texte::~Curseur_Texte(){

}

void Curseur_Texte::init(){
    cout<<"Avant init :" << this->position()<<endl;
    this->movePosition(QTextCursor::MoveOperation(1),QTextCursor::MoveMode(0),1);
    cout<<"Après init :" << this->position()<<endl;
    selectionner_mot();
}

void Curseur_Texte::selectionner_mot(){
    this->select(QTextCursor::SelectionType(0));
    cout<<"Mot selectionné :" << this->position()<< this->selectedText().toStdString() <<endl;
}

void Curseur_Texte::avancer(){
    QString mot_actuel,mot_precedent;

    selectionner_mot();
    mot_precedent=selectedText();
    setFormat_mot(1,mot_precedent);

    movePosition(QTextCursor::MoveOperation(18),QTextCursor::MoveMode(0),1);

    selectionner_mot();
    mot_actuel=selectedText();
    setFormat_mot(2,mot_actuel);

}

void Curseur_Texte::setFormat_mot(const int num_format,const QString& mot_a_formatter){
    // 1 : Emplacement mot normal
    // 2 : Emplacement mot selectionné

    selectedText().remove(0,mot_a_formatter.size());
    if(num_format==1){
        insertHtml("<p style='color:#A1B5F6;font-size:large;word-spacing:20'>" + mot_a_formatter + "</p>");
    }
    if(num_format==2){
        insertHtml("<p style='color:red;font-size:xx-large;word-spacing:50'>" + mot_a_formatter + "</p>");
    }


}
