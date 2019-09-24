#include "data.h"

Data::Data():_azim(0.0), _error_qnt(0), _port(5600), _connectionIndicator(false)
{}

void Data::setAzimut(float azimut) {
    if (_azim == azimut)
        return;
    _azim.exchange(azimut);
    emit azimutChanged();
}

float Data::azimut() const {
    return _azim.load();
}

void Data::setErrorQnt(int qnt) {
    if (_error_qnt == qnt)
        return;
    _error_qnt.exchange(qnt);
    emit errorQntChanged();
}

int Data::errorQnt() const {
    return _error_qnt.load();
}

int Data::port() const {
    return _port.load();
}

void Data::setPort(int port) {
    if (_port == port)
        return;
    _port.exchange(port);
    emit portChanged();
}

void Data::setConnectionIndicator(bool status) {
    if (_connectionIndicator == status)
        return;
    _connectionIndicator = status;
    emit connectionStatusChanged();
}

bool Data::connectionIndicator() const {
    return _connectionIndicator;
}

void Data::udpConnected() {
    setConnectionIndicator(true);
}

void Data::udpDisconnected() {
    setConnectionIndicator(false);
}
