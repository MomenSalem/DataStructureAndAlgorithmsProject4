//Student name : Momen Musa Fuad Salem
//ID : 1200034
//Section : 2
//Doctor : Ahmad Abu Snaina
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>//library for is digit function && strcasecmp

//#include <limits.h>
//#include <stdbool.h>


struct City
{
    char city_name[30];
    struct City *parent;
    char visited;
    struct City *adjcent;
    //int distance;
};
typedef struct City City;
int numberofcities = 0;//the size of the graph and array generic data initially zero
int fileloaded = 0;
int cityindex = 0;
int pefore = 0;

int checkIfDigit(char theword[30]);
int indexOfCity(char citiesarray[numberofcities][30], char cityname[30]);
void Dijkstra(char cities[numberofcities][30], int graph[numberofcities][numberofcities], int src, int dis);

//there is no time to finish the project in final time !!!
int main()
{

    FILE *opencitiesfilec;//open cities file for determine the number of cities
    opencitiesfilec = fopen("cities.txt", "r");
    if(opencitiesfilec == NULL)//if the file name is false exit the system and print message
    {
        printf("Sorry, The cities file doesn't exist(must be cities.txt [c -> small letter])");
        return 0;
    }
    char line[200];
    char *token = NULL;
    char cityName[30];
    while(fgets(line, 200, opencitiesfilec) != NULL)//find the number of cities (to create the graph)
    {
        token = strtok(line, "\t");
        if(strcmp(cityName,token) != 0)//we want the number of unique city without repetition
        {
            numberofcities++;
        }
        strcpy(cityName, token);
    }
    if(numberofcities == 0)
    {
        printf("Sorry, There is no cities (the size of array must be greater than zero)\n");
        exit(0);
    }
    fclose(opencitiesfilec);
    char cities[numberofcities][30];//array to save the city name and find the index of it, 30 the maximum number of character for the city name
    int graph[numberofcities][numberofcities];
    int menuchoice = 0;
    while(menuchoice != 4)
    {
        printf("Please choose one number of the following list below :\n");
        printf("1. Load the cities file and construct the graph\n2. Enter source city\n");
        printf("3. Enter destination city\n");
        printf("4. Exit and save step 4 to file (shortest_path.txt)\n");
        char checkdigit[30];
        scanf("%s",checkdigit);
        if(!checkIfDigit(checkdigit))
        {
            menuchoice = atoi(checkdigit);
            switch (menuchoice)
            {
            case 1:
            {
                if(fileloaded == 0)
                {
                    fileloaded = 1;//the file is visited
                    for(int k = 0 ; k < numberofcities ; k++)
                    {
                        for(int j = 0 ; j < numberofcities ; j++)
                            graph[k][j] = 0;//the initial value of all distances in the graph is zero
                    }
                    FILE *opencityfile;
                    opencityfile = fopen("cities.txt", "r");
                    char cityname[30];
                    char linefile[200];
                    token = NULL;
                    int i = 0;//for the index of city
                    while(fgets(linefile, 200, opencityfile) != NULL)//find the number of cities (to create the graph)
                    {
                        token = strtok(linefile, "\t");
                        if(strcmp(cityname,token) != 0 && i < numberofcities)//we want the number of unique city without repetition
                        {
                            strcpy(cities[i], token);//loop to construct the cities array
                            i++;
                        }
                        strcpy(cityname, token);
                    }
                    FILE *opencityfileG;//G to construct the distance between the cities
                    opencityfileG = fopen("cities.txt", "r");
                    char linefileG[200];
                    token = NULL;
                    while(fgets(linefileG, 200, opencityfileG) != NULL)//find the number of cities (to create the graph)
                    {
                        char cityname1[30];//the name of the first city(source)
                        int indexC1;//the index of the first city in the graph(row)
                        char cityname2[30];//the name of the second city(destination)
                        int indexC2;//the index of the second city in the graph(column)
                        int distance;
                        token = strtok(linefileG, "\t");
                        strcpy(cityname1, token);
                        indexC1 = indexOfCity(cities, cityname1);
                        token = strtok(NULL, "\t");
                        strcpy(cityname2, token);
                        indexC2 = indexOfCity(cities, cityname2);
                        token = strtok(NULL, "\t");
                        distance = atoi(token);
                        graph[indexC1][indexC2] = distance;
                    }
                    printf("The city file is loaded properly and the graph is constructed\n");
                }
                else
                {
                    printf("Sorry, the cities file is already loaded\n");
                }
                break;
            }
            case 2:
            {
                char cityname[30];
                printf("Please enter the source city name (from city) :\n");
                getchar();
                fgets(cityname, 30, stdin);
                cityname[strlen(cityname) - 1] = '\0';
                int index;//check if the city source exist
                index = indexOfCity(cities, cityname);
                if(index >= 0)
                {
                    cityindex = index;
                    printf("The Dijkstra process is done for city %s\n", cityname);
                }
                else
                    printf("Sorry, The city (%s) does not exist in the file (in the graph)!!\n", cityname);

                break;
            }
            case 3:
            {
                char cityname[30];
                printf("Please enter the destination city name (To city) :\n");
                getchar();
                fgets(cityname, 30, stdin);
                cityname[strlen(cityname) - 1] = '\0';
                int index;//check if the city source exist
                index = indexOfCity(cities, cityname);
                if(index >= 0)
                {
                    Dijkstra(cities, graph, cityindex, index);
                }
                //the only error is that the system can not print the path **
                else
                    printf("Sorry, The city (%s) does not exist in the file (in the graph)!!\n", cityname);

                break;
            }
            case 4:
                {
                /*FILE *writecitiessfile;
                writecitiessfile = fopen("shortest_path.txt", "w");
                //printCities();
                fclose(writecitiessfile);
                break;*/
                }
            default :
            {
                printf("You must choose a number between 1 - 4 only !!\n");
            }
            }
        }


    }


    return 0;
}
int checkIfDigit(char theword[30])//function to check if the word is digit or no
{
    for(int i = 0 ; i < strlen(theword) ; i++)
    {
        if(!isdigit(theword[i]))
        {
            printf("You Must enter a digit only!\n");
            return 1;
        }
    }
    return 0;
}
int indexOfCity(char citiesarray[numberofcities][30], char cityname[30])//function to return the index of a city
{
    for(int i = 0 ; i < numberofcities ; i++)
    {
        if(strcasecmp(citiesarray[i], cityname) == 0)
            return i;
    }
    return -1;
}
int minDis(int result[], char con[])
{
    int min_index;
    int smaller = INT_MAX;
    for (int i = 0; i < numberofcities; i++)
    {
        if (con[i] == 'f' && result[i] <= smaller)
        {
            smaller = result[i];
            min_index = i;
        }
    }

    return min_index;
}
void Dijkstra(char cities[numberofcities][30], int graph[numberofcities][numberofcities], int citysource, int citydis)
{
    char visited[numberofcities];
    int dis[numberofcities];
    for (int i = 0; i < numberofcities; i++)
    {
        visited[i] = 'f';
        dis[i] = INT_MAX;
    }
    dis[citysource] = 0;
    for (int i = 0; i < numberofcities - 1; i++)
    {
        int minimum = minDis(dis, visited);
        visited[minimum] = 't';
        for (int j = 0; j < numberofcities; j++)
        {
            if (visited[j] == 'f' && graph[minimum][j] && dis[minimum] != INT_MAX
                    && dis[minimum] + graph[minimum][j] < dis[j])
            {
                pefore = minimum;
                dis[j] = dis[minimum] + graph[minimum][j];
            }
        }
    }
    printf("From %s to %s is = ", cities[citysource], cities[citydis]);
    printf("%d\n", dis[citydis]);
    FILE *writecitiessfile;
    writecitiessfile = fopen("shortest_path.txt", "w");
    fprintf(writecitiessfile, "The longest path from %s ", cities[citysource]);
    for(int i = 0 ; i < numberofcities ; i++)
    {
       fprintf(writecitiessfile, "to %s is = %d\n", cities[i], dis[i]);
    }

    fclose(writecitiessfile);
}
