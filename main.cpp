#include <iostream>
#include "vector"

#include "User.h"

using namespace std;

using UsersVectorUnique = std::vector<std::unique_ptr<User>>;
using UsersVectorShared = std::vector<std::shared_ptr<User>>;

shared_ptr<User> getUser(UsersVectorShared userVector, int index) {
    return userVector[index];
}

void changeUserName(shared_ptr<User> user, string newName) {
    cout << "use count: " << user.use_count() << endl;
    user->name = newName;
}

void changeRefUserName(shared_ptr<User> &user, string newName) {
    cout << "use count: " << user.use_count() << endl;
    user->name = newName;
}

void addUsers(UsersVectorShared& v, uint count) {
    cout << "capacity before: " << v.capacity() << endl;
    for (auto i = 0; i < count; i++) {
        auto stub_user = make_shared<User>(User("Stub"));
        v.push_back(stub_user);
    }
    cout << "capacity after: " << v.capacity() << endl;
}

int main() {
    cout << "Hello, Pointers!" << endl;

    UsersVectorUnique u_users;
    auto u_user = make_unique<User>(User("Anton"));
    u_users.push_back(move(u_user));

    for(auto i = 0; i < 100; i++) {
        auto stub_user = make_unique<User>(User("Stub"));
        u_users.push_back(move(stub_user));
    }

    // Uncomment to get signal 11: SIGSEGV
    // cout << u_user->name << endl;
    //

    UsersVectorShared s_users;
    auto s_user = make_shared<User>(User("Stig"));
    weak_ptr<User> w_user = s_user;
    shared_ptr<User>* p_user = &s_user; // pointer to shared_ptr
    shared_ptr<User>& r_user = s_user;  // reference to shared_ptr

    // push user to vector
    s_users.push_back(s_user);

    cout << "username: " << s_user->getName() << endl;

    addUsers(s_users, 100);

    s_users[0]->name = "John";
    cout << "username: " << s_user->getName() << endl;
    cout << "username: " <<  p_user->get()->getName() << endl;
    cout << "username: " <<  r_user->getName() << endl;

    getUser(s_users, 0)->name = "Stig";

    cout << "username: " << s_user->getName() << endl;
    cout << "username: " <<  p_user->get()->getName() << endl;
    cout << "username: " <<  r_user->getName() << endl;

    changeUserName(s_user, "Keanu");

    cout << "username: " << s_user->getName() << endl;
    cout << "username: " <<  p_user->get()->getName() << endl;
    cout << "username: " <<  r_user->getName() << endl;

    addUsers(s_users, 500);
    changeRefUserName(s_user, "Matilda");


    cout << "username: " << s_user->getName() << endl;
    cout << "username: " <<  p_user->get()->getName() << endl;
    cout << "username: " <<  r_user->getName() << endl;

    cout << "use count: " << s_user.use_count() << endl;

    string search = "Matilda";
//    auto found{ find_if(s_users.begin(), s_users.end(),[search](shared_ptr<User> user)
//                             {
//                                 return (user->getName() == search);
//                             })
//    };
//
//    if (found == s_users.end())
//    {
//        cout << "No Stig\n";
//    } else {
//        cout << "Found user: " << found->get()->getName() << '\n';
//    }

    addUsers(s_users, 5000);

    auto changeUser {
            [w_user]() {
                auto user = w_user.lock();
                if (user) {
                    user->name = "Anton";
                    cout << "use count: " << w_user.use_count() << endl;
                    cout << "lambda username: " << user->getName() << endl;
                }
            }
    };

//    auto changeUser {
//            [s_user]() {
//                s_user->name = "Anton";
//                cout << "use count: " << s_user.use_count() << endl;
//                cout << "lambda username: " << s_user->getName() << endl;
//            }
//    };

    changeUser();
    cout << "username: " << s_user->getName() << endl;

    cout << "use count: " << s_user.use_count() << endl;

    return 0;
}
