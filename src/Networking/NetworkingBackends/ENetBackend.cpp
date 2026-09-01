#include "ENetBackend.hpp"

void ENetBackend::sendMessageToLobby(flatbuffers::Offset<CTSerialize::MessageHeader> out) {

}

void ENetBackend::recvMessages() {
    if (!m_fullyInitialized) {
        log::debug("ENet polled messages while not fully initialized");
        return;
    }

    while (enet_host_service(this->m_client, &this->m_event, 0) > 0) {
        // parse data
        break;
    }
}

// TODO: Finish!
ENetBackend::~ENetBackend() {
    if (!this->m_fullyInitialized) {
        return;
    }
    log::info("Disconecting from ENet backend");
    enet_peer_disconnect(this->m_peer, 0);

    this->m_peer = nullptr;
    this->m_fullyInitialized = false;
}

void ENetBackend::spawnBackend(std::string host, uint16_t port) {
    async::spawn([host, port] -> arc::Future<Result<ENetBackend*>> {
        auto handle = async::runtime().spawnBlocking<Result<ENetBackend*>>([host, port] -> Result<ENetBackend*> {
            // Setup code
            ENetBackend* backend = new ENetBackend;
            backend->m_client = enet_host_create(
                CLIENT_HOST, // create a client host
                1, // only allow 1 outgoing connection
                CHANNEL_COUNT,
                0, // assume any amount of incoming bandwidth
                0 // assume any amount of outgoing bandwidth
            );

            if (backend->m_client == NULL) {
                delete backend;
                return Err("An error occurred while trying to create an ENet client host");
            }

            enet_address_set_host(&backend->m_address, host.c_str());
            backend->m_address.port = port;

            // Initiate the connection
            backend->m_peer = enet_host_connect(backend->m_client, &backend->m_address, CHANNEL_COUNT, 0);
            if (backend->m_peer == NULL) {
                delete backend;
                return Err("No available peers for initiating an ENet connection");
            }

            /* Wait up to 5 seconds for the connection attempt to succeed. */
            if (enet_host_service(backend->m_client, &backend->m_event, 5000) > 0 && backend->m_event.type == ENET_EVENT_TYPE_CONNECT) {
                log::info("ENet Connection succeeded");
            } else {
                /* Either the 5 seconds are up or a disconnect event was */
                /* received. Reset the peer in the event the 5 seconds   */
                /* had run out without any significant event.            */
                enet_peer_reset(backend->m_peer);
                log::warn("ENet Connection failed");
                delete backend;
                return Err("Client timed out");
            }


            // todo: finish
            return Ok(backend);

        });

        Result<ENetBackend*> value = co_await handle;
        co_return value;
    }
    );
}

// C99 my beautiful
