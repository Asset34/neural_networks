#include "mainwindow.hpp"

#include <QStatusBar>
#include <QMenuBar>

#include <memory>
#include <tuple>

#include "../utills/convertions.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_network(nullptr)
{
    // Create signed image table manager
    m_tableManager = new SignedImageTableManager(3);

    // Create image drawer
    m_drawer = new ImageDrawerWidget(10, 10);
    m_drawer->setFixedWidth(400);
    m_drawer->setFixedHeight(400);

    // Create buttons
    m_toDrawerButton = new QPushButton(">>");
    m_toTableButton = new QPushButton("<<");

    // Create buttons layout
    m_buttonsLayout = new QVBoxLayout;
    m_buttonsLayout->setContentsMargins(0, 0, 0, 0);
    m_buttonsLayout->addStretch(1);
    m_buttonsLayout->addWidget(m_toDrawerButton);
    m_buttonsLayout->addWidget(m_toTableButton);
    m_buttonsLayout->addStretch(1);

    // Create main layout
    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->addWidget(m_tableManager);
    m_mainLayout->addLayout(m_buttonsLayout);
    m_mainLayout->addWidget(m_drawer);

    // Create status bar labels
    m_networkStatusLabel = new QLabel("NULL");
    m_networkStatusLabel->setFont(QFont("AnyStyle", 10));
    m_statusLabel = new QLabel("NULL");
    m_statusLabel->setFont(QFont("AnyStyle", 10));

    // Create status bar
    statusBar()->addPermanentWidget(m_networkStatusLabel, 1);
    statusBar()->addPermanentWidget(m_statusLabel);

    // Create menu actions
    m_learnNetworkAct = new QAction(tr("Learn"), this);
    m_recognizeSampleAct = new QAction(tr("Recognize"), this);

    // Create menu
    m_networkMenu = menuBar()->addMenu("Network");
    m_networkMenu->addAction(m_learnNetworkAct);
    m_sampleMenu = menuBar()->addMenu("Sample");
    m_sampleMenu->addAction(m_recognizeSampleAct);

    // Create widget
    QWidget *widget = new QWidget;
    widget->setLayout(m_mainLayout);
    setCentralWidget(widget);
    setContentsMargins(5, 5, 5, 5);

    // Create connections
    connect(m_toDrawerButton, &QPushButton::clicked, this, &MainWindow::sendToDrawer);
    connect(m_toTableButton, &QPushButton::clicked, this, &MainWindow::sendToTable);
    connect(m_learnNetworkAct, &QAction::triggered, this, &MainWindow::learn);
    connect(m_recognizeSampleAct, &QAction::triggered, this, &MainWindow::recognize);
}

MainWindow::~MainWindow()
{
    delete m_network;
}

void MainWindow::resetNetwork(size_t inputSize, size_t memorySize)
{
    delete m_network;
    m_network = new HammingNetwork(inputSize, memorySize);

    setNetworkStatus(inputSize, memorySize);
}

QString MainWindow::createResultString(const QVector<int> indexes)
{
    QString result;

    SignedImageListModel *model = m_tableManager->getModel();
    for (int index: indexes) {
        result.append(model->getSignAt(index) + " ");
    }

    return result;
}

void MainWindow::setNetworkStatus(size_t inputSize, size_t memorySize)
{
    m_networkStatusLabel->setText(m_networkStatusTemplate.arg(inputSize).arg(memorySize));
}

void MainWindow::setStatus(const QString &status)
{
    m_statusLabel->setText(status);
}

void MainWindow::sendToDrawer()
{
    std::shared_ptr<QImage> image = m_tableManager->getSelectedImage();

    if (image) {
        m_drawer->setImage(*image);
    }
}

void MainWindow::sendToTable()
{
    std::shared_ptr<QImage> image = std::make_shared<QImage>(m_drawer->getImage());

    m_tableManager->addSignedImage(image);
}

void MainWindow::learn()
{
    SignedImageListModel *model = m_tableManager->getModel();

    if (!model->rowCount()) {
        setStatus("Bad training set");
        return;
    }

    int inputSize = model->getImageAt(0).get()->width() *
                    model->getImageAt(0).get()->height();
    int memorySize = model->rowCount();

    resetNetwork(inputSize, memorySize);

    setStatus("Learning...");

    // Convert samples to bipolar vectors
    std::vector<std::vector<double>> trainingSet(memorySize);
    for (int i = 0; i < memorySize; i++) {
        trainingSet[i] = Convertions::toBipolarVector(*model->getImageAt(i));
    }

    // Learn
    bool result = m_network->learn(trainingSet);
    if (result) {
        setStatus("Network was successfully learned");
    }
    else {
        setStatus("Bad training set");
    }
}

void MainWindow::recognize()
{
    if (!m_network) {
        setStatus("Bad network");
        return;
    }

    setStatus("Recognizing...");

    //  Convert sample to bipolar vector
    std::vector<double> bipolar = Convertions::toBipolarVector(m_drawer->getImage());

    // Recognize
    std::vector<double> indexVec;
    bool result;
    std::tie(indexVec, result) = m_network->recognize(bipolar);

    if (!result) {
        setStatus("Bad sample");
        return;
    }

    QVector<int> indexes = Utills::getIndexes(indexVec);
    QString resultString = createResultString(indexes);

    setStatus("Result: " + resultString);
}
