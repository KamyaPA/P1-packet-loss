#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc_check.h"

#define max_node 100 // total nodes
#define max_distance 1000000000 // it means that node isn't connected

int list_tree(char *read_file, char *save_file)
{   
    int path[100];
    int router_path[100];
    int sum_node, sum_line, node_u, node_v, uv_line, l=0;
    int connect_arr[max_node][max_node],send,receive;
    int distance[max_node],trace[max_node],checkt2[max_node];
    int *router_list;

/* Read the file that consists of router and connect between them,
   sender and receive */
	FILE *fp;   /*read file*/
    FILE *p;    /*save file*/
	//open file
	fp=fopen(read_file, "r"); 
    p=fopen(save_file, "w");
	if(fp==NULL)
    {
		printf(" Error creating or pening file!");
		exit(1);
	}
	while(!feof(fp)){
        if(l<1)
        {
            fscanf(fp,"%d%d", &sum_node, &sum_line);
            for(int i=1;i<=sum_node;i++)
                for(int j=1;j<=sum_node;j++) connect_arr[i][j]=0;
            router_list = (int*)malloc_check(sum_node*sizeof(int));
            for(int i=0; i<sum_node; i++)
            {
                int j=i+1;
                router_list[i]=j;
            }
            l++;
        }
        else
        {   
            fscanf(fp," %d%d%d", &node_u, &node_v, &uv_line);
            connect_arr[node_u][node_v]=uv_line;
            connect_arr[node_v][node_u]=connect_arr[node_u][node_v];
        }
    }
    fclose(fp);
    free(router_list);

/* Dijkstra algorithm */
    for(int i = 1; i<=sum_node; i++)
        for(int j=1; j<=sum_node; j++)
        {  
            send=i; receive=j;
            if(send<=sum_node && receive<=sum_node && send!=0 && receive!=0)
            {
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
                {   //find node v
                    fmin=max_distance;
                    for(int i=1;i<=sum_node;i++)
                        if(checkt2[i]==0 && fmin>distance[i])
                        {
                            fmin=distance[i];
                            node_v=i;
                        }
                    if(fmin==max_distance) break;
                    //Delete v from L2
                    checkt2[node_v]=1;
                    //Optimize L2
                    for(int i=1;i<=sum_node;i++)
                        if(connect_arr[node_v][i]>0 && distance[i]>distance[node_v]+connect_arr[node_v][i])
                        {
                            distance[i]=distance[node_v]+connect_arr[node_v][i];
                            trace[i]=node_v;
                        }
                }

            /* Print list tree to file*/
                if(distance[receive]==max_distance) printf("NO PATH");
                else
                {
                    if(i!=j){
                        int path1[max_node];
                        int d=0;
                        d++;
                        path1[d]=receive;
                        while(trace[receive]!=0)
                        {
                            receive=trace[receive];
                            d++;
                            path1[d]=receive;
                        }
                        *router_path=d;
                        for(int i=0;i<d;i++)
                        {
                            path[i]=path1[(d-i)];
                            fprintf(p, "%d ", path[i]);
                        }
                        fprintf(p, "\n");
                    }
                }
            }
        }
    fclose(p);
    return 0;
}



    
