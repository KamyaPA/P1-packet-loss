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
    char navn[10];
    int speed;

    router *connection;
    char packet_creation[80];
    char packet_receaving[80];
};
typedef struct host host;
