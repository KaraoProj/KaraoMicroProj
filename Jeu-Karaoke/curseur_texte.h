#ifndef CURSEUR_TEXTE_H
#define CURSEUR_TEXTE_H

#include <QTextCursor>
#include <iostream>

class Curseur_Texte : public QTextCursor
{
public:
    explicit Curseur_Texte(QTextDocument * document=0);

    virtual void init();
    virtual void selectionner_mot();
    virtual void avancer();

    virtual void setFormat_mot(const int, const QString&);

signals:

public slots:

};

#endif // CURSEUR_TEXTE_H
