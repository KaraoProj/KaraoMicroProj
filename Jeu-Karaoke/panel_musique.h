#ifndef PANEL_MUSIQUE_H
#define PANEL_MUSIQUE_H

#include <QWidget>
#include <phonon/mediaobject.h>
#include <phonon/seekslider.h>
#include <phonon/audiooutput.h>
#include <phonon/volumeslider.h>
#include <QAction>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QState>
#include <QStateMachine>
#include <QtDebug>
#include <QLCDNumber>
#include <QTime>
#include <QToolBar>

class Panel_Musique : public QWidget
{
    Q_OBJECT
public:
    explicit Panel_Musique(QWidget *parent = 0);

    Phonon::SeekSlider *barreLecture;   // Barre de lecture
    Phonon::MediaObject *mediaObject;   // Permet de gérer la musique
    Phonon::AudioOutput *audioOutput;   // Permet d'écouter la musique
    Phonon::VolumeSlider *barreVolume;  //Barre de volume
    QAction *playAction;
    QAction *pauseAction;
    QAction *stopAction;
    QString source;
    QStateMachine * mac;
    QState * playState,*pauseState,*stopState;
    QLCDNumber *temps;

public:
    ~Panel_Musique();

    void setUI();           // Interface Utilisateur
    void setActions();      // Initilialise les QActions
    void setStateMachine();  // Initialise la machine à état
public slots:
    void debug();
    void tick(qint64 time);
/*
protected:
    void changeEvent(QEvent *e);
*/
};

#endif // PANEL_MUSIQUE_H
