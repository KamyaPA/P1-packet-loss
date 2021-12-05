#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_node 100
#define max_distance 1000000000
int sum_node, sum_line, node_u, node_v, uv_line, l=0;
int connect_arr[max_node][max_node],send,receive;
int distance[max_node],trace[max_node],checkt2[max_node];
int *router_list;

void readf()
{
	FILE *fp;
	//open file
	fp=fopen("router.txt", "r");
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
}

void dijkstra()
{
    for(int i=1;i<=sum_node;i++)
    {
        distance[i]=max_distance;
        checkt2[i]=0;
        trace[i]=0;
    }
    distance[send]=0;
    trace[send]=0;
    int node_v=send,fmin;
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
}

void output()
{
    if(distance[receive]==max_distance) printf("NO PATH");
    else
    {
        printf("\n The shortest way: \n");
        printf(" %d km\n", distance[receive]);
        int path[max_node],d=0;
        d++;
        path[d]=receive;
        while(trace[receive]!=0)
        {
            receive=trace[receive];
            d++;
            path[d]=receive;
        }
        printf("\n The routing tree: \n");
        for(int i=d;i>0;i--)
        {
            printf(" Router-%d,",path[i]);}
        printf("\n");
        }
}

int main()
{
  readf();
  dijkstra();
  output();
}
    