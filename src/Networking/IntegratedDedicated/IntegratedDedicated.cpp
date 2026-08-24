#include "IntegratedDedicated.hpp"

void IntegratedDedicated::host(uint16_t port) {
    this->m_address.host = ENET_HOST_ANY; /* Bind the server to the default localhost.     */
    this->m_address.port = port; /* Bind the server to port 7777. */
    /* create a server */
    this->m_server = enet_host_create(
        &this->m_address,
        MAX_USERS,
        CHANNEL_COUNT,
        0,
        0
    );

    if (this->m_server == NULL) {
        this->m_server = nullptr; // just in case
        log::warn("Something went wrong with IntegratedDedicated::host(port: {}).", port);
        return;
    }

    log::info("Started hosting a server.");
}