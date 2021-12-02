#include <stdio.h>
#include <stdlib.h>
int k, n, m, i, j;
int *host_list, *router_list;

int main()
{
    // creating hosts
    printf(" Input total hosts: ");
    scanf("%d", &k);
    host_list = (int*)malloc(k*sizeof(int));
    for(i=0; i<k; i++)
       {
            j=i+1;
            // recall function creates host (waiting from other member)
            host_list[i]=j;
            printf(" Host-%d\n", host_list[i]);
        }
    // creating routers
    printf(" Input total routers: ");
    scanf("%d", &n);
    router_list = (int*)malloc(n*sizeof(int));
    for(i=0; i<n; i++)
       {
            j=i+1;
            // recall function creates router (waiting from other member)
            router_list[i]=j;
            printf(" Router-%d\n", router_list[i]);
        }
    // create two dimensions array about hosts and routers without connecting
    m = k+n; // total hosts and routers
    int connect_arr[m][m];
    for(i=0; i<m; i++)
    {
        for(j=0; j<m; j++)
            connect_arr[i][j]=0;
    }
    printf("\n");
    // connecting host and router
    int host_router, number;
    for(i=0; i<k; i++)
    {   number=i+1;
        printf(" Connect host %d with router: ", number);
        scanf("%d", &host_router);
        connect_arr[i][(k-1)+host_router] = 1;
    }
    printf("\n");
    // connecting routers and routers
    int router_router=0;
    for(i=0; i<n; i++)
    {   do
        {number=i+1;
        printf(" Connect router %d with router (if don't connect input (0)): ", number);
        scanf("%d", &router_router);
        if(router_router!=0)
            connect_arr[k+i][(k-1)+router_router] = 1;}
        while(router_router!=0);
    }
    // Print connection array
    printf("\n Connection array between hosts-routers and routers-routers:\n\n  ");
    for(i=0; i<k; i++) // print hosts at first line
        printf("  %d", host_list[i]);
    for(i=0; i<n; i++) // print routes at first line
        printf("  %d", router_list[i]);
    printf("\n");
    for(i=0; i<k; i++) // print hosts line
    { printf(" %d ", host_list[i]);
        for(j=0; j<m; j++)
            {printf(" %d ", connect_arr[i][j]);}
    printf("\n");
    }
    for(i=0; i<n; i++) // print routers line
    {
        printf(" %d ", router_list[i] );
        for(j=0; j<m; j++)
           {printf(" %d ", connect_arr[k+i][j]);}
    printf("\n");
    }
    free(host_list);
    free(router_list);
    return 0;
}
    