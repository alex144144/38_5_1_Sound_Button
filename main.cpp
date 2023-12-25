#include <QtGui/QtGui>
#include <QApplication>
#include <QObject>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

class ImageButton : public QPushButton {
    Q_OBJECT
public:
    ImageButton() = default;
    explicit ImageButton(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent *e) override;
public slots:
    void setUp();
    void setDown();
private:
    QPixmap mCurrentButtonPixmap;
    QPixmap mButtonDownPixmap;
    QPixmap mButtonUpPixmap;
};

ImageButton::ImageButton(QWidget *parent) {
    setParent(parent);
    setToolTip("PUSH");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mButtonUpPixmap = QPixmap(R"(F:\__C++\Skillbox\38_Advanced_Qt\_HW\38_5_1_Sound_Button\38_5_1_Sound_Button\_Pixmaps\red_button.png)");
    mButtonDownPixmap = QPixmap(R"(F:\__C++\Skillbox\38_Advanced_Qt\_HW\38_5_1_Sound_Button\38_5_1_Sound_Button\_Pixmaps\red_button_pushed.png)");
    mCurrentButtonPixmap = mButtonUpPixmap;
    setGeometry(mCurrentButtonPixmap.rect());
    connect(this, &QPushButton::clicked, this, &ImageButton::setDown);
}

void ImageButton::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentButtonPixmap);
}

QSize ImageButton::sizeHint() const {
    return QSize(100, 100);
}

QSize ImageButton::minimumSizeHint() const {
    return sizeHint();
}

void ImageButton::keyPressEvent(QKeyEvent *e) {
    setDown();
}

void ImageButton::setDown() {
    mCurrentButtonPixmap = mButtonDownPixmap;
    update();
    QTimer::singleShot(100, this, &ImageButton::setUp);
}

void ImageButton::setUp() {
    mCurrentButtonPixmap = mButtonUpPixmap;
    update();
}

int main(int argc, char **argv) {
    QApplication a(argc, argv);
    QString clickFilePath = "F:\\__C++\\Skillbox\\38_Advanced_Qt\\_HW\\38_5_1_Sound_Button\\38_5_1_Sound_Button\\_Sound\\Mouse_Click_00.mp3";
    auto* player = new QMediaPlayer(nullptr);
    player->setSource(QUrl::fromLocalFile(clickFilePath));
    auto* audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(75);
    ImageButton redButton(nullptr);
    redButton.setFixedSize(100, 100);
    redButton.move(1000, 400);

    QObject::connect(&redButton, &QPushButton::clicked, [&player](){
           player->play();
    });

    redButton.show();

    return QApplication::exec();
}

#include <main.moc>
