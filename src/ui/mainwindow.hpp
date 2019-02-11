#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>
#include <QPushButton>

#include <QMenu>
#include <QAction>
#include <QActionGroup>

#include <neural_networks/ann_core/neuralnetwork.hpp>

#include <ui/SignedImageList_view_model/signedimagetablemanager.hpp>
#include <ui/image_drawer/imagedrawerwidget.hpp>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString buildResultString(const QVector<int> indexes);

    void setNetworkStatus();
    void setNetworkStatus(size_t inputSize, size_t memorySize);
    void setOperationStatus(const QString &status);

    QHBoxLayout *m_mainLayout;
    QVBoxLayout *m_buttonsLayout;

    QPushButton *m_toDrawerButton;
    QPushButton *m_toTableButton;

    QLabel *m_networkStatusLabel;
    QLabel *m_operationStatusLabel;

    QMenu *m_networkMenu;
    QMenu *m_sampleMenu;

    QAction *m_hammingNetworkAct;
    QAction *m_hebbianNetworkAct;
    QAction *m_learnNetworkAct;
    QAction *m_recognizeSampleAct;

    QActionGroup *m_networksActGroup;

    SignedImageTableManager *m_tableManager;
    ImageDrawerWidget *m_drawer;

    QString m_networkStatusTemplate = "(input: %1, memory: %2)";

    NeuralNetwork *m_network;

private slots:
    void sendToDrawer();
    void sendToTable();

    void learn();
    void recognize();

    void setHammingNetwork();
    void setHebbianNetwork();
};

#endif // MAINWINDOW_HPP
