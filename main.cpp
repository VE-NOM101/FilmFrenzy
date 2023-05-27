#include<bits/stdc++.h>
#include"head.h"
using namespace std;
int main(){
    critic_review obj1;
    user_review obj2;
    jump:
    cout<<"--------------------------FilmFrenzy------------------------\n";
    cout<<"Welcome to our page\n";
    cout<<"->Press, '1' to Sign-up/Sign-in\n";
    cout<<"->Press, '2' to readme file\n";
    cout<<"->Press, '3' to see movie list\n";
    cout<<"->Press, '4' to see movie list with their comment box\n";
    cout<<"->Press, '5' to exit\n";
    cout<<"@ It's very important to read the readme file before using it\n";
    cout<<endl;
    int n;
    cin>>n;
    if(n==1){
        innerjump:
        cout<<"->Press, '1' to Create a new account\n";
        cout<<"->Press, '2' to Sign-in\n";
        cout<<"->Press, '3' to Delete an account\n";
        cout<<endl;
        int m;
        cin>>m;
        if(m==1){
            cout<<"->Press,'1' for creating an account as a critic, or Press, '2' for creating an account as a user\n";
            cout<<"->Press, '3' to exit.\n";
            int p;
            cin>>p;
            if(p==1){
                obj1.login.create_new_critic();
                goto innerjump;
            }else if(p==2){
                obj2.login.create_new_user();
                goto innerjump;
            }else if(p==3){
                
            }else{
                cout<<"Invalid input\n";
            }
        }else if(m==2){
            cout<<"\n->Press, '1' to login as critic, or Press, '2' to login as user\n";
            int p;
            cin>>p;
            if(p==1){
                if(obj1.login.critic_sign_in()){
                    cout<<"------------------------------------------------------------";
                    innerjump2:
                    obj1.search();
                    cout<<endl;
                    cout<<"Do you want to stay logged in?, (y=1/n=2)\n";
                    int a;
                    cin>>a;
                    if(a==1) goto innerjump2;
                    else ;
                }else{
                    cout<<"Returning from 'Critic' sign-in menu'\n";
                }
            }else if(p==2){
                if(obj2.login.user_sign_in()){
                    cout<<"------------------------------------------------------------";
                    innerjump3:
                    cout<<"\n# Press '1' to view some movie reviews or, Press '2' to check comment box.\n";
                    int b; 
                    cin>>b;
                    if(b==1) obj2.search();
                    else if(b==2) obj2.view_comments();
                    cout<<endl;
                    cout<<"Do you want to stay logged in?, (y=1/n=2)\n";
                    int a;
                    cin>>a;
                    if(a==1) goto innerjump3;
                    else ;
                }else{
                    cout<<"Returning from 'User' sign-in menu'\n";
                }
            }else{
                cout<<"Invalid operation\n";
            }
        }else if(m==3){
        cout<<"\n#Press, '1' to delete critc type account or, Press, '2' to delete user type account\n";
        int o;
        cin>>o;
        if(o==1){
            obj1.login.delete_critic();
            goto innerjump;
        }else if(o==2){
            obj2.login.delete_user();
            goto innerjump;
        }else{
            cout<<"Invalid operation\n";
        }
        }
    }else if(n==2){
        obj1.readme_file();
    }else if(n==3){
        obj1.movie_list();
    }else if(n==4){
        obj1+obj2;
    }else if(n==5){
        return 0;
    }else{
        cout<<"Inappropriate operation\n";
    }
    cout<<endl<<"##Do you want to back to homepage again,(y=1/n=2):\n";
    int q;
    cin>>q;
    if(q==1){
        goto jump;
    }else {
        return 0;
    }
}