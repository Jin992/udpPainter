#include <udpreceiver.h>

SimpleServer::SimpleServer( int port) : QObject (0) ,_socket(new QUdpSocket(this)), _port(port)
{
    connect(_socket,  &QUdpSocket::readyRead,
               this, &SimpleServer::readPendingDatagrams);

    connect(_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
          [=](QAbstractSocket::SocketError socketError){
            emit udpDisconnectedSignal();
        qDebug() << socketError; });

}


SimpleServer::~SimpleServer()
{}

void SimpleServer::socketConnect() {
    _socket->bind(QHostAddress::Any, _get_port());
    emit udpConnectedSignal();
}


void SimpleServer::processTheDatagram(QNetworkDatagram datagram){
    if (datagram.data().size() == structSize) {
        if (datagram.data().size() == structSize) {
            struct request2_from_df *received_struct = reinterpret_cast<struct request2_from_df *>(datagram.data().data());
            if (received_struct->msgTypeId == 0x30) {
                if (received_struct->azim * 180/3.14 < 0)
                    _set_new_azimut(360 + (received_struct->azim * 180/3.14));
                else
                    _set_new_azimut(received_struct->azim * 180/3.14);
            } else {
                _set_error_qnt(++_errors);
            }
        } else {
            _set_error_qnt(++_errors);
        }
    }
}

void SimpleServer::setAzimutSetFunc(std::function<void(float)> func) {
   _set_new_azimut = func;
}

void SimpleServer::setErrorQntSetFunt(std::function<void(int)> func) {
    _set_error_qnt = func;
}

void SimpleServer::setPortGetFunc(std::function<int()> func) {
    _get_port = func;
}

void SimpleServer::readPendingDatagrams()
{
    while (_socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = _socket->receiveDatagram();
        processTheDatagram(datagram);
    }
}


