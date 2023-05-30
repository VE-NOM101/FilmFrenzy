#ifndef HEAD_H
#define HEAD_H

class user{
    protected:
        char id[25];
        char pw[36];
    public:
        user();
        user(char*id,char*pw);
        void setValue(char* user_id, char* password);
        char*getId(void);
        char*getPw(void);
};

class LoginSys{
    protected:
        std::fstream fusers;
        std::fstream fcritics;
    public:
        char curr_user[25];
        char curr_critic[25];
        LoginSys();
        bool create_new_user(void);
        bool user_sign_in(void);
        bool create_new_critic(void);
        bool critic_sign_in(void);
        bool delete_user(void);
        bool delete_critic(void);
};

class review{
    public:
        LoginSys login;
        void readme_file(void);
        virtual void search(void)=0;
        void movie_list(void);
};
class user_review;

class critic_review:public review{
    public:
        void search(void);
        void new_review(void);
        void edit_review(void);
        void delete_review(void);  
        void view(void);
        friend void operator+(critic_review&, user_review&);
};
class user_review:public review{
    public:
        void search(void);
        void comment_rating(char*movie);
        void view_comments();
        friend void operator+(critic_review&, user_review&);
};

void operator+(critic_review&, user_review&);

template<typename T>
void add_watchlist(T& obj);
template<typename T>
void view_watchlist(T& obj);

void watchlist(review& obj);

void top_movies(void);

#endif