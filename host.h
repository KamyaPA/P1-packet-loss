#define HOST_NAME_SIZE 15
#define HOST_PACKET_HOLDER_SIZE 80

struct packet{
    int id;
};
typedef struct packet packet;

struct router{
    int i;
};
typedef struct router router;

struct host{
    int id;
    char name[HOST_NAME_SIZE];
    int speed;

    router *connection;
    char packet_creation[HOST_PACKET_HOLDER_SIZE];
    char packet_receaving[HOST_PACKET_HOLDER_SIZE];
};
typedef struct host host;

void host_receave_package(host *source);
host *host_create(int id, char name[HOST_NAME_SIZE], int speed);
void host_connect(host *source, router *destination);
packet create_packet();
