#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);
  m_gl=new  NGLScene(this);
  m_ui->s_mainWindowGridLayout->addWidget(m_gl,0,0,2,2);
  connect(m_ui->togglePlay, SIGNAL(clicked()), m_gl, SLOT(playAndPause()));
  connect(m_ui->addFixedButton, &QPushButton::clicked,
          [=]()
          {
            m_gl->addFixedParticle(m_ui->fixedComboBox->currentText());
          });
  connect(m_ui->removeFixedButton, &QPushButton::clicked,
          [=]()
          {
            m_gl->removeFixedParticle(m_ui->fixedComboBox->currentText());
          });
  connect(m_ui->createMeshButton, &QPushButton::clicked,
          [=]()
          {
            m_gl->createMesh(m_ui->cWidthSpin->value(),
                     m_ui->cHeightSpin->value(),
                     m_ui->pWidthSpin->value(),
                     m_ui->pHeightSpin->value(),
                     m_ui->massSpin->value());
          });
  connect(m_ui->updateButton, &QPushButton::clicked,
          [=]()
          {
            m_gl->updateParameters(
        static_cast<float>(m_ui->gravitySpin->value()),
        static_cast<float>(m_ui->windXSpin->value()),
        static_cast<float>(m_ui->windYSpin->value()),
        static_cast<float>(m_ui->windZSpin->value()),
        m_ui->iterationsSpin->value());
  });
  connect(m_ui->resetButton, &QPushButton::clicked,
          [=]()
          {
            m_ui->gravitySpin->setValue(-9.81);
            m_ui->windXSpin->setValue(0.0);
            m_ui->windYSpin->setValue(0.0);
            m_ui->windZSpin->setValue(0.0);
            m_ui->iterationsSpin->setValue(1000);
            m_gl->updateParameters(-9.81, 0.0, 0.0, 0.0, 1000);
          });

};

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::keyPressEvent(QKeyEvent *_event)
{
		switch(_event->key())
		{
		case Qt::Key_S : m_gl->playAndPause(); break;
		case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
		}
}
