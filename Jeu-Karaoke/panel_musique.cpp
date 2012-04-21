#include "panel_musique.h"

Panel_Musique::Panel_Musique(QWidget *parent) :
    QWidget(parent)
{


    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::blue);
    setPalette(Pal);
    setAutoFillBackground(true);


    // Gestion du fichier audio
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory,this);
    mediaObject = new Phonon::MediaObject(this);

    mediaObject->setTickInterval(1000); // Emission d'un tick toutes les secondes
    connect(mediaObject, SIGNAL(tick(qint64)),this, SLOT(tick(qint64))); // On va passer le temps écoulé (tick) à l'attribut "temps"

    source = "Sound/1995_LaSuite.wav";
    mediaObject->setCurrentSource(source);
    titre = "La Suite";
    artiste = "1995";

    Phonon::createPath(mediaObject,audioOutput);    //Relie le gestionnaire du son au diffuseur de son

    setActions();
    setStateMachine();
    setUI();
}

Panel_Musique::~Panel_Musique()
{
    //delete ui;
}

void Panel_Musique::tick(qint64 time){
    QTime displayTime(00, ( time / 60000 ) % 60, ( time / 1000 ) % 60,0);
    temps->display(displayTime.toString("mm:ss"));
}

void Panel_Musique::setActions(){

    playAction = new QAction(tr("Play"),this);
    playAction->setDisabled(false);
    pauseAction = new QAction(tr("Pause"),this);
    pauseAction->setDisabled(false);
    stopAction = new QAction(tr("Stop"),this);
    stopAction->setDisabled(false);

}

void Panel_Musique::setStateMachine(){

    mac = new QStateMachine() ;
    playState = new QState();
    pauseState = new QState();
    stopState = new QState();

    playState->addTransition(pauseAction,SIGNAL(triggered()),pauseState);
    playState->addTransition(stopAction,SIGNAL(triggered()),stopState);

    pauseState->addTransition(playAction,SIGNAL(triggered()),playState);
    pauseState->addTransition(stopAction,SIGNAL(triggered()),stopState);

    stopState->addTransition(playAction,SIGNAL(triggered()),playState);
    stopState->addTransition(pauseAction,SIGNAL(triggered()),pauseState);

    mac->addState(playState);
    mac->addState(pauseState);
    mac->addState(stopState);
    mac->setInitialState(pauseState);

    QObject::connect(playState, SIGNAL(entered()), mediaObject, SLOT(play()));
    QObject::connect(pauseState, SIGNAL(entered()), mediaObject, SLOT(pause()));
    QObject::connect(stopState, SIGNAL(entered()), mediaObject, SLOT(stop()));

    mac->start();
}

void Panel_Musique::debug(){
    qDebug() <<"DEBUG";

}

void Panel_Musique::setUI(){

    QHBoxLayout * principalLayout= new QHBoxLayout;     // Layout principal

    QVBoxLayout *  interactiveLayout = new QVBoxLayout; // Layout d'interaction avec boutons, volume et barre de lecture

    barreLecture = new Phonon::SeekSlider(this);
    barreLecture->setMediaObject(mediaObject);          // On relie la barre de lecture au mediaobject

    QHBoxLayout * controlLayout = new QHBoxLayout;      // Boutons + Volume

    QToolBar * barreControle = new QToolBar;            // Barre d'outils Pause, Play, Stop
    barreControle->addAction(playAction);
    barreControle->addAction(pauseAction);
    barreControle->addAction(stopAction);

    barreVolume = new Phonon::VolumeSlider(this);
    barreVolume->setAudioOutput(audioOutput);

    controlLayout->addWidget(barreControle);
    controlLayout->addWidget(barreVolume);

    interactiveLayout->addWidget(barreLecture);
    interactiveLayout->addLayout(controlLayout);

    QVBoxLayout* informationLayout= new QVBoxLayout;    // Barre d'information : Titre, temps écoulé

    QLabel* titreLabel = new QLabel(titre);                 // Titre
    QLabel* artisteLabel = new QLabel(artiste);             // Artiste
    temps = new QLCDNumber;
    temps->display("GO");

    informationLayout->addWidget(titreLabel);
    informationLayout->addWidget(artisteLabel);
    informationLayout->addWidget(temps);

    principalLayout->addLayout(interactiveLayout);
    principalLayout->addLayout(informationLayout);

    this->setLayout(principalLayout);
}
