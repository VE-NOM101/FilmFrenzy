#include <bits/stdc++.h>
#include "head.h"
using namespace std;
user::user()
{
}
user::user(char *id, char *pw)
{
    strcpy(this->id, id);
    strcpy(this->pw, pw);
}
void user::setValue(char *user_id, char *password)
{
    strcpy(id, user_id);
    strcpy(pw, password);
}
char *user::getId(void)
{
    return id;
}
char *user::getPw(void)
{
    return pw;
}

LoginSys::LoginSys()
{
    fusers.open("user_data.dat", ios::app | ios::binary);
    fcritics.open("critic_data.dat", ios::app | ios::binary);
    fusers.close();
    fcritics.close();
}

bool LoginSys::create_new_user(void)
{
    user temp;
    char userid[25], userpw[36];
    fusers.open("user_data.dat", ios::in | ios::binary);
jump:
    bool flag = 0;
    fusers.seekg(0, ios::beg);
    cout << "Enter a valid username (Upto 25 character & space is not allowed):\n";
    cin >> userid;

    while (fusers.read((char *)&temp, sizeof(temp)))
    {
        if (!strcmp(userid, temp.getId()))
        {
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        cout << "Duplicate username!\n";
        char ch;
        cout << "Enter y for try again or n for exit\n";
        cin >> ch;
        if (ch == 'y')
        {
            goto jump;
        }
        else
        {
            fusers.close();
            return 0;
        }
    }
    else
    {
        cout << "Enter a strong password:\n";
        cin >> userpw;
        temp.setValue(userid, userpw);
        fusers.close();
        fusers.open("user_data.dat", ios::app | ios::binary);
        fusers.write((char *)&temp, sizeof(temp));
        fusers.close();
        return 1;
    }
}

bool LoginSys::user_sign_in(void)
{
    user temp;
    int count = 0;
    char userid[25], userpw[36];

outerjump:
    fusers.open("user_data.dat", ios::in | ios::binary);
    bool flag = 0;
    fusers.seekg(0, ios::beg);
    cout << "Enter username:\n";
    cin >> userid;

    while (fusers.read((char *)&temp, sizeof(temp)))
    {
        if (!strcmp(userid, temp.getId()))
        {
            flag = 1;
            break;
        }
    }

    if (flag)
    {
    innerjump:
        cout << "Enter password:\n";
        cin >> userpw;
        count++;
        if (!strcmp(userpw, temp.getPw()))
        {
            cout << "Signed-In successfully\n";
            fusers.close();
            strcpy(curr_user, userid);
            return 1;
        }
        else
        {
            cout << "Invalid Password!!!\n";
            if (count == 3)
            {
                fusers.close();
                return 0;
            }
            else
                goto innerjump;
        }
    }
    else
    {
        cout << "Username is not found!\n";
        char ch;
        cout << "Enter y for try again or n for exit:\n";
        cin >> ch;
        if (ch == 'y')
        {
            fusers.close();
            goto outerjump;
        }
        else
        {
            fusers.close();
            return 0;
        }
    }
}

bool LoginSys::create_new_critic(void)
{
    user temp;
    char criticid[25], criticpw[36];
    fcritics.open("critic_data.dat", ios::in | ios::binary);
jump:
    bool flag = 0;
    fcritics.seekg(0, ios::beg);
    cout << "Enter a valid Critc's id (Upto 25 character & space is not allowed):\n";
    cin >> criticid;

    while (fcritics.read((char *)&temp, sizeof(temp)))
    {
        if (!strcmp(criticid, temp.getId()))
        {
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        cout << "Duplicate Critic's id!\n";
        char ch;
        cout << "Enter y for try again or n for exit\n";
        cin >> ch;
        if (ch == 'y')
        {
            goto jump;
        }
        else
        {
            fcritics.close();
            return 0;
        }
    }
    else
    {
        cout << "Enter a strong password:\n";
        cin >> criticpw;
        temp.setValue(criticid, criticpw);
        fcritics.close();
        fcritics.open("critic_data.dat", ios::app | ios::binary);
        fcritics.write((char *)&temp, sizeof(temp));
        fcritics.close();
        return 1;
    }
}

bool LoginSys::critic_sign_in(void)
{
    user temp;
    int count = 0;
    char criticid[25], criticpw[36];

outerjump:
    fcritics.open("critic_data.dat", ios::in | ios::binary);
    bool flag = 0;
    fcritics.seekg(0, ios::beg);
    cout << "Enter Critic's id:\n";
    cin >> criticid;

    while (fcritics.read((char *)&temp, sizeof(temp)))
    {
        if (!strcmp(criticid, temp.getId()))
        {
            flag = 1;
            break;
        }
    }

    if (flag)
    {
    innerjump:
        cout << "Enter password:\n";
        cin >> criticpw;
        count++;
        if (!strcmp(criticpw, temp.getPw()))
        {
            cout << "Signed-In successfully\n";
            fcritics.close();
            strcpy(curr_critic, criticid);
            return 1;
        }
        else
        {
            cout << "Invalid Password!!!\n";
            if (count == 3)
            {
                fcritics.close();
                return 0;
            }
            else
                goto innerjump;
        }
    }
    else
    {
        cout << "Critic's id is not found!\n";
        char ch;
        cout << "Enter y for try again or n for exit:\n";
        cin >> ch;
        if (ch == 'y')
        {
            fcritics.close();
            goto outerjump;
        }
        else
        {
            fcritics.close();
            return 0;
        }
    }
}

bool LoginSys ::delete_user(void)
{
    user temp;
    fusers.open("user_data.dat", ios::in | ios::binary);
    char userid[25], userpw[36];
    int count = 0;
    cout << "Enter the username:\n";
    cin >> userid;
    bool flag = 0;
    int position;
    while (fusers.read((char *)&temp, sizeof(temp)))
    {
        if (!strcmp(userid, temp.getId()))
        {
            flag = 1;
            position = fusers.tellg();
            fusers.close();
            break;
        }
    }
    if (flag)
    {
        fusers.open("user_data.dat", ios::in | ios::out | ios::binary);
    jump:
        cout << "Enter the password:\n";
        cin >> userpw;
        if (!strcmp(userpw, temp.getPw()))
        {
            position -= 61;
            fusers.seekp(position, ios::beg);
            char zero[5] = "000";
            temp.setValue(zero, zero);
            fusers.write((char *)&temp, sizeof(temp));
            fusers.close();
            cout << "User account is deleted successfully\n";
            return 1;
        }
        else
        {
            cout << "Wrong password\n";
            if (count == 3)
            {
                fusers.close();
                return 0;
            }
            else
                goto jump;
        }
    }
    else
    {
        cout << "No username is matched!\n";
        fusers.close();
        return 0;
    }
}

bool LoginSys ::delete_critic(void)
{
    user temp;
    fcritics.open("critic_data.dat", ios::in | ios::binary);
    char criticid[25], criticpw[36];
    int count = 0;
    cout << "Enter the Critic's id:\n";
    cin >> criticid;
    bool flag = 0;
    int position;
    while (fcritics.read((char *)&temp, sizeof(temp)))
    {
        if (!strcmp(criticid, temp.getId()))
        {
            flag = 1;
            position = fcritics.tellg();
            fcritics.close();
            break;
        }
    }
    if (flag)
    {
        fcritics.open("critic_data.dat", ios::in | ios::out | ios::binary);
    jump:
        cout << "Enter the password:\n";
        cin >> criticpw;
        if (!strcmp(criticpw, temp.getPw()))
        {
            position -= 61;
            fcritics.seekp(position, ios::beg);
            char zero[5] = "000";
            temp.setValue(zero, zero);
            fcritics.write((char *)&temp, sizeof(temp));
            fcritics.close();
            cout << "Critic account is deleted successfully\n";
            return 1;
        }
        else
        {
            cout << "Wrong password\n";
            if (count == 3)
            {
                fcritics.close();
                return 0;
            }
            else
                goto jump;
        }
    }
    else
    {
        cout << "No Critic's id is matched!\n";
        fcritics.close();
        return 0;
    }
}