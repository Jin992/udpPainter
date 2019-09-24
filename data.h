#ifndef DATA_H
#define DATA_H
#include <cstdint>
#include <atomic>
#include<QObject>

class Data: public QObject
{
    Q_OBJECT
    Q_PROPERTY(float azimut READ azimut      WRITE setAzimut    NOTIFY azimutChanged)
    Q_PROPERTY(int errorQnt READ errorQnt    WRITE setErrorQnt  NOTIFY errorQntChanged)
    Q_PROPERTY(int port     READ port        WRITE setPort      NOTIFY portChanged)
    Q_PROPERTY(int connectionIndicator    READ connectionIndicator        WRITE setConnectionIndicator     NOTIFY connectionStatusChanged)
public:
    Data();
    void setAzimut(float azimut);
    float azimut() const;
    void setErrorQnt(int);
    void setPort(int);
    void setConnectionIndicator(bool status);
    int errorQnt() const;
    int port() const;
    bool connectionIndicator() const;

signals:
    void azimutChanged();
    void errorQntChanged();
    void startUdpSignal();
    void portChanged();
    void connectionStatusChanged();

public slots:
    void startUdp() {
        emit startUdpSignal();
    }
    void udpConnected();
    void udpDisconnected();

private:
    std::atomic<uint8_t> _msgTypeId;
    std::atomic<int64_t> _timestamp;
    std::atomic<int>     _error_qnt;
    std::atomic<float>   _azim;
    std::atomic<int>     _port;
    bool                 _connectionIndicator;
};

#endif // DATA_H
