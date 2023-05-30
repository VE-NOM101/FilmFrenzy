#include<bits/stdc++.h>
#include"head.h"
using namespace std;

void review :: readme_file(void){
    cout<<"Here are all the instructions.\n";
    string line (110,'-');
    char str[200];
    cout<<line<<endl;
    fstream fin;
    fin.open("readme.txt",ios::in);
    while(1){
        if(fin.eof()) break;
        fin.getline(str,200);
        cout<<str<<endl;
    }
    fin.close();
}
void critic_review :: search(void){
    cout<<"\nHey! critic what do you want:\n";
    cout<<"#Press w to write a review.\n";
    cout<<"#Press e to edit a review.\n";
    cout<<"#Press d to delete a review.\n";
    cout<<"#Press v to view a review.\n";
    cout<<"#Press a to add movie in watchlist & view the watchlist.\n";
    cout<<"#Press o to exit.\n";
    char ch;
    cin>>ch;
    switch(ch){
        getchar();
        case 'w': critic_review :: new_review(); break;
        case 'e': critic_review :: edit_review(); break;
        case 'd': critic_review :: delete_review(); break;
        case 'v': critic_review :: view(); break;
        case 'a': watchlist(*this); break;
        case 'o': return;
        default: cout<<"Can't understand\n";
    }
}

void critic_review :: new_review(void){
    char movie[50],temp[50];
    cout<<"Enter the movie name:\n";
    cin>>movie;
    strcpy(temp,movie);
    strcat(movie,".txt");
    fstream file;
    file.open(movie,ios::in);
    if(file.is_open()){
        cout<<"This movie has given already a review\n";
        file.close();
        return;
    }else{
        file.close();
        file.open(movie,ios::out);
        cout<<"Write some review...Write 'exit' to exit\n\n";
        file<<"Reviewed by "<<login.curr_critic<<"\n";
        string line;
        while(1){
            getline(cin,line);
            if(line=="exit") break;
            file<<line<<"\n";
        }
        file.close();

        file.open("movie_list.txt",ios::app | ios::binary);
        file.write((char*)&temp,sizeof(temp));
        file.close();
        cout<<"Successfully written...\n";
    }
}

void critic_review :: edit_review(void){
    char movie[50];
    cout<<"Enter the movie name:\n";
    cin>>movie;
    strcat(movie,".txt");
    fstream file;
    file.open(movie,ios::in);
    if(file.is_open()){
        file.close();
        file.open(movie,ios::app);
        cout<<"Write some lines that you want to be appended...Write 'exit' to exit\n";
        string line;
        while(1){
            getline(cin,line);
            if(line=="exit") break;
            file<<line<<"\n";
        }
        file.close();
        cout<<"Successfully edited...\n";
    }else{
        cout<<"This movie has given no review earlier...\n";
        file.close();
        return;
    }
}

void critic_review :: delete_review(void){
    char movie[50],temp[50];
    cout<<"Enter the movie name:\n";
    cin>>movie;
    strcpy(temp,movie);
    strcat(movie,".txt");
    fstream file;
    file.open(movie,ios::in);
    if(file.is_open()){
        file.close();
        remove(movie);

        file.open("movie_list.txt",ios::in | ios::out | ios::binary);
        char temp2[50];
        file.seekg(0,ios::beg);

        while(file.read((char*)&temp2,sizeof(temp2))){
            if(!strcmp(temp,temp2)){
                int position=file.tellg();
                position-=50;
                file.seekp(position,ios::beg);
                strcpy(temp2,"000");
                file.write((char*)&temp2,sizeof(temp2));
                file.close();
                break;
            }
        }

        cout<<"Successfully deleted\n";
    }else{
        cout<<movie<<", is not found"<<"\n";
        file.close();
        return;
    }
}

void critic_review :: view(void){
    char movie[50];
    cout<<"Enter the movie name:\n";
    cin>>movie;
    strcat(movie,".txt");
    fstream file;
    file.open(movie,ios::in);
    if(file.is_open()){
        char line[500];
        while(1){
            if(file.eof()) break;
            file.getline(line,500);
            cout<<line<<endl;
        }
        cout<<"Review of the movie: "<<movie<<" has been viewed successfully\n";
        file.close(); 
    }else{
        cout<<movie<<", is not found to view"<<"\n";
        file.close();
        return;
    }
}

void user_review :: search(void){
    char movie[50],temp[50];
    cout<<"Enter the movie name:\n";
    cin>>movie;
    strcpy(temp,movie);
    strcat(movie,".txt");
    fstream file;
    file.open(movie,ios::in);
    if(file.is_open()){
        char line[500];
        while(1){
            if(file.eof()) break;
            file.getline(line,500);
            cout<<line<<endl;
        }
        file.close();
        strcat(temp,"_comment.txt");
        comment_rating(temp);
    }else{
        cout<<movie<<", no such movie is found"<<"\n";
        file.close();
        return;
    }
}

void user_review :: comment_rating(char*movie){
    cout<<"Do you want to do add comment,y/n\n";
    char ch;
    cin>>ch;
    if(ch=='y'){
        getchar();
        char line[200];
        cout<<"Write the comment:\n";
        scanf("%[^\n]",line);
        fstream file;
        file.open(movie,ios::app);
        file<<line<<" ->commented by @"<<login.curr_user<<endl;
        cout<<"Comment is added successfully\n";
        file.close();
    }else{
        cout<<"No comment is added\n";
    }
}
// new features

void user_review :: view_comments(void){
    char movie_comment[50];
    cout<<"Enter the movie name:\n";
    cin>>movie_comment;
    strcat(movie_comment,"_comment.txt");
    fstream file;
    file.open(movie_comment,ios::in);
    if(file.is_open()){
        char line[500];
        while(1){
            if(file.eof()) break;
            file.getline(line,500);
            cout<<line<<endl;
        }
        file.close();
    }else{
        cout<<movie_comment<<", no relevant file is found."<<"\n";
        file.close();
        return;
    }
}

void review :: movie_list(void){
    char movie[50];
    fstream file;
    file.open("movie_list.txt",ios::in | ios::binary);
    int count=1;
    cout<<endl<<"Here, is the movie list:\n";
    while(file.read((char*)&movie,sizeof(movie))){
        if(strcmp(movie,"000")){
            cout<<count<<". "<<movie<<endl;
            count++;
        }
    }
    file.close();
    return;
}

void operator+(critic_review&obj1, user_review&obj2){
    char movie[50];
    fstream file,file2;
    file.open("movie_list.txt",ios::in | ios::binary);
    int count=1;
    cout<<endl<<"Here, is the movie list:\n";
    while(file.read((char*)&movie,sizeof(movie))){
        if(strcmp(movie,"000")){
            cout<<count<<". "<<movie<<endl;
            cout<<"Comment box of "<<movie<<endl;
            cout<<"................................................\n";
            count++;
            char temp[50];
            strcpy(temp,movie);
            strcat(temp,"_comment.txt");
            file2.open(temp,ios::in);
            if(file2.is_open()){
                char line[500];
                while(1){
                    if(file2.eof()) break;
                    file2.getline(line,500);
                    cout<<line<<endl;
                }
                file2.close();
            }else{
                file2.close();
            }
        }
        cout<<endl;
    }
    file.close();
    return;
}


//update 2


template<typename T>

void add_watchlist(T& obj){

    fstream file;
    char name[25];
    char wlist[50];
    if(typeid(obj)==typeid(user_review)) strcpy(name,obj.login.curr_user);
    else if(typeid(obj)==typeid(critic_review)) strcpy(name,obj.login.curr_critic);
    strcpy(wlist,name);
    strcat(wlist,"_wlist.txt");
    file.open(wlist,ios:: app);
    if(file.is_open()){
        cout<<"Enter the movie name, that you want to add in watchlist:\n";
        char movie[50];
        cin>>movie;
        file<<movie<<endl;
        cout<<"Movie added successfully in the list <"<<name<<">\n";
        cout<<endl;
        file.close();
        return;
    }else{
        file.close();
        return;
    }
}

template<typename T>
void view_watchlist(T& obj){
    fstream file;
    char name[25];
    char wlist[50];
    if(typeid(obj)==typeid(user_review)) strcpy(name,obj.login.curr_user);
    else if(typeid(obj)==typeid(critic_review)) strcpy(name,obj.login.curr_critic);
    strcpy(wlist,name);
    strcat(wlist,"_wlist.txt");
    file.open(wlist,ios:: in);
    if(file.is_open()){
        char line [100];
        int count =1;
        cout<<"Watchlist of <"<<name<<">\n";
        cout<<"..................................................\n";
        while(1){
            if(file.eof()) break;
            file.getline(line,100);
            cout<<count<<") "<<line<<endl;
            count++;
        }
        file.close();
        return;
    }else{
        cout<<"No watchlist has been found.\n";
        file.close();
        return;
    }
}

void watchlist(review& obj){
    jump:
    cout<<"\nPress, 1 to add movie in watchlist.\n";
    cout<<"Press, 2 to view movie watchlist.\n";
    cout<<"Press, any other key to exit.\n";
    int p;
    cin>>p;
    if(p==1){
        add_watchlist(obj);
        goto jump;
    }else if(p==2){
        view_watchlist(obj);
        goto jump;
    }else{
        return;
    }
}

void top_movies(void){
    fstream file;
    file.open("top_movies.txt",ios::in);
    if(file.is_open()){
        char line[100];
        int count=1;
        while(1){
            if(file.eof()) break;
            file.getline(line,100);
            cout<<count<<") "<<line<<endl;
            count++;
        }
        file.close();
    }else{
        cout<<"top_movies.txt file doesn't exist\n";
        file.close();
    }
}