#include <iostream>
#include <fstream>
using namespace std;
void GETdata(int adad[9][9]){
    string get;
    fstream getData ("Data.txt");
    int j = 0 , k = 0;
    while(getline(getData , get)){
        for(int i=0;i<get.size();i++){
            if(get[i] == ' '){
                continue;
            }
            else if( 48<=get[i] && get[i] <= 57){
                adad[j][k] = (int)get[i] - 48;
                k++;
            }
        }
        k = 0;
        j++;
    }
}
void del(int adad[9][9] , int check[9] , int c , int h){
    for(int i =c;i<3+c;i++){
        for(int j=h;j<3+h;j++){
            if(adad[i][j]!=0){
                for(int k=0;k<9;k++){
                    if(adad[i][j]==check[k]){
                        check[k] = 0;
                    }
                }
            }
        }
    }
}
void crossHaching(int adad[9][9],int check[9], int c , int h){
    int crossHach[3][3];
    for(int k=0;k<9;k++){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                crossHach[i][j] = 0;
            }
        }
        for(int i=c;i<3+c;i++){
            for(int j=h;j<3+h;j++){
                if(adad[i][j]!=0){
                    crossHach[i-c][j-h] = 1;
                }
            }
        }
        if(check[k] != 0){
            for(int i=c;i<3+c;i++){
                for(int j=h+3;j!=h;j++){
                    if(j==9){
                        j = -1;
                        continue;
                    }
                    if(adad[i][j] == check[k]){
                        for(int m=0;m<3;m++){
                            crossHach[i%3][m]=1;
                        }
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
                        for(int m=0;m<3;m++){
                            crossHach[m][i%3]=1;
                        }
                        break;
                    }
                }
            }
            int Tjavab=0,javabi , javabj;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(crossHach[i][j] == 0){
                        javabi = i;
                        javabj = j;
                        Tjavab++;
                    }
                }
            }
            if(Tjavab == 1){
                adad[javabi+c][javabj+h] = check[k];
            }
        }
    }
}
void showSodo(int adad[9][9]){
    for(int i =0;i< 9 ;i++){
        for(int j=0;j< 9 ;j++){
            cout << adad [i][j]<<" ";
        }
        cout << endl;
    }
    cout << endl;
}
void setupCH(int adad[9][9]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            int check[9] = {1,2,3,4,5,6,7,8,9};
            del(adad , check , 3*i , 3*j);
            crossHaching(adad , check, 3*i , 3*j);
        }
    }
}
void put(int adad[9][9] , int check[9] , int r , int c ){
    int pass[9];
    for(int i=0;i<9;i++){
        pass[i] = check[i];
    }
    for(int i=r ; i < r+3 ;i++){
        for(int j=c ; j<c+3 ; j++){
            for(int i=0;i<9;i++){
                check[i] = pass[i];
            }
            if(adad[i][j] != 0){
                continue;
            }
            for(int k=c+3 ; k!=c ; k++){
                if(k>=9){
                    k = -1;
                    continue;
                }
                if(adad[i][k]==0){
                    continue;
                }
                for(int l=0;l<9;l++){
                    if(check[l]!=0&&check[l] == adad[i][k]){
                        check[l] = 0;
                    }
                }
            }
            for(int k=r+3 ; k!=r ; k++){
                if(k>=9){
                    k = -1;
                    continue;
                }
                if(adad[k][j]==0){
                    continue;
                }
                for(int l=0;l<9;l++){
                    if(check[l]!=0&&check[l] == adad[k][j]){
                        check[l] = 0;
                    }
                }
            }
            int Tjav = 0 , jav;
            for(int l=0;l<9;l++){
                if(check[l]!=0){
                    Tjav++;
                    jav = check[l];
                }
            }
            if(Tjav == 1){
                adad[i][j] = jav;
            }
        }
    }
}
void setup(int adad[9][9]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            int check[9] = {1,2,3,4,5,6,7,8,9};
            del(adad , check , 3*i , 3*j);
            put(adad , check , 3*i , 3*j);
        }
    }
}
bool tamam(int adad[9][9]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(adad[i][j] == 0){
                return true;
            }
        }
    }
    return false;
}
int main()
{
    int adad[9][9];
    GETdata(adad);
    showSodo(adad);
    int counter = 0;
    bool finish = true;
    while(tamam(adad)){
        if(counter == 50){
            finish = false;
            break;
        }
        setupCH(adad);
        setup(adad);
        counter++;
    }
    if(finish){
        cout << "I SOLVE It :)"<<endl;
    }
    else{
        cout << "I CANT SOLVE IT :("<<endl;
    }
    showSodo(adad);
    return 0;
}
