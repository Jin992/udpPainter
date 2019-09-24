#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <data.h>
#include <functional>
#include <QtDebug>

struct __attribute__((__packed__)) request2_from_df{
  uint8_t msgTypeId;
  int64_t timestamp;
  float azim;
 };

constexpr unsigned structSize = sizeof(request2_from_df);

class SimpleServer: public QObject
{
    Q_OBJECT
public:
    SimpleServer( int port = 5600 );
    ~SimpleServer();

    void processTheDatagram(QNetworkDatagram datagram);
    void setAzimutSetFunc(std::function<void(float)> func);
    void setErrorQntSetFunt(std::function<void(int)> func);
    void setPortGetFunc(std::function<int()> func);

public slots:
    void readPendingDatagrams();
    void socketConnect();

signals:
    void udpConnectedSignal();
    void udpDisconnectedSignal();


private:
    QUdpSocket *_socket;
    std::function<void(float)>  _set_new_azimut;
    std::function <void(int)>   _set_error_qnt;
    std::function<int()>        _get_port;
    int                         _port;
    int                         _errors;
};
