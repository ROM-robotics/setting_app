#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QScrollArea>
#include <QTextEdit>
#include <QProgressBar>
#include <QTimer>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "networkmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onModeToggleClicked();
    void onRefreshWifiClicked();
    void onConnectionStatusChanged(bool connected);
    void onWifiStatusReceived(const QString &ssid, const QString &status, const QString &ipAddress);
    void onWifiNetworksScanned(const QStringList &networks);
    void onWifiNetworkChanged(bool success, const QString &message);
    void onNetworkError(const QString &error);
    void showVirtualKeyboard();
    void hideVirtualKeyboard();
    void onKeyboardKeyPressed(const QString &key);
    void updateConnectionIndicator();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void setupUI();
    void setupStyle();
    void setupVirtualKeyboard();
    void createKeyboardButton(const QString &text, QGridLayout *layout, int row, int col, int colspan = 1);
    void updateModeDisplay();
    void updateWifiDisplay();
    void showStatusMessage(const QString &message, bool isError = false);

    Ui::MainWindow *ui;
    NetworkManager *m_networkManager;
    
    // UI Components
    QWidget *m_centralWidget;
    QVBoxLayout *m_mainLayout;
    
    // Header
    QFrame *m_headerFrame;
    QLabel *m_titleLabel;
    QLabel *m_connectionIndicator;
    
    // Mode Selection
    QFrame *m_modeFrame;
    QPushButton *m_modeToggle;
    QLabel *m_modeLabel;
    
    // Connection Status
    QFrame *m_statusFrame;
    QLabel *m_statusLabel;
    QPushButton *m_refreshButton;
    
    // WiFi Information
    QFrame *m_wifiFrame;
    QLabel *m_wifiSSIDLabel;
    QLabel *m_wifiStatusLabel;
    QLabel *m_wifiIPLabel;
    
    // Status Messages
    QTextEdit *m_logTextEdit;
    
    // Virtual Keyboard
    QFrame *m_keyboardFrame;
    QScrollArea *m_keyboardScrollArea;
    QGridLayout *m_keyboardLayout;
    QLineEdit *m_currentInput;
    
    // Animation and effects
    QTimer *m_connectionTimer;
    QPropertyAnimation *m_fadeAnimation;
    QGraphicsOpacityEffect *m_opacityEffect;
    
    // State
    bool m_keyboardVisible;
};
#endif // MAINWINDOW_H
