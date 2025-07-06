/*======================================
 #    Ontokentrikos Programmatismos    #
 #        CEID UPATRAS 2018-2019       #
 #    Project: Social Network in C++   #
 #      ---------------------------    #
 #     Thanos Georgios,  AM:1067486    #
 #    Kapelles Dionysios, AM:1067479   #
=======================================*/
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Variables
string regname, regpass;  // name and password for Registration
string logname, logpass;  // name and password for Log In
string name, password;    // name and password existing in Database
string posts;             // posts of user who is logged in
string friendname, frend; // strings for friend names

// Functions-Methods
int mainMenu();   // main menu
void menu2();     // menu after the successful login
void menu3();     // menu to add friends
int reg();        // the registration process
void login();     // login process
void friendrequest();  // view the friend requests
void friends();   // view the friends
void post();      // posting process
void viewposts(); // view your posts
void viewFriendPosts(); // view friend posts
void deletefriends(); // delete friend
void listUsers(); // see all registered users
void goBack();    // choose to exit from a menu or go back to main menu
int exit();       // exit the program

//=======================
// Main Menu and Options
//=======================
int mainMenu()
{
    cout << endl;
    // Main menu options
    cout << "Main Menu (Type the number of your choice)" << endl << string(42, '=') << endl;
    cout << "1: Register" << endl;
    cout << "2: Log In" << endl;
    cout << "3: Exit the Program" << endl;
    cout << endl;

	// Choose from the available numbers
    int choice;
	cout << "Choice: ";
	cin >> choice;
	cin.ignore();

	switch (choice)
	{
		case 1:
			reg();
			break;
		case 2:
			login();
			break;
		case 3:
			exit();
			break;
		default:
			cout << "Wrong choice! Try again!" << endl << endl;
			mainMenu();
	}
    return 0;
}

//===============================
// New User Registration proccess
//===============================
int reg()
{
    ifstream f;
    f.open( "database.txt" );   // Accesing database file

	// Give username
    cout << endl << "Write the desired username :" << endl;
    getline( cin, regname );

	// Check if username already exists
	while(!f.eof())
	{
		getline(f, name, '\n');     // Reading the usernames from the database
		getline(f, password, '\n'); // Reading the passwords from the database
		while(regname == name)
		{
			 cout << "The username already exists! Try again : " << endl;
			 reg(); // If name already exists start process of registration again
		}
	}
	f.close();
	// Give password
    cout << "Write the desired password: " << endl;
    getline ( cin, regpass );

	// if the password is less than 4 chars try the registration proccess again
    while ( regpass.length() < 4)
    {
        cout << endl;
        cout << "The chosen password is too short!" << endl;
        cout << "The password needs to be at least four characters long." << endl << endl;;
        cout << "Try another password :" << endl;
        getline ( cin, regpass );
    }

	ofstream g( "database.txt", ios::app ); // Open database file to write
	// The ios::app lets you write in the same file without deleting the existing content
    ofstream v( regname.c_str(), ios::app );
	v.close();
	// If the name and the password are ok add them to database
	g << regname << '\n';
	g << regpass << '\n';

	g.close(); // close the database file

	cout << endl;
	cout << "You have successfully registered!" << endl << endl;
	cout << "Type:" << endl;
	cout << "1. Log In" << endl;
	cout << "2. Return to main menu" << endl;
	cout << "3. Exit the program" << endl;
	cout << endl;

	// Process after successful registration
	int a;
	cin >> a;
	cin.ignore();

	switch (a)
	{
		case 1:
			login();
			break;
		case 2:
			mainMenu();
			break;
		case 3:
			exit();
			break;
		default:
			cout << "Wrong choice! Try again!" << endl;
			break;
	}
    return 0;
}

//================
//  User login
//================
void login()
{
	// Open file with usernames and passwords
    ifstream f;
    f.open( "database.txt" );

	// Check if user is already registered
    if (!f.is_open())
    {
        cout << endl;
        cout << "You have to register first!" << endl;
        mainMenu();
    }

    cout << endl << "Write your username: " << endl;
    getline( cin, logname ); // Enter username to login

    cout << "Write your password: " << endl;
    getline( cin, logpass ); // Enter password to login

    int j;
    while(!f.eof()){
        getline(f, name, '\n');     //reading the usernames in the database
        getline(f, password, '\n'); //reading the passwords from the database

		// Check if username and password are right
        if ( logname == name && logpass == password )
        {
            cout << endl;
            cout << "Successfully logged in! " << endl;
            cout << "Welcome, " << logname << " !" << endl;
            menu2();
            break;
        }
        else if ( logname != name && logpass == password ) {j=1;}
        else if ( logname == name && logpass != password ) {j=2;}
    }
    // Check for wrong username or password
    if(j==1)
    {
		cout << "Wrong username!" << endl;
		login();
    }
    else if (j==2)
	{
		cout << "Wrong password!" << endl;
		login();
    }
    f.close();
}

//==============================
// Menu after successful Log In
//==============================
void menu2()
{
    cout << endl << "Type the number of your choice :" << endl << string(32, '=') << endl;
    cout << "1: See your wall" << endl;
    cout << "2: See friends wall" << endl;
    cout << "3: Send friend request" << endl;
    cout << "4: Accept/Reject friend request" << endl;
    cout << "5: See my friends" << endl;
    cout << "6: Delete Friend" << endl;
    cout << "7: Back" << endl;
    cout << "8: Log out" << endl;
    cout << endl;

	// Choose from the available numbers
    int a;
	cout << "Choice: ";
	cin >> a;
	switch (a)
	{
		case 1:
			viewposts();
			break;
		case 2:
			viewFriendPosts();
			break;
		case 3:
			menu3();
			break;
		case 4:
			friendrequest();
			break;
		case 5:
			friends();
			break;
		case 6:
            deletefriends();
            break;
		case 7:
			mainMenu();
			break;
		case 8:
			cout << "You have successfully logged out!" << endl;
			mainMenu();
			break;
		default:
			cout << "Wrong choice! Try again!" << endl;
			menu2();
			break;
	}
}

//==========================
// See your wall with posts
//==========================
void viewposts()
{
	string namepost, reply;
	// Print all user's posts
	cout << endl << "Your posts are :" << endl << string(16, '=') << endl;
	// Open file of logged in user posts
    ifstream p;
    p.open( "Post.txt" );
    int lineCount = 1;
    // Repeat process to print all logged in user's posts
    while(!p.eof())
    {
        getline(p, name, '\n');   // Read the names from Post.txt file
        getline(p, posts, '\n');  // Read the posts from Post.txt file
        if (name==logname)
        {
            cout << lineCount << " " << posts << endl;
            lineCount++;
        }
    }
    // Close file of posts
    p.close();
    // Print all friend posts
    cout << endl << "Your friends posts are :" << endl << string(24, '=') << endl;
	bool same;
	ifstream user;
    user.open(logname.c_str());
    // Check if user is friend and then print all of his posts
    while(!user.eof())
    {
        int i=1;
        same = false;
        getline(user, frend, '\n');
		ifstream p;
    	p.open("Post.txt"); // Open file of posts
        while(!p.eof())
        {
            getline(p, name, '\n');     // Read the names from Post.txt file
            getline(p, posts, '\n');    // Read the posts from Post.txt file
            if ( frend == name && same == true )
            {
                cout << "  Post " << i << " : " << posts << endl << endl; i++;
            }
            else if ( frend == name && same == false && frend!="")
            {
                cout << "Friend : " << name << endl << string(9, '=')+string(name.size(), '=')  << endl;
                cout << "  Post " << i << " : ";
                cout << posts << endl << endl;
                i++;
                same = true;
            }
        }
		p.close();
    }
    user.close();

    // Print all conversations posts
    ifstream conversations;
    conversations.open("Reply_to_post");
	while(!conversations.eof())
	{
		getline(conversations, namepost, '\n');
		ifstream friends;
		friends.open(logname.c_str());
		string userfrend;
		while(getline(friends, userfrend))
		{
			if(userfrend == namepost.substr(0, namepost.find(":")))
				cout << namepost << endl;
			else if(namepost.substr(0,1)==" ")
			{
				if(namepost.find(logname.c_str()) != std::string::npos)
					cout << namepost << endl;
				else
					continue;
			}
		}

	}
    conversations.close();
    goBack();
}

//============================
// See friends wall and posts
//============================
void viewFriendPosts()
{
	cout << "Type the number of your choice :" << endl << string(32, '=') << endl;
	cout << "1. Post a message" << endl;
	cout << "2. Reply to a message" << endl;
	cout << "3. Like" << endl << endl;
	cout << "Choice: ";
	int choiceType;
	cin >> choiceType;

	if(choiceType==1)
	{
		string post;
		// Creat file to save user posts, without deleting the existed ones
		ofstream P( "Post.txt", ios::app );
		cout << "Write the post you want: " << endl;
		cin.ignore();
		getline(cin, post); // To write string with more than one word
		P << logname << '\n';
		P << post << '\n';
		P.close();
		goBack();
	}
	else if(choiceType==2)
	{
		string myChoice="Y";
		// Repeat process to choose frined to see posts
		while(myChoice=="Y" || myChoice=="y")
		{
            string frend;

            ifstream friends;
            friends.open((logname.c_str())); // Open file of logged in user friends

            cout << "Your friends are : " << endl << string(19, '=') << endl;
            int j=1;
            // Proccess to print a numbered list of logged in user friends
            while(getline(friends, frend) && frend!="")
            {
                cout << j << ". " << frend << endl;
                j++;
            }
            // Close file of friends
            friends.close();

            string tempFriend;

			cout << endl << "Choose the number of friend you want to see the posts :" << endl;
			int friendNum;
			cin >> friendNum;

			int l=0;
			ifstream myFriends(logname.c_str()); // Open file of logged in user
			ofstream postTemp("Temp"); // Open a temporary file to write on it
			while(!myFriends.eof()){
				l++;
				getline(myFriends, frend);
				// Check the number that user typed
				if(friendNum == l)
				{
					cout << "Friend : " << frend << endl << string(frend.size(), '=')+"==========" << endl;
					int i=1;
					ifstream friendPosts;
					friendPosts.open("Post.txt"); // Open file off all Posts
					while(!friendPosts.eof())
					{
						getline(friendPosts, name, '\n');  // Read user name
						getline(friendPosts, posts, '\n'); // Read user post
						// Check if friend's name exists on Posts.txt file
						// and print all friend's posts
						if (name == frend)
						{
							cout << "  Post " << i << " : " << posts << endl << endl;
							postTemp << posts << endl;
							i++;
						}
						tempFriend = frend; // Save current friend in tempFriend string
					}
					// Close file with posts
					friendPosts.close();
				}
				else
					continue;
			}
			postTemp.close();
			string moreRepl="Y";

			// Process to reply on a friend's post
			while(moreRepl=="Y" || moreRepl=="y")
			{
				cout << "Choose the post you wish to reply on (type it's number) : ";
				int numReply;
				cin >> numReply;
				ifstream posttemp("Temp"); // Open temporary file of posts
				int a=0; // Variable to keep count of lines
				while(!posttemp.eof())
				{
					a++;
					getline(posttemp, posts);
					if(numReply == a)
					{

						ifstream repost;
						repost.open("Reply_to_post"); // Open file of conversations
						string namepost;

						ofstream temprepost("TempRePost"); // Open temporary file to write on it
						int b=0; // Helping variable
						while(!repost.eof())
						{
							getline(repost, namepost);
							if(namepost.substr(0, namepost.find(":"))==tempFriend && namepost.find(posts) != std::string::npos )
								b++;
							temprepost << namepost << endl;
						}
						temprepost.close();

						ifstream tempLikes;
						tempLikes.open("TempRePost");
						ofstream postreplies("Reply_to_post");
						string post;
						cout << "Enter your reply..." << endl;
						cin.ignore();
						string userReply;
						getline(cin, userReply);
						while(getline(tempLikes, post) && post!="")
						{
							// Check if friend's posts already exists. Then leave a post under the other repost for this post
							if(b>0)
							{
								if(post.substr(0, post.find(":"))==tempFriend && post.find(posts) != std::string::npos )
								{
									postreplies << post << endl << string((tempFriend.size()+2) ,' ') << userReply << " ("+logname+")" << endl;
									continue;
								}
								else
									postreplies << post << endl;
							}
							// If friend's posts doesn't exists write the name of friend and his posts to leave a post
							else if(b==0)
								postreplies << post << endl;
						}
						if(b==0)
							postreplies << tempFriend+": " << posts << endl << string((tempFriend.size()+2) ,' ') << userReply  << " ("+logname+")" << endl;

						temprepost.close();
						postreplies.close();
						remove("TempRePost");

					}
				}
				cout << endl << "Reply to other posts of the same friend ? (Y/N) : ";
				cin >> moreRepl;
				if(moreRepl=="Y" || moreRepl=="y")
					continue;
				else
					posttemp.close();
					remove("Temp");
					break;
			}
			// Check if user wants to see other friend walls
			cout << endl << "See other friend's wall ? (Y/N) : ";
			cin >> myChoice;
			if(myChoice=="Y" || myChoice=="y")
			{
                cout << endl;
				continue;
			}
			else
			{
				myFriends.close();
				goBack();
				break;
            }
		}
	}
	else
	{
		string myChoice="Y";
		// Repeat process to choose frined to see posts
		while(myChoice=="Y" || myChoice=="y")
		{
            string frend;
            ifstream friends;
            friends.open((logname.c_str())); // Open file of logged in user friends

            cout << "Your friends are : " << endl << string(19, '=') << endl;
            int j=1;
            // Process to print a numbered list of logged in user's friends
            while(getline(friends, frend) && frend!="")
            {
                cout << j << ". " << frend << endl;
                j++;
            }
            friends.close();
            string tempFriend;

			cout << endl << "Choose the number of friend you want to see the posts :" << endl;
			int friendNum;
			cin >> friendNum;
			int l=0;
			ifstream myFriends(logname.c_str());
			ofstream postTemp("Temp");
			while(!myFriends.eof()){
				l++;
				getline(myFriends, frend);
				// Check the number that user typed
				if(friendNum == l)
				{
					cout << "Friend : " << frend << endl << string(frend.size(), '=')+"=========" << endl;
					int i=1;
					ifstream friendPosts;
					friendPosts.open("Post.txt"); // Open file of all Posts
					while(!friendPosts.eof())
					{
						getline(friendPosts, name, '\n');  // Read user name
						getline(friendPosts, posts, '\n'); // Read user post
						// Check if friend's name exists on Posts.txt file
						// and print all friend's posts
						if (name == frend)
						{
							cout << "  Post " << i << " : " << posts << endl << endl;
							postTemp << posts << endl;
							i++;
						}
						tempFriend = frend;
					}
					// Close file with posts
					friendPosts.close();
				}
				else
					continue;
			}
			postTemp.close();
			string moreRepl="Y";
			// Process to leave a LIKE on a friend's post
			while((moreRepl=="Y") || (moreRepl=="y"))
			{
				cout << "Choose the post you wish to leave a LIKE!" << endl;
				int numReply;
				cin >> numReply;

				ifstream posttemp("Temp"); // Open temporary file with posts
				int a=0; // Variable to keep count of lines
				while(!posttemp.eof())
				{
					a++;
					getline(posttemp, posts);
					if(numReply == a)
					{
						ifstream likes;
						likes.open("LIKES");
						string namepost;

						ofstream templikes("TempLikes");
						int b=0; // Helping variable
						while(!likes.eof())
						{
							getline(likes, namepost);
							if(namepost.substr(0, namepost.find(":"))==tempFriend && namepost.find(posts) != std::string::npos )
								b++;
							templikes << namepost << endl;
						}
						templikes.close();

						ifstream tempLikes;
						tempLikes.open("TempLikes");
						ofstream replies("LIKES");
						string like;
						while(getline(tempLikes, like) && like!="")
						{
							// Check if friend's posts already exists. Then leave a like under the other likes for this post
							if(b>0)
							{
								if(like.substr(0, like.find(":"))==tempFriend && like.find(posts) != std::string::npos )
								{
									replies << like << endl << string((tempFriend.size()+2) ,' ') << "LIKE!" << " ("+logname+")" << endl;
									continue;
								}
								else
									replies << like << endl;
							}
							else if(b==0)// If friend's posts doesn't exists write the name of friend and his posts to leave a like
							{
								replies << like << endl;
							}
								//~ replies << tempFriend+": " << posts << endl << string((tempFriend.size()+2) ,' ') << "LIKE!" << " ("+logname+")" << endl;
								//~ replies.close();
								//~ break;n
						}
						if(b==0)
							replies << tempFriend+": " << posts << endl << string((tempFriend.size()+2) ,' ') << "LIKE!" << " ("+logname+")" << endl;

						templikes.close();
						replies.close();
						remove("TempLikes");
					}
				}
				cout << "Leave a LIKE to other posts of the same friend ? (Y/N) : ";
				cin >> moreRepl;
				if((moreRepl=="Y") || (moreRepl=="y"))
					continue;
				else
				{
					posttemp.close();
					remove("Temp");
					break;
                }
			}

			// Check if user wants to see other friend walls
			cout << "See other friend wall ? (Y/N) : ";
			cin >> myChoice;
			if((myChoice=="Y") || (myChoice=="y"))
			{
				cout << endl;
				continue;
			}
			else
			{
				myFriends.close();
				goBack();
            }
		}
	}
}

//====================
// Send friend request
//====================
void menu3()
{
	string line;
	ofstream users("users");    // Create file to save the names (not the passwords) of all registered users

	ifstream data;
	data.open("database.txt" ); // Open file database with user names and passwords

	cout << endl << "Registered (non friends) Users :" << endl << string(32, '=') << endl;
	int i = 0;
	// Save the names (not the passwords) of all registered users to "users" file
	while(!data.eof()){
		getline(data, line);
		if (i%2==0)
			users << line << endl;
		i++;
	}
	users.close();
	data.close();

    int lineCount=1;

    ifstream regUsers;
    regUsers.open("users"); // Open users file

    ofstream nonFriends("Temp");  // Create temporary file with all non-friend users

    string logline;
    while(getline(regUsers, line) && line!="")
    {
		if(line!=logname)
		{
			ifstream logUser(logname.c_str());
			int counter = 0;
			while(getline(logUser, logline))
			{
					// Check if other user name exists already in logged in user firends file
					if(logline.find(line) != std::string::npos) // find method
						counter++;
					else
						continue;
			}
			logUser.close();
			if(counter==0)
			{
				cout << lineCount << " " << line << endl;
				nonFriends << line << endl;
			}
			else
				continue;
		}
		else
			continue;
		lineCount++;
	}
	// Close files
	nonFriends.close();
	regUsers.close();

	cout << endl << "Send Friend Request..." << endl;

	int friendNumber;
	string moreFriends = "Y";

	// Write in the file of requests without deleting the existing text
	ofstream requests("Requests",  ios::app);

	// Proccess to send friend requests
	while(true){
		cout << "Choose the number that corresponds to the desired friend : ";
		cin >> friendNumber;

		// Open file with all non friends registered users
		ifstream nonFriends;
		nonFriends.open("Temp");

		int j=0;
		while(getline(nonFriends, line) && line!=""){
			j++;
			if(friendNumber == j)
			{
				// Save the requests as "user_sent_request -> user_to_accept" to the file of requests
				requests << logname + " -> " + line << endl;
			}
			else
				continue;
		}
		cout << "Add more friends ? (Y/N) : ";
		cin >> moreFriends;
		if((moreFriends=="Y") || (moreFriends=="y"))
		{
			menu3();
			continue;
        }
		else
		{
            // Close files
            requests.close();
            nonFriends.close();
            // Remove temporary file
            remove("Temp");
            goBack();
			break;
        }
	}

}

//==============================
// Accept/Reject Friend Request
//==============================
void friendrequest()
{
	string line;

	// Create file to save names of users sent request to the logged in user
	ofstream tempreq("TempReq");

	ifstream freq;
	freq.open("Requests"); // Open file with friend requests

	// Create temporary file to remake Requests text file
	ofstream mytemp;
	mytemp.open("Temp");

	// Process to save names of users who sent frined request to the logged in user
	while(getline(freq, line))
	{
		// Check if logname exists in line (find method) and not to be at the beggining of the line
		if((line.find(logname) != std::string::npos) && ((line.substr(0, line.find(" "))!=logname)))
			{
				tempreq << line.substr(0, line.find(" ")) << endl;
			}
		else
			mytemp << line << endl;
	}
	mytemp.close();
	remove("Requests");
	rename("Temp", "Requests");
	tempreq.close();

	int lineCount=1;

    ifstream tempReq;
    tempReq.open("TempReq");

	cout << endl <<"Choose the number of user you want to accept or press 0 to exit..." << endl;

	cout << "Requests" << endl << string(8,'=') << endl;
    // Print a numbered lists of users who sent frined request to the logged in user
    while(getline(tempReq, line) && line!=""){
		cout << lineCount << " " << line << endl;
		lineCount++;
	}
	tempReq.close();

	int friendNumber;
	string moreRequests = "Y";

	// Process to choose to accept or not a friend request
	while(moreRequests=="Y" || moreRequests=="y"){
		cout << endl << "Type number : ";
		cin >> friendNumber;

		ifstream tempReq;
		tempReq.open("TempReq"); // Open file of users that sent request

		int j=0;
		// Add the user who sent the request to the file of the logged in user
		// without deleting the existing text (ios::app)
		ofstream userFile(logname.c_str(), ios::app);
		while(getline(tempReq, line) && line!=""){
			j++;
			if(friendNumber == j)
			{
				// Add friend name to the file of user who sent request that has been accepted
				userFile << line << endl;
				// Add the logged in user name in the files of the users who sent the requests
				ofstream otherfile(line.c_str(), ios::app);
				otherfile << logname << endl;
				otherfile.close();
			}
			else if(friendNumber == 0)
				goBack();
				break;
		}
		cout << "Accept more requests ? (Y/N) : ";
		cin >> moreRequests;
		// Stop proces of accepting or not friend requests
		if(moreRequests=="Y" || moreRequests=="y")
		{
			friendrequest();
			continue;
		}
		else
			userFile.close();
			goBack();
			break;
	}
	tempReq.close();
}

//=================================
// See my (user logged in) friends
//=================================
void friends()
{
	string line;
	cout << endl << "Your friends are :" << endl << string(18,'=') << endl;
	// Open file with name the same of the logged in user
    ifstream logUser;
    logUser.open(logname.c_str());
    while(!logUser.eof())
    {
		getline(logUser, line);
		cout << line << endl;
	}
	goBack();
}

//=======================
// Delete friends
//=======================
void deletefriends()
{
	string line;

	// open file with username as name
	ifstream myfile;
	myfile.open(logname.c_str());

	cout << "Your friends are : " << endl << "===================" << endl;
	int lineCount = 1;
	// print all friends of the logged in user
	while(getline(myfile, line) && line != ""){
			cout << lineCount << " " << line << endl;
			lineCount++;
	}
    myfile.close();
	cout << endl << "Delete Friend..." << endl;

	int friendNumber;
	string delmoreFriends = "Y";

	// create temporaray file for input
	ofstream temp1;
    temp1.open("temp1", ios::app);

    ofstream temp2;
    temp2.open("temp2", ios::app);

    while(delmoreFriends == "Y"  || delmoreFriends=="y"){
		cout << "Choose the number that corresponds to the desired friend" << endl;
		cin >> friendNumber;

		ifstream Myfile;
		Myfile.open(logname.c_str());

		int j=0;
		// Copy all the other friends to a temp file
		while(getline(Myfile, line) && line!=""){
			j++;
			if(friendNumber != j)
            {
                temp1 << line << endl;
            }
			else
			{
                // Copy all friends from the frined you delete exept the logged in user to a temp file
				ifstream myuserfriend(line.c_str());
				string muf;
				while(getline(myuserfriend, muf))
				{
                    if(muf!=logname)
                        temp2 << muf << endl;
                    else
                        continue;
				}
				remove(line.c_str());
                rename("temp2", line.c_str());
            }
		}


		cout << "Delete more friends (Y/N) ? " << endl;
		cin >> delmoreFriends;
		if(delmoreFriends=="Y" || delmoreFriends=="y")
            deletefriends();
        else
            break;

        Myfile.close();
        temp1.close();
        temp2.close();
        remove(logname.c_str());
    }
    rename("temp1", logname.c_str());
    goBack();
}

//===============================
// Go back to Main Menu function
//===============================
void goBack()
{
	cout << endl << "Go back to main menu ? (Y/N) : ";
	string choice;
	cin >> choice;
	if((choice=="Y") || (choice=="y"))
		menu2();
	else
		exit();
}

//=======================
// Exit from the program
//=======================
int exit()
{
    cout << endl << "Programm Terminated!" << endl;
    exit(0);
    //return 0;
}

int main()
{
	cout << "======================================" << endl;
    cout << "# Welcome to the C++ Social Network! #" << endl;
    cout << "======================================" << endl;
    mainMenu();
}
