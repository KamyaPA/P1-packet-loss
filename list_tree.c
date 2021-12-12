
// Funktion får file (txt), som konfigurerer netværk
// og return listetræ i path[100] array og antal router 
// i listetræ i router_path variabel
// kald på funktion: list_tree(path, &router_path, text);

int path[100]; // array consists list of the tree
int router_path; // total router in list of the tree
char text[]="router.txt"; // network configuration file

int list_tree(int *path, int *router_path, char *file)
{
    #define max_node 100 // total nodes
    #define max_distance 1000000000 // it means that don't connect
    int sum_node, sum_line, node_u, node_v, uv_line, l=0;
    int connect_arr[max_node][max_node],send,receive;
    int distance[max_node],trace[max_node],checkt2[max_node];
    int *router_list;

    /* Read the file "router.txt" that consists of router and connect between them,
        sender and receive */
	FILE *fp;
	//open file
	fp=fopen(file, "r");
	if(fp==NULL)
    {
		printf(" Error creating or pening file!");
		exit(1);
	}
	while(!feof(fp))
        if(l<2)
        {
            while(l<1)
            {
                fscanf(fp,"%d%d", &sum_node, &sum_line);
                for(int i=1;i<=sum_node;i++)
                    for(int j=1;j<=sum_node;j++) connect_arr[i][j]=0;
                router_list = (int*)malloc(sum_node*sizeof(int));
                printf("\n List routers: \n");   
                for(int i=0; i<sum_node; i++)
                {
                    int j=i+1;
                    router_list[i]=j;
                    printf(" Router-%d\n", router_list[i]);
                }
                l++;
            }
            while(l<2)
            {
                fscanf(fp,"%d%d", &send, &receive);
                printf("\n Send packets: Router-%d and receive packets: Router-%d\n", send, receive);
                l++;
            }
        }
        else
        {   
            fscanf(fp," %d%d%d", &node_u, &node_v, &uv_line);
            connect_arr[node_u][node_v]=uv_line;
            connect_arr[node_v][node_u]=connect_arr[node_u][node_v];
        }
        printf("\n Conneting array between routers: \n");
        printf("   ");
        for(int i=0; i<sum_node; i++) 
            printf(" %4d", router_list[i]);
        printf("\n");
        for(int i=1;i<=sum_node;i++)
        {
            printf(" %2d", router_list[i-1]);
            for(int j=1;j<=sum_node;j++)
                printf(" %4d", connect_arr[i][j]);
            printf("\n");
        }
    fclose(fp);
    free(router_list);

    // Dijkstra algorithm
    for(int i=1;i<=sum_node;i++)
    {
        distance[i]=max_distance;
        checkt2[i]=0;
        trace[i]=0;
    }
    distance[send]=0;
    trace[send]=0;
    node_v=send;
    int fmin;
    while(node_v!=receive)
    {
    //find node v
        fmin=max_distance;
        for(int i=1;i<=sum_node;i++)
            if(checkt2[i]==0 && fmin>distance[i])
            {
                fmin=distance[i];
                node_v=i;
            }
        if(fmin==max_distance) break;
    //Delete v from T2
        checkt2[node_v]=1;
    //Optimal T2
        for(int i=1;i<=sum_node;i++)
            if(connect_arr[node_v][i]>0 && distance[i]>distance[node_v]+connect_arr[node_v][i])
            {
                distance[i]=distance[node_v]+connect_arr[node_v][i];
                trace[i]=node_v;
            }
    }

    // Print list tree
    if(distance[receive]==max_distance) printf("NO PATH");
    else
    {
        printf("\n The shortest way: \n");
        printf(" %d km\n", distance[receive]);
        int path1[max_node];
        int d=0;
        d=0;
        d++;
        path1[d]=receive;
        while(trace[receive]!=0)
        {
            receive=trace[receive];
            d++;
            path1[d]=receive;
        }
        *router_path=d;
        printf("\n The routing tree: \n");
        for(int i=0;i<d;i++)
        {
            path[i]=path1[(d-i)];
            printf(" Router-%d,",path[i]);}
        printf("\n");
        }
}



    