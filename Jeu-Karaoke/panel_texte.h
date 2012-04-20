#ifndef PANEL_TEXTE_H
#define PANEL_TEXTE_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>

class Panel_Texte : public QWidget
{
    Q_OBJECT
    QLineEdit* saisie;
    QTextEdit* zone_paroles;


public:
    explicit Panel_Texte(QWidget *parent = 0);
    ~Panel_Texte();

signals:

public slots:

};

#endif // PANEL_TEXTE_H
