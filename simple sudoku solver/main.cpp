#include <iostream>
#include <fstream>
using namespace std;
void GETdata(int [][9]);
void del(int [][9] , int [9] , int  , int );
void crossHaching(int [][9] ,int , int  , int );
void showSodo(int [][9]);
void setupCH(int [][9]);
void setup(int [][9]);
void put(int [][9], int  , int  , int  );
bool is_solved(int [][9] );
int main()
{
    int adad[9][9];
    GETdata(adad);
    showSodo(adad);
    // counter for controlling of number of searching for answers
    int counter = 0;
    bool finish = true;
    while(is_solved(adad)){
        if(counter == 50){
            finish = false;
            break;
        }
        //setupCH is cross hatching algorithmn
        setupCH(adad);
        //setup is search answer with deleting number that used in square, row, and column
        setup(adad);
        counter++;
    }
    if(finish)
        cout << "I SOLVE It :)"<<endl;
    else
        cout << "I CANT SOLVE IT :("<<endl;
    showSodo(adad);
    return 0;
}

void GETdata(int adad[9][9])
{
    //this function is for getting sudoku input
    string get;
    fstream getData ("Data.txt");
    // j for Row and k for cloumn
    int j = 0;
    while(getline(getData , get))
    {
        int k = 0;
        for(int i=0;i<get.size();i++)
        {
            if(get[i] == ' ')
                continue;
            else if( 48<=get[i] && get[i] <= 57)
            {
                adad[j][k] = (int)get[i] - 48;
                k++;
            }
            else{
                system("cls");
                cout << "YOU ENTER WRONG PLEASE CHECK Data";
                exit(1);
            }
        }
        j++;
    }
}
void del(int adad[9][9] , int check[9] , int c , int h)
{
    //this function will delete numbers that exist in the square from possible number
    for(int i =c;i<3+c;i++)
        for(int j=h;j<3+h;j++)
            if(adad[i][j]!=0)
                for(int k=0;k<9;k++)
                    if(adad[i][j]==check[k])
                        //if a number is not possible to be answered I will change that number in check to zero
                        check[k] = 0;
}
void crossHaching(int adad[9][9],int check[9], int c , int h)
{
    //this function provide an algorithm that uses in cross hatching
    //crossHach will change the value member of row or column to one if in that row or column cant put number is checking
    int crossHach[3][3];
    for(int k=0;k<9;k++)
        {
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                crossHach[i][j] = 0;
        //detect full square
        for(int i=c;i<3+c;i++)
            for(int j=h;j<3+h;j++)
                if(adad[i][j]!=0)
                    crossHach[i-c][j-h] = 1;
        if(check[k] != 0){
            for(int i=c;i<3+c;i++){
                for(int j=h+3;j!=h;j++){
                    if(j==9){
                        j = -1;
                        continue;
                    }
                    if(adad[i][j] == check[k]){
                        for(int m=0;m<3;m++)
                            crossHach[i%3][m]=1;
                        break;
                    }
                }
            }
            for(int i=h;i<h+3;i++){
                for(int j=c+3;j!=c;j++){
                    if(j==9){
                        j = -1;
                        continue;
                    }
                    if(adad[j][i] == check[k]){
                        for(int m=0;m<3;m++)
                            crossHach[m][i%3]=1;
                        break;
                    }
                }
            }
            // Nans count total number that can be put
            // ansj and ansi  will save last possible square that can put number
            int Nans=0,ansi , ansj;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(crossHach[i][j] == 0){
                        ansi = i;
                        ansj = j;
                        Nans++;
                    }
                }
            }
            if(Nans == 1)
                adad[ansi+c][ansj+h] = check[k];
        }
    }
}
void showSodo(int adad[9][9])
{
    // for show sudoku
    for(int i =0;i< 9 ;i++){
        for(int j=0;j< 9 ;j++)
            cout << adad [i][j]<<" ";
        cout << endl;
    }
    cout << endl;
}
void setupCH(int adad[9][9])
{
    // make primary data for cross hatching
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            {
            // check will have all possible number that can put
            int check[9] = {1,2,3,4,5,6,7,8,9};
            //3*i is the first row that wants to check
            //3*j is the first column that wants to check
            del(adad , check , 3*i , 3*j);
            crossHaching(adad , check, 3*i , 3*j);
        }
    }
}
void put(int adad[9][9] , int check[9] , int r , int c )
{
    //put is function that start cross hatching
    //pass will restore check array after del function
    int pass[9];
    for(int i=0;i<9;i++)
        pass[i] = check[i];
    // i and j will select all small square in big square that selected
    for(int i=r ; i < r+3 ;i++){
        for(int j=c ; j<c+3 ; j++){
            // back check to after del status
            for(int i=0;i<9;i++)
                check[i] = pass[i];
            if(adad[i][j] != 0)
                continue;
            // check row
            for(int k=c+3 ; k!=c ; k++){
                if(k>=9){
                    k = -1;
                    continue;
                }
                if(adad[i][k]==0)
                    continue;
                for(int l=0;l<9;l++)
                    if(check[l]!=0&&check[l] == adad[i][k])
                        check[l] = 0;
            }
            //check clomn
            for(int k=r+3 ; k!=r ; k++)
            {
                if(k>=9){
                    k = -1;
                    continue;
                }
                if(adad[k][j]==0)
                    continue;
                for(int l=0;l<9;l++)
                    if(check[l]!=0&&check[l] == adad[k][j])
                        check[l] = 0;
            }
            int Nans = 0 , ans;
            for(int l=0;l<9;l++)
                if(check[l]!=0){
                    Nans++;
                    ans = check[l];
                }
            if(Nans == 1)
                adad[i][j] = ans;
        }
    }
}
void setup(int adad[9][9])
{
    // this function will provide data that used for checking row and cloumn
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            int check[9] = {1,2,3,4,5,6,7,8,9};
            del(adad , check , 3*i , 3*j);
            put(adad , check , 3*i , 3*j);
        }
}
bool is_solved(int adad[9][9])
{
    // see if sudoku is solved or not
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            if(adad[i][j] == 0)
                return true;
    return false;
}
